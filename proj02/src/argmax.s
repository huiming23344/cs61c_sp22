.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    addi t0, x0, 1
    bge a1, t0, prologue
    li a0, 36
    j exit
    
prologue:
    addi sp, sp, -4
    sw s0 , 0, sp

loop_start:
    addi t0, a0, 0    # t0 = arr*
    addi t1, a1, 0    # t1 = arr_num
    addi t4, x0, 0    # t4 = 0 max_num for now
    addi t5, x0, 0    # t5 = 0 max_index
    addi s0, x0, 0    # s0 = 0 counter

loop_continue:
    slli t2, s0, 2
    add t2, t2, t0
    lw t3, 0, t2      # t3 = arr[i]
    blt t4, t3, update_max
    addi s0, s0, 1
    blt s0, t1, loop_continue
    jal x0, loop_end

update_max:
    addi t4, t3, 0
    addi t5, s0, 0
    addi s0, s0, 1
    blt s0, t1, loop_continue
    jal x0, loop_end

loop_end:
    addi a0, t5, 0
	# Epilogue
    lw s0, 0, sp
    addi sp, sp, 4 

	ret

