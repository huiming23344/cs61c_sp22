.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    addi t0, x0, 1                  # t0 = 1
    beq a0, t0, return1             # if x = 1 return 1
    # return factorial(n - 1)
    addi t0, a0, 0                  # t0 = n
    addi sp, sp, -8                 # push t0, ra to stack
    sw t0, 0, sp
    sw ra, 4, sp
    addi a0, a0, -1                 # a0 = n - 1
    jal ra, factorial               # a0 = factorial(n - 1)
    lw t0, 0, sp
    lw ra, 4, sp
    addi sp, sp, 8
    mul a0, a0, t0                  # a0 = n * factorial(n - 1)
    jr ra
return1:
    addi a0, x0, 1                  # a0 = 1       return 1
    jr ra