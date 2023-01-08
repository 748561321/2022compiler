.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra

write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

func1:
  move $gp, $sp
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  lw $t0, -4($gp)
  lw $t1, 12($gp)
  addi $t0, $t1, 0
  sw $t0, -4($gp)
  lw $t2, -8($gp)
  lw $t3, 8($gp)
  addi $t2, $t3, 0
  sw $t2, -8($gp)
  lw $t4, -12($gp)
  lw $t5, -8($gp)
  lw $t6, -4($gp)
  mul $t4, $t6, $t5
  sw $t4, -12($gp)
  lw $t7, -16($gp)
  lw $s0, -12($gp)
  move $t7, $s0
  sw $t7, -16($gp)
  lw $s1, -20($gp)
  lw $s2, 12($gp)
  addi $s1, $s2, 4
  sw $s1, -20($gp)
  lw $s3, -24($gp)
  lw $s4, 8($gp)
  addi $s3, $s4, 4
  sw $s3, -24($gp)
  lw $s5, -12($gp)
  lw $s6, -24($gp)
  lw $s7, -20($gp)
  mul $s5, $s7, $s6
  sw $s5, -12($gp)
  lw $t8, -32($gp)
  lw $t9, -12($gp)
  move $t8, $t9
  sw $t8, -32($gp)
  lw $t0, -36($gp)
  lw $t1, -32($gp)
  lw $t2, -16($gp)
  add $t0, $t2, $t1
  sw $t0, -36($gp)
  lw $t3, -36($gp)
  move $v0, $t3
  jr $ra

func2:
  move $gp, $sp
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  lw $t0, -4($gp)
  li $t0, 0
  sw $t0, -4($gp)
label1:
  lw $t1, -4($gp)
  lw $t2, 8($gp)
  ble $t1, $t2, label2
  j label3
label2:
  lw $t3, -8($gp)
  lw $t4, -4($gp)
  lw $t5, -4($gp)
  mul $t3, $t5, $t4
  sw $t3, -8($gp)
  lw $t6, -12($gp)
  lw $t7, -8($gp)
  move $t6, $t7
  sw $t6, -12($gp)
  lw $s0, -16($gp)
  li $s0, 1
  sw $s0, -16($gp)
  lw $s1, -20($gp)
  lw $s2, -16($gp)
  lw $s3, -4($gp)
  add $s1, $s3, $s2
  sw $s1, -20($gp)
  lw $s4, -24($gp)
  li $s4, 1
  sw $s4, -24($gp)
  lw $s5, -28($gp)
  lw $s6, -24($gp)
  lw $s7, -4($gp)
  add $s5, $s7, $s6
  sw $s5, -28($gp)
  lw $t8, -8($gp)
  lw $t9, -28($gp)
  lw $t0, -20($gp)
  mul $t8, $t0, $t9
  sw $t8, -8($gp)
  lw $t1, -36($gp)
  lw $t2, -8($gp)
  move $t1, $t2
  sw $t1, -36($gp)
  lw $t3, -40($gp)
  li $t3, 0
  sw $t3, -40($gp)
  lw $t4, 8($gp)
  lw $t5, -12($gp)
  bge $t4, $t5, label7
  j label8
label7:
  lw $t6, -40($gp)
  li $t6, 1
  sw $t6, -40($gp)
label8:
  lw $t7, -40($gp)
  bne $t7, $0, label6
  j label5
label6:
  lw $s0, -48($gp)
  li $s0, 0
  sw $s0, -48($gp)
  lw $s1, 8($gp)
  lw $s2, -36($gp)
  blt $s1, $s2, label9
  j label10
label9:
  lw $s3, -48($gp)
  li $s3, 1
  sw $s3, -48($gp)
label10:
  lw $s4, -48($gp)
  bne $s4, $0, label4
  j label5
label4:
  lw $s5, -4($gp)
  move $v0, $s5
  jr $ra
label5:
  lw $s6, -56($gp)
  li $s6, 1
  sw $s6, -56($gp)
  lw $s7, -60($gp)
  lw $t8, -56($gp)
  lw $t9, -4($gp)
  add $s7, $t9, $t8
  sw $s7, -60($gp)
  lw $t0, -4($gp)
  lw $t1, -60($gp)
  move $t0, $t1
  sw $t0, -4($gp)
  j label1
label3:
  lw $t2, -68($gp)
  li $t2, 1
  sw $t2, -68($gp)
  lw $t3, -72($gp)
  lw $t4, -68($gp)
  sub $t3, $0, $t4
  sw $t3, -72($gp)
  lw $t5, -72($gp)
  move $v0, $t5
  jr $ra

