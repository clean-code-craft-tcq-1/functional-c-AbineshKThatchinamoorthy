/*****************************************************************************/
/***    \file        BatteryConditionValidation.c
***     \author      Abinesh Kanji Kovil Thatchinamoorthy (RBEI/ECK1) 
***
***     \brief       Source file for Battery Condition Monitoring
/*****************************************************************************/

/* Project Inlcudes */
#include "BatteryConditionValidation.h"

static battCondn_t battCondn_s;
static battCondn_t prevBattCondn_s;
static BMS_t bms_s;
static int langVal_i;

/* Funtion declarations */
static int testBatteryCond_i();
static int checkBatteryParam_i(float minRange_f, float maxRange_f,int batParamIndex_i, int langIndex_i);
static void informTrendChange_v(int batParamIndex_i, int langIndex_i);
static void informForCounterMeasure_v();

/*---------------------------------------------------------------------------*/
/*     FUNCTION:    testBatteryCond_i
 */
/*!    \brief       check whether the Battery parameter is within the range
 * 
 *     \param       tempVal_f       [IN] - current Battery param value
 *     \param       socVal_f        [IN] - acceptable minimum value
 *     \param       chargeRateVal_f [IN] - acceptable maximum value
 *     \returns     validity_i      [OUT]- Overall Battery Status
 *
*//*------------------------------------------------------------------------*/
static int testBatteryCond_i() {
  int validity_i = 1, langIndex_i = 0;
  
  langIndex_i = (GERMAN_LANGUAGE == langVal_i)? 3: 0;
  
  checkBatteryParam_i(TEMP_VALID_MIN_VAL        ,TEMP_VALID_MAX_VAL       ,0 ,langIndex_i);     /* Store the temperature status in last bit */
  checkBatteryParam_i(SOC_VALID_MIN_VAL         ,SOC_VALID_MAX_VAL        ,1 ,langIndex_i);/* Store the temperature status in last but 1 bit*/
  checkBatteryParam_i(CHARGE_RATE_VALID_MIN_VAL ,CHARGE_RATE_VALID_MAX_VAL,2 ,langIndex_i);/* Store the temperature status in last but 2 bits*/
  
  /* One/Many of the 3 states is not valid */
  if(0 < bms_s.anomalyCnt_i)
  {
      validity_i = 0;
      /* Inform the external controller for counter measure */ 
      informForCounterMeasure_v();
  }
  
  bms_s.anomalyCnt_i = 0;
  bms_s.invalidBattParam_c[] = "";
    
  /*Return the validity status */
  return validity_i;
}

/*---------------------------------------------------------------------------*/
/*     FUNCTION:    checkBatteryParam_i
 */
/*!    \brief       check whether the Battery parameter is within the range
 * 
 *     \param       batteryParam_f [IN] - current Battery param value
 *     \param       minRange_f     [IN] - acceptable minimum value
 *     \param       maxRange_f     [IN] - acceptable maximum value
 *     \param       batParamIndex_i[IN] - Index of the Battery parameter
 *     \returns     Battery parameter validity status
 *
*//*------------------------------------------------------------------------*/
static int checkBatteryParam_i(float minRange_f, float maxRange_f,int batParamIndex_i, int langIndex_i)
{
  
  if(battCondn_s.battCondnParam_i[batParamIndex_i] < minRange_f)
  {
   printf("Battery parameter %s %s!\n Current Val : %d !\n", batPar[batParamIndex_i+langIndex_i], batLevel[batParamIndex_i+langIndex_i], battCondn_s.battCondnParam_i[batParamIndex_i]);
   bms_s.invalidBattParam_c[batParamIndex_i+langIndex_i] = batPar[batParamIndex_i+langIndex_i];
   bms_s.anomalyCnt_i++;
  }
  else if(battCondn_s.battCondnParam_i[batParamIndex_i] > maxRange_f)
  {
   printf("Battery parameter %s %s!\n Current Val : %d !\n", batPar[batParamIndex_i+langIndex_i], batLevel[batParamIndex_i+langIndex_i], battCondn_s.battCondnParam_i[batParamIndex_i]);
   bms_s.invalidBattParam_c[batParamIndex_i+langIndex_i] = batPar[batParamIndex_i+langIndex_i];
   bms_s.anomalyCnt_i++;
  }
  else
  {
    informTrendChange_v(batParamIndex_i, langIndex_i);
    bms_s.battCondnValidity_i[batParamIndex_i] = 1;
  }
}


