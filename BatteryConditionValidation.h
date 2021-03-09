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

/* Enum for the possible values of Command Ignition status from BCM */
typedef enum
{
    VSUM_STATE_BCM_ING_STS_INIT   = 0X00,
    VSUM_STATE_BCM_ING_STS_IGN_LK = 0X01,
    VSUM_STATE_BCM_ING_STS_ACC    = 0X03,
    VSUM_STATE_BCM_ING_STS_RUN    = 0X04,
    VSUM_STATE_BCM_ING_STS_START  = 0X05,
    VSUM_STATE_BCM_ING_STS_SNA    = 0X07,
}vsum_BcmCmdIngSts_t;

typedef struct {
    int prevBattCondnParam_i[3];
}prevBattCondn_t;

typedef struct {
    int battCondnParam_i[3];
}battCondn_t;


