#include <stdint.h>
#include <stdbool.h>

#define LOG_LEVEL 0

#define LOW_BYTE 0
#define HIGH_BYTE 1

#define SEXT_11BITS 0x400
#define SEXT_9BITS  0x100
#define SEXT_8BITS  0x80
#define SEXT_6BITS  0x20
#define SEXT_5BITS  0x10

#define SHF_LSHFL 0
#define SHF_RSHFL 1
#define SHF_RSHFA 3

#define RETURN_REGISTER 7

#define IS_ZERO(x) ((bool)(((uint16_t)x) == 0))
#define IS_NEG(x) ((bool)(((((uint16_t)x) & 0x8000) >> 15) == 1))
#define IS_POS(x) (!IS_NEG(x))

#define SEXT(val, sig_ext) (((uint16_t)val) | (0 - (((uint16_t)val) & sig_ext)))
#define ZEXT(x) (((uint16_t)x) & 0x00FF)

#define LSHFT(reg, amt4) (((uint16_t)reg) << amt4)
#define RSHFTL(reg, amt4) (((uint16_t)reg) >> amt4)
#define RSHFTA(reg, amt4) (((int16_t)reg) >> amt4)

#define ADDR(x) (((uint16_t)x) >> 1)
#define SET_LOW_BYTE_MEM(x) (((uint16_t)x) & 0xFF)
#define SET_HI_BYTE_MEM(x) ((((uint16_t)x) & 0xFF00) >> 8)
#define SET_MEM(x) (((uint16_t)x) & 0xFF)

#define GET_N(x) ((((uint16_t)x) & 0x0800) >> 11)
#define GET_Z(x) ((((uint16_t)x) & 0x0400) >> 10)
#define GET_P(x) ((((uint16_t)x) & 0x0200) >> 9)

#define GET_LOW_BYTE_MEM(x) (((uint16_t)x) & 0xFF)
#define GET_HI_BYTE_MEM(x) ((((uint16_t)x) & 0xFF) << 8)
#define MASK_16_BITS(val) (((uint16_t)val) & 0xFFFF)
#define MASK_8_BITS(val) ((uint8_t)(((uint16_t)val) & 0xFF))

#define GET_IR_11_9(x) ((((uint16_t)x) & 0x0E00) >> 9)
#define GET_IR_8_6(x) ((((uint16_t)x) & 0x01C0) >> 6)
#define GET_IR_2_0(x) ((((uint16_t)x) & 0x0007) >> 0)
#define GET_IR_7_0(x) ((((uint16_t)x) & 0x00FF) >> 0)
#define GET_IR_5(x) ((((uint16_t)x) & 0x0020) >> 5)
#define GET_IR_11(x) ((((uint16_t)x) & 0x0800) >> 11)

#define GET_MAR_0(x) ((((uint16_t)x) & 0x0001) >> 0)

#define GET_SHF_TYPE(instr) ((((uint16_t)instr) & 0x0030) >> 4)

#define GET_IMM5(x) ((((uint16_t)x) & 0x001F) >> 0)
#define GET_AMOUNT4(instr) ((((uint16_t)instr) & 0x000f) >> 0)
#define GET_OFFSET6(x) ((((uint16_t)x) & 0x003F) >> 0)
#define GET_PCOFFSET9(x) ((((uint16_t)x) & 0x1FF) >> 0)
#define GET_PCOFFSET11(x) ((((uint16_t)x) & 0x7FF) >> 0)