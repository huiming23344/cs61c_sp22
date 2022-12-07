.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
	addi t0, x0, 1
	blt a2, t0, arr_length_error
	blt a3, t0, stride_length_error
	blt a4, t0, stride_length_error
	jal x0, prologue

	arr_length_error:
	li a0, 36
	j exit

stride_length_error:
	li a0, 37
	j exit

prologue:
	addi sp, sp, -8
	sw s0, 0, sp
	sw s1, 4, sp

loop_start:
	addi s0, x0, 0    # s0 = 0 counter
	addi s1, x0, 0    # s1 = 0 ans

loop:
	mul t0, s0, a3
	mul t1, s0, a4
	slli t0, t0, 2
	slli t1, t1, 2
	add t0, t0, a0
	add t1, t1, a1
	lw t2, 0, t0
	lw t3, 0, t1
	mul t4, t2, t3
	add s1, t4, s1
	addi s0, s0, 1
	blt s0, a2, loop
	jal x0, loop_end
	


loop_end:
	addi a0, s1, 0

	# Epilogue
	lw s1, 4, sp
	lw s0, 0, sp
	addi sp, sp, 8

	ret
