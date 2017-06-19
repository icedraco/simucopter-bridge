#include "ArduCopterRequestHandler.h"

void SIMUCOPTER::ArduCopterRequestHandler::register_self(BridgeService &service) const {
    /**
     * NOTE: WE DO NOT PUT THE SET_* MESSAGES HERE, AS THEY ARE NOT
     *       CONSIDERED REQUESTS THAT MUST RETURN A VALUE!
     *
     *       ADD THEM TO THE COMMAND HANDLER INSTEAD!
     */

    service.set_request_handler(SimuCopterMessage::GET_FLIGHT_MODE, this);
    service.set_request_handler(SimuCopterMessage::GET_ACCEL_X, this);
    service.set_request_handler(SimuCopterMessage::GET_ACCEL_Y, this);
    service.set_request_handler(SimuCopterMessage::GET_ACCEL_Z, this);
    service.set_request_handler(SimuCopterMessage::GET_GYRO_X, this);
    service.set_request_handler(SimuCopterMessage::GET_GYRO_Y, this);
    service.set_request_handler(SimuCopterMessage::GET_GYRO_Z, this);
    service.set_request_handler(SimuCopterMessage::GET_STATE_YAW, this);
    service.set_request_handler(SimuCopterMessage::GET_STATE_ROLL, this);
    service.set_request_handler(SimuCopterMessage::GET_STATE_PITCH, this);
    service.set_request_handler(SimuCopterMessage::GET_DESIRED_YAW, this);
    service.set_request_handler(SimuCopterMessage::GET_DESIRED_ROLL, this);
    service.set_request_handler(SimuCopterMessage::GET_DESIRED_PITCH, this);
    service.set_request_handler(SimuCopterMessage::GET_DESIRED_THROTTLE, this);
}

virtual void SIMUCOPTER::ArduCopterRequestHandler::handle(const BridgeMessage &msg, BridgeMessage &response) const {
    assert(msg.type == BridgeMessageType::REQUEST);
    double result;
    float target_roll, target_pitch, target_yaw;  // desired angles (GET_DESIRED_*)

    switch ((SimuCopterMessage)msg.type) {
        case SimuCopterMessage::GET_FLIGHT_MODE:
            result = copter.copter_control_mode;
            break;

        case SimuCopterMessage::GET_ACCEL_X:
            result = copter.ins.get_accel(0).x;
            break;

        case SimuCopterMessage::GET_ACCEL_Y:
            result = copter.ins.get_accel(0).y;
            break;

        case SimuCopterMessage::GET_ACCEL_Z:
            result = copter.ins.get_accel(0).z;
            break;

        case SimuCopterMessage::GET_GYRO_X:
            result = copter.ins.get_gyro(0).x;
            break;

        case SimuCopterMessage::GET_GYRO_Y:
            result = copter.ins.get_gyro(0).y;
            break;

        case SimuCopterMessage::GET_GYRO_Z:
            result = copter.ins.get_gyro(0).z;
            break;

        case SimuCopterMessage::GET_STATE_YAW:
            result = copter.ahrs.yaw;
            break;

        case SimuCopterMessage::GET_STATE_ROLL:
            result = copter.ahrs.roll;
            break;

        case SimuCopterMessage::GET_STATE_PITCH:
            result = copter.ahrs.pitch;
            break;

        case SimuCopterMessage::GET_DESIRED_YAW:
            copter.get_pilot_desired_angle_rates(
                    copter.channel_roll->get_control_in(),
                    copter.channel_pitch->get_control_in(),
                    copter.channel_yaw->get_control_in(),
                    target_roll,
                    target_pitch,
                    target_yaw);
            result = target_yaw;
            break;

        case SimuCopterMessage::GET_DESIRED_ROLL:
            copter.get_pilot_desired_angle_rates(
                    copter.channel_roll->get_control_in(),
                    copter.channel_pitch->get_control_in(),
                    copter.channel_yaw->get_control_in(),
                    target_roll,
                    target_pitch,
                    target_yaw);
            result = target_roll;
            break;

        case SimuCopterMessage::GET_DESIRED_PITCH:
            copter.get_pilot_desired_angle_rates(
                    copter.channel_roll->get_control_in(),
                    copter.channel_pitch->get_control_in(),
                    copter.channel_yaw->get_control_in(),
                    target_roll,
                    target_pitch,
                    target_yaw);
            result = target_pitch;
            break;

        case SimuCopterMessage::GET_DESIRED_THROTTLE:
            result = copter.get_pilot_desired_throttle(copter.channel_throttle->control_in);
            break;

        default:
            /**
             * This area should not be reached: the unfamiliar messages
             * should've not been registered in the first place!
             *
             * If we are here, then it must be a bug!
             */
            result = -999;
    }

    response.set_data(&result, sizeof(result));
}