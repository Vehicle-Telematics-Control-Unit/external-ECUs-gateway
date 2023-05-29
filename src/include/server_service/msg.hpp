#ifndef __MSG__
#define __MSG__

#define EMPTY_MESSAGE 0

typedef enum
{
    TYRES_CONDITION_OKAY = 0,
    TYRES_ARE_DEFLATED
} TYRES;

typedef enum
{
    BATTERY_OKAY = 0,
    BATTERY_FAULT
} BATTERY;

typedef enum
{
    HEAD_LIGHT_OKAY = 0,
    HEAD_LIGHT_FAULT
} HEAD_LIGHT;

typedef enum
{
    OIL_LEVEL_OKAY = 0,
    OIL_LEVEL_LOW
} OIL_LEVEL;

typedef enum
{
    HEADING_PORT = 6000,
    SPEED_PORT,
    TYRES_PORT,
    BATTERY_PORT,
    HEAD_LIGHT_PORT,
    OIL_LEVEL_PORT
} SRC_PORTS;

// typedef struct
// {
//     /* data */
//     uint16_t heading; // port 6000
//     uint8_t speed;    // port 6001
// } msg_DSRC;

// typedef struct
// {
//     /* data */
//     TYRES tyres;          // port 6002
//     BATTERY battery;      // port 6003
//     HEAD_LIGHT headLight; // port 6004
//     OIL_LEVEL oilLevel;   // port 6005
// } msg_diagnostic;

#endif
