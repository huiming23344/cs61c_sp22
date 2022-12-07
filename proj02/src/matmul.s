.import ../src/dot.s
.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:
	addi t0, x0, 1
	blt a1, t0, return_error_code
	blt a2, t0, return_error_code
	blt a4, t0, return_error_code
	blt a5, t0, return_error_code
	bne a2, a4, return_error_code
	jal x0, prologue

return_error_code:
	li a0, 38
	j exit

prologue:
	addi sp, sp, -12
	sw s0, 0, sp
	sw s1, 4, sp
	sw s2, 8, sp

outer_loop_start:
	addi s0, x0, 0     # the row counter

outer_loop:
inner_loop_start:
	addi s1, x0, 0     # the colunm counter
	
inner_loop:
	# Prologue
	addi sp, sp, -32
	sw a0, 0, sp
	sw a1, 4, sp
	sw a2, 8, sp
	sw a3, 12, sp
	sw a4, 16, sp
	sw a5, 20, sp
	sw a6, 24, sp
	sw ra, 28, sp
	# prepare the parameters
	mul a0, s0, a2
	slli a0, a0, 2
	lw s2, 0, ,sp
	add a0, a0, s2
	slli a1, s1, 2
	lw s2, 12, sp
	add a1, s2, a1
	lw a2, 16, sp
	li a3, 1
	lw a4, 20, sp
	# call dot
	jal ra dot
	# store the result
	lw t0, 20, sp
	mul s2, s0, t0
	slli s2, s2, 2
	lw t0, 24, sp
	add s2, s2, t0
	slli t0, s1, 2
	add s2, t0, s2
	sw a0, 0, s2
	# Epilogue
	lw a0, 0, sp
	lw a1, 4, sp
	lw a2, 8, sp
	lw a3, 12, sp
	lw a4, 16, sp
	lw a5, 20, sp
	lw a6, 24, sp
	lw ra, 28, sp
	addi sp, sp, 32
	addi s1, s1, 1
	beq s1, a5, inner_loop_end
	jal x0, inner_loop

inner_loop_end:
	addi s0, s0, 1
	beq s0, a1, outer_loop_end
	jal x0, outer_loop

outer_loop_end:
	# Epilogue
	lw s0, 0, sp
	lw s1, 4, sp
	lw s2, 8, sp
	addi sp, sp, 12
	ret
