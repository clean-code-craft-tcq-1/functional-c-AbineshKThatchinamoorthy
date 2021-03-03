#include <stdio.h>
#include <assert.h>

int checkBatteryCond_i(float batteryParam_f ,float minRange_f, float maxRange_f,int batParamIndex_i);
int batteryIsOk(float temperature, float soc, float chargeRate);
  
int batteryIsOk(float temperature, float soc, float chargeRate) {
  int validity_i = 0;
  
  validity_i |= (checkBatteryCond_i(temperature,0,45,0));
  validity_i |= (checkBatteryCond_i(soc,20,80,1)) << 1;
  validity_i |= (checkBatteryCond_i(chargeRate,0,0.8,2)) << 2;
  
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
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
