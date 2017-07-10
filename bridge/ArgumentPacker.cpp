#include "ArgumentPacker.h"

using namespace SIMUCOPTER;

void ArgumentPacker::unpack(const void *src, size_t src_sz, int *arg1) const {
    assert(src_sz >= sizeof(struct int_arg1_envelope_s));
    struct int_arg1_envelope_s* envelope = (int_arg1_envelope_s*)src;
    *arg1 = envelope->arg1;
}

void ArgumentPacker::unpack(const void *src, size_t src_sz, double *arg1) const {
    assert(src_sz >= sizeof(struct arg1_envelope_s));
    struct arg1_envelope_s* envelope = (arg1_envelope_s*)src;
    *arg1 = envelope->arg1;
}

void ArgumentPacker::unpack(const void *src, size_t src_sz, double *arg1, double *arg2) const {
    assert(src_sz >= sizeof(struct arg2_envelope_s));
    struct arg2_envelope_s* envelope = (arg2_envelope_s*)src;
    *arg1 = envelope->arg1;
    *arg2 = envelope->arg2;
}

void ArgumentPacker::unpack(const void *src, size_t src_sz, double *arg1, double *arg2, double *arg3) const {
    assert(src_sz >= sizeof(struct arg3_envelope_s));
    struct arg3_envelope_s* envelope = (arg3_envelope_s*)src;
    *arg1 = envelope->arg1;
    *arg2 = envelope->arg2;
    *arg3 = envelope->arg3;
}

size_t ArgumentPacker::pack(void *dst, size_t dst_limit, int arg1) const {
    assert(dst_limit >= sizeof(struct int_arg1_envelope_s));
    struct int_arg1_envelope_s* envelope = (int_arg1_envelope_s*)dst;
    envelope->arg1 = arg1;
    return sizeof(struct int_arg1_envelope_s);
}

size_t ArgumentPacker::pack(void *dst, size_t dst_limit, double arg1) const {
    assert(dst_limit >= sizeof(struct arg1_envelope_s));
    struct arg1_envelope_s* envelope = (arg1_envelope_s*)dst;
    envelope->arg1 = arg1;
    return sizeof(struct arg1_envelope_s);
}

size_t ArgumentPacker::pack(void *dst, size_t dst_limit, double arg1, double arg2) const {
    assert(dst_limit >= sizeof(struct arg2_envelope_s));
    struct arg2_envelope_s* envelope = (arg2_envelope_s*)dst;
    envelope->arg1 = arg1;
    envelope->arg2 = arg2;
    return sizeof(struct arg2_envelope_s);
}

size_t ArgumentPacker::pack(void *dst, size_t dst_limit, double arg1, double arg2, double arg3) const {
    assert(dst_limit >= sizeof(struct arg3_envelope_s));
    struct arg3_envelope_s* envelope = (arg3_envelope_s*)dst;
    envelope->arg1 = arg1;
    envelope->arg2 = arg2;
    envelope->arg3 = arg3;
    return sizeof(struct arg3_envelope_s);
}
