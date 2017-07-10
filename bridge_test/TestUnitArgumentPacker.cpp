//
// Unit Test Case for ArgumentPacker component
//

#include <thread>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <bridge/ArgumentPacker.h>

#define TUAP_BUFFER_SIZE 64
#define TUAP_MAGIC_BYTE 0xFF

using testing::Eq;
using SIMUCOPTER::ArgumentPacker;
using SIMUCOPTER::int_arg1_envelope_s;
using SIMUCOPTER::arg1_envelope_s;
using SIMUCOPTER::arg2_envelope_s;
using SIMUCOPTER::arg3_envelope_s;

namespace {
    class TestUnitArgumentPacker: public testing::Test {
    public:
        ArgumentPacker packer;
        char buffer[TUAP_BUFFER_SIZE];
    };

    static void set_buffer(void* buffer, size_t buffer_sz) {
        memset(buffer, TUAP_MAGIC_BYTE, buffer_sz);
    }

    static bool is_buffer_intact(void* buffer, size_t buffer_sz, size_t skip_bytes) {
        assert(skip_bytes <= buffer_sz);
        unsigned char* buf = (unsigned char*)buffer;

        // ensure the bytes past "skip_bytes" point were not changed since
        // set_buffer() was invoked
        for (size_t i = skip_bytes; i < buffer_sz; i++) {
            if (buf[i] != TUAP_MAGIC_BYTE) {
                fprintf(stderr,
                        "WARNING: is_buffer_intact(buf, %ld, %ld) failed at index %ld -> 0x%02x != 0x%02x\n",
                        buffer_sz, skip_bytes, i, buf[i], TUAP_MAGIC_BYTE);

                return false; // byte changed
            }
        }

        return true; // rest of the buffer appears to be intact
    }
}


TEST_F(TestUnitArgumentPacker, TestPackUnpackDoubleArg1) {
    assert(sizeof(buffer) >= TUAP_BUFFER_SIZE);
    double arg = 0;

    packer.pack(buffer, sizeof(buffer), 13.37);
    packer.unpack(buffer, sizeof(buffer), &arg);

    ASSERT_EQ(arg, 13.37);
}

TEST_F(TestUnitArgumentPacker, TestPackUnpackDoubleArg2) {
    assert(sizeof(buffer) >= TUAP_BUFFER_SIZE);
    double arg1 = 0;
    double arg2 = 0;

    packer.pack(buffer, sizeof(buffer), 13.37, 66.66);
    packer.unpack(buffer, sizeof(buffer), &arg1, &arg2);

    ASSERT_EQ(arg1, 13.37);
    ASSERT_EQ(arg2, 66.66);
}

TEST_F(TestUnitArgumentPacker, TestPackUnpackDoubleArg3) {
    assert(sizeof(buffer) >= TUAP_BUFFER_SIZE);
    double arg1 = 0;
    double arg2 = 0;
    double arg3 = 0;

    packer.pack(buffer, sizeof(buffer), 13.37, -66.66, -123.45);
    packer.unpack(buffer, sizeof(buffer), &arg1, &arg2, &arg3);

    ASSERT_EQ(arg1, 13.37);
    ASSERT_EQ(arg2, -66.66);
    ASSERT_EQ(arg3, -123.45);
}

TEST_F(TestUnitArgumentPacker, TestPackUnpackIntArg1) {
    assert(sizeof(buffer) >= TUAP_BUFFER_SIZE);
    const int n = 1337;
    int arg = 0;

    packer.pack(buffer, sizeof(buffer), n);
    packer.unpack(buffer, sizeof(buffer), &arg);

    ASSERT_EQ(arg, n);
}

TEST_F(TestUnitArgumentPacker, RespectBufferLimitsArg1) {
    const size_t limit_bytes = sizeof(struct arg1_envelope_s);
    assert(sizeof(buffer) >= limit_bytes);
    set_buffer(buffer, sizeof(buffer));
    packer.pack(buffer, limit_bytes, 1234567.89);
    ASSERT_TRUE(is_buffer_intact(buffer, sizeof(buffer), limit_bytes));
}

TEST_F(TestUnitArgumentPacker, RespectBufferLimitsArg2) {
    const size_t limit_bytes = sizeof(struct arg2_envelope_s);
    assert(sizeof(buffer) >= limit_bytes);
    set_buffer(buffer, sizeof(buffer));
    packer.pack(buffer, limit_bytes, 1234567.89, -3.1337);
    ASSERT_TRUE(is_buffer_intact(buffer, sizeof(buffer), limit_bytes));
}

TEST_F(TestUnitArgumentPacker, RespectBufferLimitsArg3) {
    const size_t limit_bytes = sizeof(struct arg3_envelope_s);
    assert(sizeof(buffer) >= limit_bytes);
    set_buffer(buffer, sizeof(buffer));
    packer.pack(buffer, limit_bytes, 1234567.89, -3.1337, 0);
    ASSERT_TRUE(is_buffer_intact(buffer, sizeof(buffer), limit_bytes));
}

TEST_F(TestUnitArgumentPacker, RespectBufferLimitsIntArg1) {
    const size_t limit_bytes = sizeof(struct int_arg1_envelope_s);
    const int n = 1337;
    assert(sizeof(buffer) >= limit_bytes);
    set_buffer(buffer, sizeof(buffer));
    packer.pack(buffer, limit_bytes, n);
    ASSERT_TRUE(is_buffer_intact(buffer, sizeof(buffer), limit_bytes));
}
