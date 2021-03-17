/*****************************************************************************/
/***    \file        BatteryConditionValidation.c
***     \author      Abinesh Kanji Kovil Thatchinamoorthy (RBEI/ECK1) 
***
***     \brief       Header file for Battery Condition Monitoring
/*****************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <string.h>

/*=============================================================================
=======                       CONSTANTS  &  TYPES                       =======
=============================================================================*/

char batPar[6][12] = {"TEMP","SOC","CHARGERATE","TEMP","LADEZUSTAND","LADESTROM"};
char batLevel[6][12] = {"low","high","Normallevel","niedrig","hoch","Normal"};


#define TEMP_VALID_MIN_VAL                 0
#define TEMP_VALID_MAX_VAL                45
#define SOC_VALID_MIN_VAL                 20
#define SOC_VALID_MAX_VAL                 80
#define CHARGE_RATE_VALID_MIN_VAL          0
#define CHARGE_RATE_VALID_MAX_VAL         0.8

#define ALL_VALID_STATE                    7

/* Enum for the possible values of Languages */
typedef enum
{
    ENGLISH_LANGUAGE   = 0X00,
    GERMAN_LANGUAGE          ,
    TOTAL_LANGUAGES_SUPPORTED,
}vsum_LangVal_t;

typedef struct {
    int battCondnParam_i[3];
}battCondn_t;

typedef struct {
    int battCondnValidity_i[3];
    int anomalyCnt_i;   
}BMS_t;


