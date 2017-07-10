#include "SitlRequestHandler.h"

extern float radians(float);

bool SIMUCOPTER::SitlRequestHandler::connect_sitl(void) {
    connected = false;

    m_sitl = (SITL::SITL *)AP_Param::find_object("SIM_");
    if (m_sitl == nullptr) {
        return false;
    }

    m_sitl_model = (SITL::Aircraft *)AP_Param::find_object("SIM_");
    if (m_sitl_model == nullptr) {
        return false;
    }

    m_barometer = (AP_Baro *)AP_Param::find_object("GND_");
    if (m_barometer == nullptr) {
        return false;
    }

    connected = true;
    return true;
}

void SIMUCOPTER::SitlRequestHandler::register_self(BridgeService& service) {
    /**
     * NOTE: WE DO NOT PUT THE SET_* MESSAGES HERE, AS THEY ARE NOT
     *       CONSIDERED REQUESTS THAT MUST RETURN A VALUE!
     *
     *       ADD THEM TO THE COMMAND HANDLER INSTEAD!
     */

    service.set_request_handler(SimuCopterMessage::SITL_GET_ACCEL_X, this);
    service.set_request_handler(SimuCopterMessage::SITL_GET_ACCEL_Y, this);
    service.set_request_handler(SimuCopterMessage::SITL_GET_ACCEL_Z, this);
    service.set_request_handler(SimuCopterMessage::SITL_GET_GYRO_X, this);
    service.set_request_handler(SimuCopterMessage::SITL_GET_GYRO_Y, this);
    service.set_request_handler(SimuCopterMessage::SITL_GET_GYRO_Z, this);
    service.set_request_handler(SimuCopterMessage::SITL_GET_STATE_YAW, this);
    service.set_request_handler(SimuCopterMessage::SITL_GET_STATE_ROLL, this);
    service.set_request_handler(SimuCopterMessage::SITL_GET_STATE_PITCH, this);
    service.set_request_handler(SimuCopterMessage::SITL_GET_HEIGHT, this);
    service.set_request_handler(SimuCopterMessage::SITL_GET_HEADING, this);
}

void SIMUCOPTER::SitlRequestHandler::handle(const BridgeMessage& msg, BridgeMessage& response) {
    assert(msg.type == BridgeMessageType::REQUEST);
    double result;
    switch ((SimuCopterMessage)msg.id) {
        case SITL_GET_ACCEL_X:
            result = radians(m_sitl->state.xAccel);
            break;

        case SITL_GET_ACCEL_Y:
            result = radians(m_sitl->state.yAccel);
            break;

        case SITL_GET_ACCEL_Z:
            result = radians(m_sitl->state.zAccel);
            break;

        case SITL_GET_GYRO_X:
            result = (double)m_sitl_model->get_gyro().x;
            break;

        case SITL_GET_GYRO_Y:
            result = (double)m_sitl_model->get_gyro().y;
            break;

        case SITL_GET_GYRO_Z:
            result = (double)m_sitl_model->get_gyro().z;
            break;

        case SITL_GET_STATE_YAW:
            result = radians(m_sitl->state.yawDeg);
            break;

        case SITL_GET_STATE_ROLL:
            result = radians(m_sitl->state.rollDeg);
            break;

        case SITL_GET_STATE_PITCH:
            result = radians(m_sitl->state.pitchDeg);
            break;

        case SITL_GET_HEIGHT:
            result = (double)m_barometer->get_altitude();
            break;

        case SITL_GET_HEADING:
            result = (double)m_sitl->state.heading;
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

    char buffer[BRIDGE_MSG_DATA_CAPACITY];
    size_t packed_sz = m_packer.pack(buffer, BRIDGE_MSG_DATA_CAPACITY, result);
    response.set_data(&buffer, packed_sz);
}
