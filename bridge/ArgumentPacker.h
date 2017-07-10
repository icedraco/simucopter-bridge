//
// ArgumentPacker
//
// Responsible for packing and unpacking arbitrary arguments into/from a void*
// buffer.
//
// This component will convert function arguments into bytes, and back,
// allowing them to travel over the network in messages.
//

#pragma once

#include <cstdlib>
#include <assert.h>


namespace SIMUCOPTER {
    struct int_arg1_envelope_s {
        int arg1;
    };

    struct arg1_envelope_s {
        double arg1;
    };

    struct arg2_envelope_s {
        double arg1;
        double arg2;
    };

    struct arg3_envelope_s {
        double arg1;
        double arg2;
        double arg3;
    };

    class ArgumentPacker {
    public:
        ArgumentPacker() {}

        // void* --> arg1[, arg2[, arg3]]
        void unpack(const void *src, size_t src_sz, int *arg1) const;
        void unpack(const void *src, size_t src_sz, double *arg1) const;
        void unpack(const void *src, size_t src_sz, double *arg1, double *arg2) const;
        void unpack(const void *src, size_t src_sz, double *arg1, double *arg2, double *arg3) const;

        // arg1[, arg2[, arg3]] --> void*
        size_t pack(void *dst, size_t dst_limit, int arg1) const;
        size_t pack(void *dst, size_t dst_limit, double arg1) const;
        size_t pack(void *dst, size_t dst_limit, double arg1, double arg2) const;
        size_t pack(void *dst, size_t dst_limit, double arg1, double arg2, double arg3) const;
    };
}