func3:
  move $gp, $sp
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  lw $t0, -4($gp)
  addi $sp, $sp, -72
  sw $t0, 0($sp)
  sw $t1, 4($sp)
  sw $t2, 8($sp)
  sw $t3, 12($sp)
  sw $t4, 16($sp)
  sw $t5, 20($sp)
  sw $t6, 24($sp)
  sw $t7, 28($sp)
  sw $s0, 32($sp)
  sw $s1, 36($sp)
  sw $s2, 40($sp)
  sw $s3, 44($sp)
  sw $s4, 48($sp)
  sw $s5, 52($sp)
  sw $s6, 56($sp)
  sw $s7, 60($sp)
  sw $t8, 64($sp)
  sw $t9, 68($sp)
  addi $sp, $sp, -8
  lw $t1, 8($gp)
  sw $t1, 0($sp)
  lw $t2, 12($gp)
  sw $t2, 4($sp)
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $gp, 4($sp)
  jal func1
  move $sp, $gp
  lw $ra, 0($sp)
  lw $gp, 4($sp)
  addi $sp, $sp, 16
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  lw $t2, 8($sp)
  lw $t3, 12($sp)
  lw $t4, 16($sp)
  lw $t5, 20($sp)
  lw $t6, 24($sp)
  lw $t7, 28($sp)
  lw $s0, 32($sp)
  lw $s1, 36($sp)
  lw $s2, 40($sp)
  lw $s3, 44($sp)
  lw $s4, 48($sp)
  lw $s5, 52($sp)
  lw $s6, 56($sp)
  lw $s7, 60($sp)
  lw $t8, 64($sp)
  lw $t9, 68($sp)
  addi $sp, $sp, 72
  move $t0, $v0
  sw $t0, -4($gp)
  lw $t3, -8($gp)
  lw $t4, -4($gp)
  move $t3, $t4
  sw $t3, -8($gp)
  lw $t5, -12($gp)
  addi $sp, $sp, -72
  sw $t0, 0($sp)
  sw $t1, 4($sp)
  sw $t2, 8($sp)
  sw $t3, 12($sp)
  sw $t4, 16($sp)
  sw $t5, 20($sp)
  sw $t6, 24($sp)
  sw $t7, 28($sp)
  sw $s0, 32($sp)
  sw $s1, 36($sp)
  sw $s2, 40($sp)
  sw $s3, 44($sp)
  sw $s4, 48($sp)
  sw $s5, 52($sp)
  sw $s6, 56($sp)
  sw $s7, 60($sp)
  sw $t8, 64($sp)
  sw $t9, 68($sp)
  addi $sp, $sp, -4
  lw $t6, -8($gp)
  sw $t6, 0($sp)
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $gp, 4($sp)
  jal func2
  move $sp, $gp
  lw $ra, 0($sp)
  lw $gp, 4($sp)
  addi $sp, $sp, 12
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  lw $t2, 8($sp)
  lw $t3, 12($sp)
  lw $t4, 16($sp)
  lw $t5, 20($sp)
  lw $t6, 24($sp)
  lw $t7, 28($sp)
  lw $s0, 32($sp)
  lw $s1, 36($sp)
  lw $s2, 40($sp)
  lw $s3, 44($sp)
  lw $s4, 48($sp)
  lw $s5, 52($sp)
  lw $s6, 56($sp)
  lw $s7, 60($sp)
  lw $t8, 64($sp)
  lw $t9, 68($sp)
  addi $sp, $sp, 72
  move $t5, $v0
  sw $t5, -12($gp)
  lw $t7, -12($gp)
  move $v0, $t7
  jr $ra

main:
  move $gp, $sp
  addi $sp, $sp, -4
  addi $sp, $sp, -40
  sw $sp, -4($sp)
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  lw $t0, -4($gp)
  li $t0, 2
  sw $t0, -4($gp)
  lw $t1, -52($gp)
  li $t1, 0
  sw $t1, -52($gp)
  lw $t2, -56($gp)
  li $t2, 0
  sw $t2, -56($gp)
label11:
  lw $t3, -60($gp)
  li $t3, 2
  sw $t3, -60($gp)
  lw $t4, -52($gp)
  lw $t5, -60($gp)
  blt $t4, $t5, label12
  j label13
label12:
  lw $t6, -64($gp)
  li $t6, 0
  sw $t6, -64($gp)
  lw $t7, -56($gp)
  lw $s0, -64($gp)
  move $t7, $s0
  sw $t7, -56($gp)
label14:
  lw $s1, -72($gp)
  li $s1, 2
  sw $s1, -72($gp)
  lw $s2, -56($gp)
  lw $s3, -72($gp)
  blt $s2, $s3, label15
  j label16
