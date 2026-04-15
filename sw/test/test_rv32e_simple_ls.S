.section .text
.globl main

main:
    addi t0, sp, 0
    sw   t0, -4(sp)
    lw   t0, -4(sp)

    # switch to RV32E reliable
    addi a0, x0, 1      # rv32e
    addi a1, x0, 1      # reliability on
    addi sp, sp, -4
    sw   ra, 0(sp)
    call core_mode_switch
    lw   ra, 0(sp)
    addi sp, sp, 4
    
    # random instructions for debugging
    li t0, 0xDEADBEEE
    addi x13, t0, 1

    # return 0
    li a0, 0
    ret