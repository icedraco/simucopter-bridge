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
            assert(arg1 != nullptr);
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


// TODO: Implement this a bit better than a static function...
static void do_handle(int cmdid, double arg) {
    switch (cmdid) {
        case SIMUCOPTER::SimuCopterMessage::SET_RATE_TARGET_YAW:
            copter.attitude_control->rate_bf_yaw_target(arg);
            break;

        case SIMUCOPTER::SimuCopterMessage::SET_RATE_TARGET_ROLL:
            copter.attitude_control->rate_bf_pitch_target(arg);
            break;

        case SIMUCOPTER::SimuCopterMessage::SET_RATE_TARGET_PITCH:
            copter.attitude_control->rate_bf_roll_target(arg);
            break;

        case SIMUCOPTER::SimuCopterMessage::SET_MOTORS_YAW:
            copter.motors->set_yaw(arg);
            break;

        case SIMUCOPTER::SimuCopterMessage::SET_MOTORS_ROLL:
            copter.motors->set_roll(arg);
            break;

        case SIMUCOPTER::SimuCopterMessage::SET_MOTORS_PITCH:
            copter.motors->set_pitch(arg);
            break;

        case SIMUCOPTER::SimuCopterMessage::SET_MOTORS_THROTTLE:
            copter.motors->set_throttle(arg);
            break;

        default:
            // ignore
            fprintf(stderr, "WARNING UNKNOWN COMMAND ID -> id=0x%x\n", cmdid);
            break;
    }
}


void SIMUCOPTER::ArduCopterCommandHandler::tick(void) {
    for (auto iter = m_commandBuffer.begin(); iter != m_commandBuffer.end(); ++iter)
        do_handle(iter->first, iter->second);
    copter.motors->output();
}


void SIMUCOPTER::ArduCopterCommandHandler::handle(const BridgeMessage &cmd) {
    if (cmd.type != BridgeMessageType::COMMAND) {
        fprintf(stderr, "ERROR: RECEIVED A NON-COMMAND -> type=%d, id=0x%x\n", cmd.type, cmd.id);
    }

    assert(cmd.type == BridgeMessageType::COMMAND);

    //----------------------------------------------------------------------------------------------------
    // FIXME: handle() uses a simple argument buffering mechanism - it will break with more than one arg,
    //        or more complex situations!
    //----------------------------------------------------------------------------------------------------

    // extract argument
    double arg1, arg2, arg3;
    switch ((SimuCopterMessage)cmd.id) {
        case SimuCopterMessage::SHUTDOWN:
            m_shutdown = true;
            break;

        case SimuCopterMessage::SET_RATE_TARGET_YAW:
        case SimuCopterMessage::SET_RATE_TARGET_ROLL:
        case SimuCopterMessage::SET_RATE_TARGET_PITCH:
        case SimuCopterMessage::SET_MOTORS_YAW:
        case SimuCopterMessage::SET_MOTORS_ROLL:
        case SimuCopterMessage::SET_MOTORS_PITCH:
        case SimuCopterMessage::SET_MOTORS_THROTTLE:
            extract_args(cmd, 1, &arg1, &arg2, &arg3);
            m_commandBuffer[cmd.id] = arg1;
            break;

        default:
            // ignore
            fprintf(stderr, "WARNING UNKNOWN COMMAND ID -> id=0x%x\n", cmd.id);
            break;
    }
}
