#pragma once

namespace SIMUCOPTER {
    /**
     * SimuCopter message IDs
     */
    enum SimuCopterMessage {
        PING                  = 0x0000,
        ERROR                 = 0xffff,
        SHUTDOWN              = 0xfffe,

        GET_FLIGHT_MODE       = 0x1000,
        GET_ACCEL_X           = 0x1001,
        GET_ACCEL_Y           = 0x1002,
        GET_ACCEL_Z           = 0x1003,
        GET_GYRO_X            = 0x1011,
        GET_GYRO_Y            = 0x1012,
        GET_GYRO_Z            = 0x1013,
        GET_STATE_YAW         = 0x1031,
        GET_STATE_ROLL        = 0x1032,
        GET_STATE_PITCH       = 0x1033,
        GET_STATE_THROTTLE    = 0x1034,
        GET_DESIRED_YAW       = 0x1041,
        GET_DESIRED_ROLL      = 0x1042,
        GET_DESIRED_PITCH     = 0x1043,
        GET_DESIRED_THROTTLE  = 0x1044,
        GET_HEADING           = 0x1045,

        SET_RATE_TARGET_YAW   = 0x1051,
        SET_RATE_TARGET_ROLL  = 0x1052,
        SET_RATE_TARGET_PITCH = 0x1053,
        SET_MOTORS_YAW        = 0x1061,
        SET_MOTORS_ROLL       = 0x1062,
        SET_MOTORS_PITCH      = 0x1063,
        SET_MOTORS_THROTTLE   = 0x1064,

        GCS_SEND_TEXT         = 0x2001,

        SITL_GET_ACCEL_X      = 0x3001,
        SITL_GET_ACCEL_Y      = 0x3002,
        SITL_GET_ACCEL_Z      = 0x3003,
        SITL_GET_GYRO_X       = 0x3011,
        SITL_GET_GYRO_Y       = 0x3012,
        SITL_GET_GYRO_Z       = 0x3013,
        SITL_GET_STATE_YAW    = 0x3031,
        SITL_GET_STATE_ROLL   = 0x3032,
        SITL_GET_STATE_PITCH  = 0x3033,

        SITL_GET_HEIGHT       = 0x3041,
        SITL_GET_HEADING      = 0x3042,
    };
}