/*---------------------------------------------------------------------------*/
/*     FUNCTION:    informTrendChange_v
 */
/*!    \brief       Print the change in trend when the value is Normal
 * 
 *     \param       batParamIndex_i[IN] - Index of the Battery parameter
 *     \returns     void
 *
*//*------------------------------------------------------------------------*/
static void informTrendChange_v(int batParamIndex_i, int langIndex_i)
{
   int valChange_i = 0;
  
   valChange_i = battCondn_s.battCondnParam_i[batParamIndex_i] - prevBattCondn_s.battCondnParam_i[batParamIndex_i];
  
   if(4 <= valChange_i)
   {
      printf(" Battery parameter %s %s.\n Current trend : Value is increasing(Approaching higher threshold) \n Current Val : %d !\n", batPar[batParamIndex_i+langIndex_i], batLevel[batParamIndex_i+langIndex_i], battCondn_s.battCondnParam_i[batParamIndex_i]);
   }
   else if(4 >= valChange_i)
   {
     printf(" Battery parameter %s %s .\n Current trend : Value is decreasing(Approaching lower threshold) \n Current Val : %d !\n", batPar[batParamIndex_i+langIndex_i], batLevel[batParamIndex_i+langIndex_i], battCondn_s.battCondnParam_i[batParamIndex_i]);
   }
   else
   {
      printf(" Battery parameter %s %s .\n Current Val : %d !\n", batPar[batParamIndex_i+langIndex_i], batLevel[batParamIndex_i+langIndex_i], battCondn_s.battCondnParam_i[batParamIndex_i]);
   }  
}

static void informForCounterMeasure_v()
{
  string prntStr[100] = " ";
  printf("ANAMOLY's DETECTED - Time for COUNTER MEASURE \n ");
  /* No actual controller which takes care of counter measure during anamolies - So currently, print the anamolies in the console */
  for(int cnt_i = 0; cnt_i < bms_s.anomalyCnt_i; cnt_i++)
  {
    strcat(prntStr, " "
    strcat(prntStr, bms_s.invalidBattParam_c[cnt_i]);
  }
  
  printf("Anamoly's for the below Battery parameters have been detected\n %s ", prntStr)
}

int main() {
  battCondn_s.battCondnParam_i[0] = 25;
  battCondn_s.battCondnParam_i[1] = 70;
  battCondn_s.battCondnParam_i[2] = 0.7;
  langVal_i = GERMAN_LANGUAGE;
  assert(testBatteryCond_i());
  battCondn_s = prevBattCondn_s;
  
  battCondn_s.battCondnParam_i[0] = 50;
  battCondn_s.battCondnParam_i[1] = 10;
  battCondn_s.battCondnParam_i[2] = 0;
  assert(!testBatteryCond_i());
  langVal_i = ENGLISH_LANGUAGE;
  battCondn_s = prevBattCondn_s;
  
  battCondn_s.battCondnParam_i[0] = 50;
  battCondn_s.battCondnParam_i[1] = 75;
  battCondn_s.battCondnParam_i[2] = 0.9;
  langVal_i = ENGLISH_LANGUAGE;
  assert(!testBatteryCond_i());
  battCondn_s = prevBattCondn_s;
  
  battCondn_s.battCondnParam_i[0] = 25;
  battCondn_s.battCondnParam_i[1] = 85;
  battCondn_s.battCondnParam_i[2] = 0.9;
  langVal_i = GERMAN_LANGUAGE;
  assert(!testBatteryCond_i());
  battCondn_s = prevBattCondn_s;
  
  battCondn_s.battCondnParam_i[0] = 50;
  battCondn_s.battCondnParam_i[1] = 85;
  battCondn_s.battCondnParam_i[2] = 0.9;
  langVal_i = ENGLISH_LANGUAGE;
  assert(!testBatteryCond_i());
  battCondn_s = prevBattCondn_s;
}
