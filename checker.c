#include <stdio.h>
#include <assert.h>

int checkBatteryCond_i(float batteryParam_f ,float minRange_f, float maxRange_f,int batParamIndex_i);
int batteryIsOk(float temperature, float soc, float chargeRate);
  
int batteryIsOk(float temperature, float soc, float chargeRate) {
  int validity_i = 0;
  
  validity_i |= (checkTemperatureLevel_i(temperature));
  validity_i |= (checkSocLevel_i(soc)) << 1;
  validity_i |= (checkChargeRate_i(chargeRate)) << 2;
  
  validity_i = (7 == validity_i) ? 1 : 0;
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
  
  if((batteryParam_f < minRange) || (batteryParam_f < maxRange))
  {
   printf("Battery parameter %s is out of range!\n",batPar[batParIndex]);
   return 0;
  }
  else
  {
   printf("Battery parameter %s is Normal !\n",batPar[batParIndex]);
   return 1;
  }
}
    
int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
