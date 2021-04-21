.text

main:
	li 	$t1, 0
	la 	$a0, input_message
	li 	$v0, 4
	syscall

	li 	$v0, 8 		# string_input syscall
	la 	$a0, buffer
	li 	$a1, 20
	move 	$t0, $a0
	syscall

loop:
	lb   	$a0, 0($t0)
	beqz 	$a0, exit_loop
	addi 	$t0, $t0, 1
	addi 	$t1, $t1, 1
	j     	loop
	
exit_loop:
	la	$a0, print_message1
	li	$v0, 4
	syscall
	
	li   	$v0, 1
	li 	$t2, -1		# chop off captured carriage return from [enter]
	add  	$a0, $t2, $t1
	syscall

	la	$a0, print_message2
	li	$v0, 4
	syscall

	li   	$v0, 10
	syscall
	
.data
	
input_message: 	.asciiz "Give me a string: "
print_message1:	.asciiz	"Your input was "
print_message2:	.asciiz " characters long.\n"
buffer: 	.space 20 	# cannot handle string longer than 19 chars
