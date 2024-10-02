.data
asize0:  .word    4,  4,  2, 2    #i, j, k, l
frame0:  .word    0,  0,  0,  0, 
         .word    0,  0,  0,  0,
         .word    0,  1,  2,  0,
         .word    0,  3,  4,  0, 
window0: .word    1,  2, 
         .word    3,  4, 
         
         
newline: .asciiz     "\n" 
bracket_1: .asciiz     "[" 
bracket_2: .asciiz     "]" 
comma: .asciiz     "," 
match: .asciiz "Match at "


.text

.globl main

main:

la $a0,asize0
la $a1,frame0
la $a2,window0

lw $s0,0($a0)#i
lw $s1,4($a0)#j
lw $s2,8($a0)#k
lw $s3,12($a0)#l

la $a1,frame0
la $t5,($a1)


li $t0,0
li $t1,0
li $t2,0
li $t3,0
li $t4,0
li $t6,0
li $t7,0
li $t8,0
li $t9,0




start_again:
beq $s0,$s2,ending_program


jal print_newline


li $t0,0
li $t1,0
li $t2,0
li $t4,0
li $t5,0
li $t6,0
li $t7,0
li $t8,0


move $t0,$zero
sub $t1,$s0,$s2

j iterate_rightF
next_one2:

jal print_newline





li $t0,0
li $t1,0
li $t2,0
li $t4,0
li $t5,0
li $t6,0
li $t7,0
li $t8,0


move $t1,$zero
sub $t0,$s1,$s3

j iterate_down
next_one3:



jal print_newline





li $t0,0
li $t1,0
li $t2,0
li $t4,0
li $t5,0
li $t6,0
li $t7,0
li $t8,0


sub $t1,$s0,$s2



j iterate_left
next_one4:

jal print_newline

sub $s0,$s0,$s2
sub $s1,$s1,$s3

li $t0,0
li $t1,0
li $t2,0
li $t4,0
li $t5,0
li $t6,0
li $t7,0
li $t8,0


sub $t0,$s1,$s3



j iterate_up
next_one5:

jal print_newline
add $t3,$t3,$s3
add $t9,$t9,$s2

j start_again

ending_program:






j program_end




#move $t0,$zero
#move $t1,$s3




#move $t0,$zero
#sub $t1,$s0,$s2

iterate_rightF:
bgt $t0,$t1,leave_right
li $t4,0 #intialize #t4
add $t4,$t4,$a0  #store rgister offset value to t4
li $t6,0
la $s5,($a2)
loop_F1:
beq  $t6,$s2,exit_i1
li $t7,0
loopj1:
beq $t7,$s3,jend1
#increments j by whatever framesize and getting 4 bites then adding it to t4 to offset
lw $s4,0($s5)
add $v0,$v0,$s4
lw $s4,0($t4)
sub $v0,$v0,$s4
move $t8,$s0
mul $t8,$t8,4
add $t4,$t4,$t8
move $t8,$s2
mul $t8,$t8,4
add $s5,$s5,$t8
addi $t7,$t7,1
j loopj1
jend1:
move $t8,$s0
mul $t8,$t8,4
mul $t8,$t8,$s3
addi $t8,$t8,-4
sub $t4,$t4,$t8
move $t8,$s2
mul $t8,$t8,4
mul $t8,$t8,$s3
addi $t8,$t8,-4
sub $s5,$s5,$t8
li $t8,0
addi $t6,$t6,1
j loop_F1
exit_i1:
la $t5,($a0)
jal print_vo1
la $a0,($t5)
add $a0,$a0,4
addi $t0,$t0,1 
addi $t9,$t9,1  
j iterate_rightF
leave_right:
addi $t9,$t9,-1
j next_one2

#move $t0,$zero
#sub $t1,$s1,$s3

iterate_down:
bgt $t1,$t0,leave_down
li $t4,0 #intialize #t4
add $t4,$t4,$a0  #store rgister offset value to t4
li $t6,0
la $s5,($a2)
loop_F2:
beq  $t6,$s2,exit_i2
li $t7,0
loopj2:
beq $t7,$s3,jend2
#increments j by whatever framesize and getting 4 bites then adding it to t4 to offset
lw $s4,0($s5)
add $v0,$v0,$s4
lw $s4,0($t4)
sub $v0,$v0,$s4
move $t8,$s0
mul $t8,$t8,4
add $t4,$t4,$t8
move $t8,$s2
mul $t8,$t8,4
add $s5,$s5,$t8
addi $t7,$t7,1
j loopj2
jend2:
move $t8,$s0
mul $t8,$t8,4
mul $t8,$t8,$t7
addi $t8,$t8,-4
sub $t4,$t4,$t8
move $t8,$s2
mul $t8,$t8,4
mul $t8,$t8,$t7
addi $t8,$t8,-4
sub $s5,$s5,$t8
li $t8,0
addi $t6,$t6,1
j loop_F2
exit_i2:
la $t5,($a0)
jal print_vo1
la $a0,($t5)
move $t5,$s0
mul $t5,$t5,4
add $a0,$a0,$t5
la $t5,($a0)
addi $t1,$t1,1  
addi $t3,$t3,1 
j iterate_down
leave_down:
j next_one3

