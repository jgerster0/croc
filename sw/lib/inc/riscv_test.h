#ifndef _ENV_RISCV_TEST_H
#define _ENV_RISCV_TEST_H

#define RVTEST_RV32U \
    .macro init; \
    .endm

#define TESTNUM gp

// clang-format off
#define RVTEST_CODE_BEGIN \
    .section .text; \
    .align 2; \
    .globl main; \
    main: \
    lui t0, 0x10001; \
    sw ra, -4(t0); \
    li TESTNUM, 0; \
    init;

#define RVTEST_CODE_END unimp

#define RVTEST_PASS \
    fence; \
    li a0, 0; \
    lui t0, 0x10001; \
    lw ra, -4(t0); \
    ret

#define RVTEST_FAIL \
    fence; \
    1: beqz TESTNUM, 1b; \
    sll TESTNUM, TESTNUM, 1; \
    or TESTNUM, TESTNUM, 1; \
    mv a0, TESTNUM; \
    lui t0, 0x10001; \
    lw ra, -4(t0); \
    ret

#define EXTRA_DATA

#define RVTEST_DATA_BEGIN \
    EXTRA_DATA \
    .align 4; \
    .global begin_signature; \
    begin_signature:

#define RVTEST_DATA_END \
    .align 4; \
    .global end_signature; \
    end_signature:

#endif