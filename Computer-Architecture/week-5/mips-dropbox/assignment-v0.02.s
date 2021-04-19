	.data
buffer:	.space 20
str_1:	.asciiz "Give input:"
str_2:	.asciiz "You entered: "
null_char:	.byte	'\0'
str_3:	.asciiz "We found a null!\n"
str_4:	.asciiz "No null here...\n"

	.text
__t1_eq_null_char:
	la	$a0, str_3
	li	$v0, 4
	syscall

	jr	$ra
__store_str_mem:
	# assuming string addr to be stored in s0
	move	$t0, $a0	# load first char of string in t0
	lb	$t1, null_char	# load '\0' into t1

	li	$s1, 0		# load false into s1 for branching
	
	
__get_str_input:
	la	$a0, str_1	# load str_1 address to s0
	li	$v0, 4		# load print_string opcode
	syscall			# print string
	
	li 	$v0, 8		# set up read string syscall
				# expects a0 to be read buffer address
				# expects a1 to be buffer read length (reads up
				# to n-1 chars w/ null char OR if fewer than n-1 chars are 
				# given reads up to newline and null terminates)
	la 	$a0, buffer 	# loads address of data variable "buffer"
	li 	$a1, 20		# tells read string syscall to read <= 19 chars
	move 	$t0, $a0	# save string address to t0
	syscall			# get input

	# test t0 has string
	la 	$a0, buffer
	move	$a0, $t0
	li	$v0, 4
	syscall
	sw 	$v0, buffer	# store result of input in buffer

	la	$a0, str_2	# load second output string
	li	$v0, 4		# setup syscall to print string
	syscall			# run print string

	la	$a0, buffer	# reload buffer address
	move 	$a0, $t0	# replace a0 with string address
	li 	$v0, 4		# set up print_string syscall
	syscall			# print input string

	# return to main
	jr 	$ra

	.globl main

main:
	# invoke __get_str_input
	jal __get_str_input

	# exit
	li $v0, 10
	syscall