label15:
  lw $s4, -76($gp)
  li $s5, 20
  lw $s6, -52($gp)
  mul $s4, $s6, $s5
  sw $s4, -76($gp)
  lw $s7, -80($gp)
  lw $t8, -76($gp)
  lw $t9, -48($gp)
  add $s7, $t9, $t8
  sw $s7, -80($gp)
  lw $s5, -84($gp)
  lw $t0, -80($gp)
  addi $s5, $t0, 4
  sw $s5, -84($gp)
  lw $t1, -88($gp)
  li $t2, 8
  lw $t3, -56($gp)
  mul $t1, $t3, $t2
  sw $t1, -88($gp)
  lw $t2, -92($gp)
  lw $t4, -88($gp)
  lw $t5, -84($gp)
  add $t2, $t5, $t4
  sw $t2, -92($gp)
  lw $t6, -96($gp)
  lw $t7, -92($gp)
  addi $t6, $t7, 0
  sw $t6, -96($gp)
  lw $s0, -100($gp)
  lw $s1, -56($gp)
  lw $s2, -52($gp)
  mul $s0, $s2, $s1
  sw $s0, -100($gp)
  lw $s3, -104($gp)
  lw $s4, -56($gp)
  lw $s6, -100($gp)
  add $s3, $s6, $s4
  sw $s3, -104($gp)
  lw $s7, -96($gp)
  lw $t8, -104($gp)
  move $s7, $t8
  sw $s7, -96($gp)
  lw $t9, -112($gp)
  li $s5, 20
  lw $t0, -52($gp)
  mul $t9, $t0, $s5
  sw $t9, -112($gp)
  lw $s5, -116($gp)
  lw $t1, -112($gp)
  lw $t3, -48($gp)
  add $s5, $t3, $t1
  sw $s5, -116($gp)
  lw $t2, -120($gp)
  lw $t4, -116($gp)
  addi $t2, $t4, 4
  sw $t2, -120($gp)
  lw $t5, -124($gp)
  li $t6, 8
  lw $t7, -56($gp)
  mul $t5, $t7, $t6
  sw $t5, -124($gp)
  lw $t6, -128($gp)
  lw $s0, -124($gp)
  lw $s1, -120($gp)
  add $t6, $s1, $s0
  sw $t6, -128($gp)
  lw $s2, -132($gp)
  lw $s3, -128($gp)
  addi $s2, $s3, 4
  sw $s2, -132($gp)
  lw $s4, -136($gp)
  lw $s6, -52($gp)
  lw $s7, -52($gp)
  mul $s4, $s7, $s6
  sw $s4, -136($gp)
  lw $t8, -140($gp)
  lw $t9, -56($gp)
  lw $t0, -136($gp)
  mul $t8, $t0, $t9
  sw $t8, -140($gp)
  lw $s5, -144($gp)
  lw $t1, -56($gp)
  lw $t3, -140($gp)
  add $s5, $t3, $t1
  sw $s5, -144($gp)
  lw $t2, -132($gp)
  lw $t4, -144($gp)
  move $t2, $t4
  sw $t2, -132($gp)
  lw $t5, -152($gp)
  li $t5, 1
  sw $t5, -152($gp)
  lw $t7, -156($gp)
  lw $t6, -152($gp)
  lw $s0, -56($gp)
  add $t7, $s0, $t6
  sw $t7, -156($gp)
  lw $s1, -56($gp)
  lw $s2, -156($gp)
  move $s1, $s2
  sw $s1, -56($gp)
  j label14
