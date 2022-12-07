.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    addi t0, x0, 1
    bge a0, t0, prologue
    li a0, 36
    j exit
    
prologue:
    addi sp, sp, -4
    sw s0, 0, sp

loop_start:
    addi s0, x0, 0        # use s0 as counter
    addi t0, a0, 0        # t0 = arr*
    addi t1, a1, 0        # t1 = arr_num

loop_continue:
    slli t2, s0, 2        
    add t2, t2, t0
    lw t3, 0, t2          # t3 = arr[i]
    blt t3, x0, negate
    sw t3, 0, t2
    addi s0, s0, 1        # s0 = s0 + 1
    blt s0, t1, loop_continue
    jal x0, loop_end

negate:
    addi t3, x0, 0
    sw t3, 0, t2
    addi s0, s0, 1        # s0 = s0 + 1
    blt s0, t1, loop_continue
    jal x0, loop_end

loop_end:
	# Epilogue
    lw s0, 0, sp
    addi sp, sp, 4
    
	ret
