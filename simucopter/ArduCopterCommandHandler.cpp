#include "ArduCopterCommandHandler.h"

// TODO: Argument packing should be "standardized" as time permits... this is ugly
static void extract_args(const BridgeMessage& cmd, int num_args, double* arg1, double* arg2, double* arg3) {
    if (num_args < 1)
        return;
    if (num_args > 3)
        num_args = 3;

    struct {
        double arg1;
        double arg2;
        double arg3;
    } arg_s;

    switch(num_args) {
        case 1:
            if (arg1 != nullptr)
                cmd.load_data(arg1, sizeof(double));
            break;

        case 2:
        case 3:
            memset(&arg_s, 0, sizeof(arg_s));
            cmd.load_data(&arg_s, sizeof(arg_s));
            if (arg1 != nullptr)
                *arg1 = arg_s.arg1;
            if (arg2 != nullptr)
                *arg2 = arg_s.arg2;
            if (arg3 != nullptr)
                *arg3 = arg_s.arg3;
            break;

        default:
            assert(false);
    }
}


void SIMUCOPTER::ArduCopterCommandHandler::handle(const BridgeMessage &cmd) const {
    assert(cmd.type == BridgeMessageType::COMMAND);
    double arg1, arg2, arg3;
    switch ((SimuCopterMessage)cmd.id) {
        case SimuCopterMessage::SHUTDOWN:
            m_flag_shutdown = true;
            break;

        case SimuCopterMessage::SET_RATE_TARGET_YAW:
            extract_args(cmd, 1, &arg1, &arg2, &arg3);
            copter.attitude_control->rate_bf_yaw_target(arg1);
            break;

        case SimuCopterMessage::SET_RATE_TARGET_ROLL:
            extract_args(cmd, 1, &arg1, &arg2, &arg3);
            copter.attitude_control->rate_bf_pitch_target(arg1);
            break;

        case SimuCopterMessage::SET_RATE_TARGET_PITCH:
            extract_args(cmd, 1, &arg1, &arg2, &arg3);
            copter.attitude_control->rate_bf_roll_target(arg1);
            break;

        case SimuCopterMessage::SET_MOTORS_YAW:
            extract_args(cmd, 1, &arg1, &arg2, &arg3);
            copter.motors->set_yaw(arg1);
            break;

        case SimuCopterMessage::SET_MOTORS_ROLL:
            extract_args(cmd, 1, &arg1, &arg2, &arg3);
            copter.motors->set_roll(arg1);
            break;

        case SimuCopterMessage::SET_MOTORS_PITCH:
            extract_args(cmd, 1, &arg1, &arg2, &arg3);
            copter.motors->set_pitch(arg1);
            break;

        case SimuCopterMessage::SET_MOTORS_THROTTLE:
            extract_args(cmd, 1, &arg1, &arg2, &arg3);
            copter.motors->set_throttle(arg1);
            break;

        default:
            // ignore
            break;
    }
}
