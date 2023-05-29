#ifndef __MSG__
#define __MSG__

#define EMPTY_MESSAGE 0

enum class DIAG_STATE : uint8_t
{
    FAULTY = 0,
    OKAY = 1
};

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

#endif
