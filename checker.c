#include <stdio.h>
#include <assert.h>

int checkTemperatureLevel_i(float temperature);
int checkSocLevel_i(float soc);
int  checkChargeRate_i(float chargeRate);
int batteryIsOk(float temperature, float soc, float chargeRate);
  
int batteryIsOk(float temperature, float soc, float chargeRate) {
  int validity_i = 0;
  
  validity_i |= (checkTemperatureLevel_i(temperature));
  validity_i |= (checkSocLevel_i(soc));
  validity_i |= (checkChargeRate_i(chargeRate));

  return validity_i;
}

int checkTemperatureLevel_i(float temperature) {
    if(temperature < 0 || temperature > 45) {
    printf("Temperature out of range!\n");
    return 0;
  } 
  return 1;
}

int checkSocLevel_i(float soc) {
  if(soc < 20 || soc > 80) {
      printf("State of Charge out of range!\n");
      return 0;
  }
  return 1;
}

int  checkChargeRate_i(float chargeRate) {
  if(chargeRate > 0.8) {
      printf("Charge Rate out of range!\n");
      return 0;
    }
  return 1;
}
    
int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
