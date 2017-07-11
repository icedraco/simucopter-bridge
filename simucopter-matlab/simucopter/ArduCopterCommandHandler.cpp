#include "ArduCopterCommandHandler.h"


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
    copter.set_land_complete(false);
    copter.motors->set_desired_spool_state(AP_Motors::DESIRED_THROTTLE_UNLIMITED);

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
            m_packer.unpack(cmd.data(), cmd.size(), &arg1);
            m_commandBuffer[cmd.id] = arg1;
            break;

        default:
            // ignore
            fprintf(stderr, "WARNING UNKNOWN COMMAND ID -> id=0x%x\n", cmd.id);
            break;
    }
}
