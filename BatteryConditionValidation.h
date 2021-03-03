/*****************************************************************************/
/***    \file        BatteryConditionValidation.c
***     \author      Abinesh Kanji Kovil Thatchinamoorthy (RBEI/ECK1) 
***
***     \brief       Header file for Battery Condition Monitoring
/*****************************************************************************/

#include <stdio.h>
#include <assert.h>

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/

char batPar[3][10] = {"temp","soc","chargerate"};

#define TEMP_VALID_MIN_VAL                 0
#define TEMP_VALID_MAX_VAL                45
#define SOC_VALID_MIN_VAL                 20
#define SOC_VALID_MAX_VAL                 80
#define CHARGE_RATE_VALID_MIN_VAL          0
#define CHARGE_RATE_VALID_MAX_VAL         0.8

#define ALL_VALID_STATE                    7