#mub $t0,$s0,$s2
#sub $t1,$s1,$s3

iterate_left:
bltz  $t1,leave_left
li $t4,0 #intialize #t4
add $t4,$t4,$a0  #store rgister offset value to t4
li $t6,0
la $s5,($a2)
loop_F3:
beq  $t6,$s2,exit_i3
li $t7,0
loopj3:
beq $t7,$s3,jend3
#increments j by whatever framesize and getting 4 bites then adding it to t4 to offset
lw $s4,0($s5)
add $v0,$v0,$s4
lw $s4,0($t4)
sub $v0,$v0,$s4
move $t8,$s0
mul $t8,$t8,4
add $t4,$t4,$t8
move $t8,$s2
mul $t8,$t8,4
add $s5,$s5,$t8
addi $t7,$t7,1
j loopj3
jend3:
move $t8,$s0
mul $t8,$t8,4
mul $t8,$t8,$s3
addi $t8,$t8,-4
sub $t4,$t4,$t8
move $t8,$s2
mul $t8,$t8,4
mul $t8,$t8,$s3
addi $t8,$t8,-4
sub $s5,$s5,$t8
li $t8,0
addi $t6,$t6,1
j loop_F3
exit_i3:
la $t5,($a0)
jal print_vo1
la $a0,($t5)
add $a0,$a0,-4
addi $t1,$t1,-1  
sub $t9,$t9,1 
j iterate_left
leave_left:
j next_one4


#mub $t0,$s1,$s3
#sub $t1,$s1,$s3

iterate_up:
bltz $t0,leave_up
li $t4,0 #intialize #t4
add $t4,$t4,$a0  #store rgister offset value to t4
li $t6,0
la $s5,($a2)
loop_F4:
beq  $t6,$s2,exit_i4
li $t7,0
loopj4:
beq $t7,$s3,jend4
#increments j by whatever framesize and getting 4 bites then adding it to t4 to offset
lw $s4,0($s5)
add $v0,$v0,$s4
lw $s4,0($t4)
sub $v0,$v0,$s4
move $t8,$s0
mul $t8,$t8,4
add $t4,$t4,$t8
move $t8,$s2
mul $t8,$t8,4
add $s5,$s5,$t8
addi $t7,$t7,1
j loopj4
jend4:
move $t8,$s0
mul $t8,$t8,4
mul $t8,$t8,$s3
addi $t8,$t8,-4
sub $t4,$t4,$t8
move $t8,$s2
mul $t8,$t8,4
mul $t8,$t8,$s3
addi $t8,$t8,-4
sub $s5,$s5,$t8
li $t8,0
addi $t6,$t6,1
j loop_F4
exit_i4:
la $t5,($a0)
jal print_vo1
la $a0,($t5)
mul $t2,$s0,$s1
sub $a0,$a0,$t2
addi $t0,$t0,-1  
sub $t3,$t3,1
j iterate_up
leave_up:
j next_one5





#next iteration

print_newline:

la $s6,newline
move $a0,$s6
li $v0,4
syscall
la $a0,($t5)
li $v0,0

jr $ra

print_vo1:
beqz $v0,print_match
move $s4,$v0
la $s6,bracket_1
move $a0,$s6
li $v0,4
syscall
move $v0,$s4
move $a0,$v0
li $v0,1
syscall
la $s6,bracket_2
move $a0,$s6
li $v0,4
syscall
la $a0,($t5)
li $v0,0
jr $ra


print_voW:
move $s4,$v0
move $v1,$v0
la $s6,window0
move $a0,$s6
li $v0,4
syscall
la $s6,bracket_1
move $a0,$s6
li $v0,4
syscall
move $v0,$s4
move $a0,$v0
li $v0,1
syscall
la $a0,asize0
li $v0,0
la $s6,bracket_2
move $a0,$s6
li $v0,4
syscall
la $s6,newline
move $a0,$s6
li $v0,4
syscall
la $a0,($t5)
li $v0,0
jr $ra


print_match:


la $s6,newline
move $a0,$s6
li $v0,4
syscall
la $s6,match
move $a0,$s6
li $v0,4
syscall
la $s6,bracket_1
move $a0,$s6
li $v0,4
syscall
move $a0,$t3
li $v0,1
syscall
la $s6,comma
move $a0,$s6
li $v0,4
syscall
move $a0,$t9
li $v0,1
syscall
la $s6,bracket_2
move $a0,$s6
li $v0,4
syscall

li $s6,0
li $a1,0




j program_end




program_end:
li $v0,10
syscall
  
 
    
    
    
    
