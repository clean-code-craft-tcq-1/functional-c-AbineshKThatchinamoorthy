#include <stdio.h>
#include <assert.h>

int checkBatteryCond_i(float batteryParam_f ,float minRange_f, float maxRange_f,int batParamIndex_i);
int testBatteryCond_i(float temperature, float soc, float chargeRate);

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
int testBatteryCond_i(float tempVal_f, float socVal_f, float chargeRateVal_f) {
  int validity_i = 0;
  
  validity_i |= (checkBatteryCond_i(tempVal_f,0,45,0));/* Store the temperature status in last bit */
  validity_i |= (checkBatteryCond_i(socVal_f,20,80,1)) << 1;/* Store the temperature status in last but 1 bit*/
  validity_i |= (checkBatteryCond_i(chargeRateVal_f,0,0.8,2)) << 2;/* Store the temperature status in last but 2 bits*/
  /* All the 3 states are valid */
  validity_i = (7 == validity_i) ? 1 : 0;
  /*Return the validity status */
  return validity_i;
}

/*---------------------------------------------------------------------------*/
/*     FUNCTION:    checkBatteryCond_i
 */
/*!    \brief       check whether the Battery parameter is within the range
 * 
 *     \param       batteryParam_f [IN] - current Battery param value
 *     \param       minRange_f     [IN] - acceptable minimum value
 *     \param       maxRange_f     [IN] - acceptable maximum value
 *     \param       batParamIndex_i[IN] - acceptable maximum value
 *     \returns     Battery parameter validity status
 *
*//*------------------------------------------------------------------------*/
int checkBatteryCond_i(float batteryParam_f ,float minRange_f, float maxRange_f,int batParamIndex_i)
{
  /*Battery par printed for ref*/
  char batPar[3][10] = {"temp","soc","chargerate"};
  
  if((batteryParam_f < minRange_f) || (batteryParam_f > maxRange_f))
  {
   printf("Battery parameter %s is out of range!\n",batPar[batParamIndex_i]);
   return 0;
  }
  else
  {
   printf("Battery parameter %s is Normal !\n",batPar[batParamIndex_i]);
   return 1;
  }
}
    
int main() {
  assert(testBatteryCond_i(25, 70, 0.7));
  assert(!testBatteryCond_i(50, 85, 0));
}
