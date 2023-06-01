#ifndef __MSG__
#define __MSG__

#define EMPTY_MESSAGE 0

enum class DIAG_STATE : uint8_t
{
    FAULTY = 0,
    OKAY = 1
};

enum class MSG_TYPE : uint8_t
{
    DSRC = 0,
    DIAGNOSTIC = 1
};

// typedef enum
// {
//     OIL_LEVEL_OKAY = 0,
//     OIL_LEVEL_LOW
// } OIL_LEVEL;

enum class SRC_PORTS : uint16_t
{
    SPEED_PORT = 6000,
    HEADING_PORT,
    TYRES_PORT,
    BATTERY_PORT,
    HEAD_LIGHT_PORT,
    OIL_LEVEL_PORT
};

#endif
