//
// Common assistance functionality for testing purposess
//

#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>

static const int MIN_RAND_PORT = 3000;
static const int MAX_RAND_PORT = 65535;

inline std::string get_random_zmq_url() {
    static int range = MAX_RAND_PORT - MIN_RAND_PORT;
    int rand_port = rand() % range + MIN_RAND_PORT;
    std::stringstream ss;
    ss << "tcp://127.0.0.1:" << rand_port;
    return ss.str();
}
