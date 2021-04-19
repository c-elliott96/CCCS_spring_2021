	.data
buffer: .space 20
str1:  .asciiz "Enter string"
str2:  .asciiz "You wrote:\n"

	.text
__iter_over_string:
	la $s0, buffer	# load start address of 20b buffer
	lw $t0, ($s0) 	# load char at i = 0 of buffer into t0
	

	.globl main
main:
	la $a0, str1    # Load 
	li $v0, 4       #print string asking for string
	syscall

	;; # While loop bool
	;; li $s0, 1	# loop bool (is input not '\0') set to true

	;; # compare v0 to '\0'
	
	li $v0, 8       # get input

	la $a0, buffer  # load byte space into address
	li $a1, 20      # allot the byte space for string

	move $t0, $a0   # save string to t0
	syscall

	la $a0, str2    # load 
	li $v0, 4       # print "you wrote" string
	syscall

	la $a0, buffer  # reload byte space to primary address
	move $a0, $t0   # primary address = t0 address
	li $v0, 4       # print 
	syscall

	li $v0, 10      # end
	syscall