label16:
  lw $s3, -164($gp)
  li $s4, 20
  lw $s6, -52($gp)
  mul $s3, $s6, $s4
  sw $s3, -164($gp)
  lw $s4, -168($gp)
  lw $s7, -164($gp)
  lw $t8, -48($gp)
  add $s4, $t8, $s7
  sw $s4, -168($gp)
  lw $t9, -172($gp)
  lw $t0, -168($gp)
  addi $t9, $t0, -12
  sw $t9, -172($gp)
  lw $s5, -176($gp)
  li $t1, 20
  lw $t3, -52($gp)
  mul $s5, $t3, $t1
  sw $s5, -176($gp)
  lw $t1, -180($gp)
  lw $t2, -176($gp)
  lw $t4, -48($gp)
  add $t1, $t4, $t2
  sw $t1, -180($gp)
  lw $t5, -184($gp)
  lw $t7, -180($gp)
  addi $t5, $t7, 4
  sw $t5, -184($gp)
  lw $t6, -188($gp)
  li $t6, 0
  sw $t6, -188($gp)
  lw $s0, -192($gp)
  li $s1, 8
  lw $s2, -188($gp)
  mul $s0, $s2, $s1
  sw $s0, -192($gp)
  lw $s1, -196($gp)
  lw $s3, -192($gp)
  lw $s6, -184($gp)
  add $s1, $s6, $s3
  sw $s1, -196($gp)
  lw $s4, -200($gp)
  li $s7, 20
  lw $t8, -52($gp)
  mul $s4, $t8, $s7
  sw $s4, -200($gp)
  lw $s7, -204($gp)
  lw $t9, -200($gp)
  lw $t0, -48($gp)
  add $s7, $t0, $t9
  sw $s7, -204($gp)
  lw $s5, -208($gp)
  lw $t3, -204($gp)
  addi $s5, $t3, 4
  sw $s5, -208($gp)
  lw $t1, -212($gp)
  li $t1, 1
  sw $t1, -212($gp)
  lw $t2, -216($gp)
  li $t4, 8
  lw $t5, -212($gp)
  mul $t2, $t5, $t4
  sw $t2, -216($gp)
  lw $t4, -220($gp)
  lw $t7, -216($gp)
  lw $t6, -208($gp)
  add $t4, $t6, $t7
  sw $t4, -220($gp)
  lw $s0, -224($gp)
  addi $sp, $sp, -72
  sw $t0, 0($sp)
  sw $t1, 4($sp)
  sw $t2, 8($sp)
  sw $t3, 12($sp)
  sw $t4, 16($sp)
  sw $t5, 20($sp)
  sw $t6, 24($sp)
  sw $t7, 28($sp)
  sw $s0, 32($sp)
  sw $s1, 36($sp)
  sw $s2, 40($sp)
  sw $s3, 44($sp)
  sw $s4, 48($sp)
  sw $s5, 52($sp)
  sw $s6, 56($sp)
  sw $s7, 60($sp)
  sw $t8, 64($sp)
  sw $t9, 68($sp)
  addi $sp, $sp, -8
  lw $s2, -220($gp)
  sw $s2, 0($sp)
  lw $s1, -196($gp)
  sw $s1, 4($sp)
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $gp, 4($sp)
  jal func3
  move $sp, $gp
  lw $ra, 0($sp)
  lw $gp, 4($sp)
  addi $sp, $sp, 16
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  lw $t2, 8($sp)
  lw $t3, 12($sp)
  lw $t4, 16($sp)
  lw $t5, 20($sp)
  lw $t6, 24($sp)
  lw $t7, 28($sp)
  lw $s0, 32($sp)
  lw $s1, 36($sp)
  lw $s2, 40($sp)
  lw $s3, 44($sp)
  lw $s4, 48($sp)
  lw $s5, 52($sp)
  lw $s6, 56($sp)
  lw $s7, 60($sp)
  lw $t8, 64($sp)
  lw $t9, 68($sp)
  addi $sp, $sp, 72
  move $s0, $v0
  sw $s0, -224($gp)
  lw $s3, -172($gp)
  lw $s6, -224($gp)
  move $s3, $s6
  sw $s3, -172($gp)
  lw $s4, -232($gp)
  li $s4, 1
  sw $s4, -232($gp)
  lw $t8, -236($gp)
  lw $s7, -232($gp)
  lw $t9, -52($gp)
  add $t8, $t9, $s7
  sw $t8, -236($gp)
  lw $t0, -52($gp)
  lw $s5, -236($gp)
  move $t0, $s5
  sw $t0, -52($gp)
  j label11
label13:
  lw $t3, -244($gp)
  li $t3, 0
  sw $t3, -244($gp)
  lw $t1, -248($gp)
  li $t2, 20
  lw $t5, -244($gp)
  mul $t1, $t5, $t2
  sw $t1, -248($gp)
  lw $t2, -252($gp)
  lw $t4, -248($gp)
  lw $t7, -48($gp)
  add $t2, $t7, $t4
  sw $t2, -252($gp)
  lw $t6, -256($gp)
  lw $s0, -252($gp)
  addi $t6, $s0, -12
  sw $t6, -256($gp)
  lw $s2, -260($gp)
  li $s2, 1
  sw $s2, -260($gp)
  lw $s1, -264($gp)
  li $s3, 20
  lw $s6, -260($gp)
  mul $s1, $s6, $s3
  sw $s1, -264($gp)
  lw $s3, -268($gp)
  lw $s4, -264($gp)
  lw $t8, -48($gp)
  add $s3, $t8, $s4
  sw $s3, -268($gp)
  lw $s7, -272($gp)
  lw $t9, -268($gp)
  addi $s7, $t9, -12
  sw $s7, -272($gp)
  lw $t0, -276($gp)
  lw $s5, -272($gp)
  lw $t3, -256($gp)
  add $t0, $t3, $s5
  sw $t0, -276($gp)
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $t1, -276($gp)
  move $a0, $t1
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $t5, -280($gp)
  li $t5, 0
  sw $t5, -280($gp)
  lw $t2, -280($gp)
  move $v0, $t2
  jr $ra
