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
  li $t0, 0
  sw $t0, -4($gp)
  lw $t1, -8($gp)
  li $t1, 3
  sw $t1, -8($gp)
  lw $t2, -12($gp)
  li $t2, 0
  sw $t2, -12($gp)
label1:
  lw $t3, -4($gp)
  lw $t4, -8($gp)
  blt $t3, $t4, label2
  j label3
label2:
  lw $t5, -16($gp)
  li $t6, 4
  lw $t7, -4($gp)
  mul $t5, $t7, $t6
  sw $t5, -16($gp)
  lw $s0, -20($gp)
  lw $s1, -16($gp)
  lw $s2, 8($gp)
  add $s0, $s2, $s1
  sw $s0, -20($gp)
  lw $s3, -24($gp)
  li $s3, 1
  sw $s3, -24($gp)
  lw $s4, -28($gp)
  lw $s5, -24($gp)
  lw $s6, -4($gp)
  add $s4, $s6, $s5
  sw $s4, -28($gp)
  lw $s7, -32($gp)
  li $t8, 4
  lw $t9, -28($gp)
  mul $s7, $t9, $t8
  sw $s7, -32($gp)
  lw $t0, -36($gp)
  lw $t1, -32($gp)
  lw $t2, 8($gp)
  add $t0, $t2, $t1
  sw $t0, -36($gp)
  lw $t3, -40($gp)
  lw $t4, -20($gp)
  lw $t3, 0($t4)
  sw $t3, -40($gp)
  lw $t5, -44($gp)
  lw $t6, -36($gp)
  lw $t5, 0($t6)
  sw $t5, -44($gp)
  lw $t7, -40($gp)
  lw $s0, -44($gp)
  bgt $t7, $s0, label4
  j label5
label4:
  lw $s1, -48($gp)
  li $s1, 1
  sw $s1, -48($gp)
  lw $s2, -52($gp)
  lw $s3, -48($gp)
  lw $s4, -4($gp)
  add $s2, $s4, $s3
  sw $s2, -52($gp)
  lw $s5, -56($gp)
  li $s6, 4
  lw $s7, -52($gp)
  mul $s5, $s7, $s6
  sw $s5, -56($gp)
  lw $t8, -60($gp)
  lw $t9, -56($gp)
  lw $t0, 8($gp)
  add $t8, $t0, $t9
  sw $t8, -60($gp)
  lw $t1, -64($gp)
  li $t2, 4
  lw $t3, -4($gp)
  mul $t1, $t3, $t2
  sw $t1, -64($gp)
  lw $t4, -68($gp)
  lw $t5, -64($gp)
  lw $t6, 8($gp)
  add $t4, $t6, $t5
  sw $t4, -68($gp)
  lw $t7, -72($gp)
  lw $s0, -68($gp)
  lw $t7, 0($s0)
  sw $t7, -72($gp)
  lw $s1, -60($gp)
  lw $s2, -72($gp)
  sw $s2, 0($s1)
  lw $s3, -76($gp)
  li $s3, 1
  sw $s3, -76($gp)
  lw $s4, -80($gp)
  lw $s5, -76($gp)
  lw $s6, -4($gp)
  add $s4, $s6, $s5
  sw $s4, -80($gp)
  lw $s7, -84($gp)
  li $t8, 4
  lw $t9, -80($gp)
  mul $s7, $t9, $t8
  sw $s7, -84($gp)
  lw $t0, -88($gp)
  lw $t1, -84($gp)
  lw $t2, 8($gp)
  add $t0, $t2, $t1
  sw $t0, -88($gp)
  lw $t3, -92($gp)
  li $t4, 4
  lw $t5, -4($gp)
  mul $t3, $t5, $t4
  sw $t3, -92($gp)
  lw $t6, -96($gp)
  lw $t7, -92($gp)
  lw $s0, 8($gp)
  add $t6, $s0, $t7
  sw $t6, -96($gp)
  lw $s1, -100($gp)
  li $s1, 2
  sw $s1, -100($gp)
  lw $s2, -104($gp)
  lw $s3, -100($gp)
  lw $s4, -4($gp)
  add $s2, $s4, $s3
  sw $s2, -104($gp)
  lw $s5, -108($gp)
  li $s6, 4
  lw $s7, -104($gp)
  mul $s5, $s7, $s6
  sw $s5, -108($gp)
  lw $t8, -112($gp)
  lw $t9, -108($gp)
  lw $t0, 8($gp)
  add $t8, $t0, $t9
  sw $t8, -112($gp)
  lw $t1, -116($gp)
  lw $t2, -96($gp)
  lw $t1, 0($t2)
  sw $t1, -116($gp)
  lw $t3, -120($gp)
  lw $t4, -112($gp)
  lw $t3, 0($t4)
  sw $t3, -120($gp)
  lw $t5, -124($gp)
  lw $t6, -120($gp)
  lw $t7, -116($gp)
  add $t5, $t7, $t6
  sw $t5, -124($gp)
  lw $s0, -88($gp)
  lw $s1, -124($gp)
  sw $s1, 0($s0)
label5:
  lw $s2, -128($gp)
  li $s2, 1
  sw $s2, -128($gp)
  lw $s3, -132($gp)
  lw $s4, -128($gp)
  lw $s5, -4($gp)
  add $s3, $s5, $s4
  sw $s3, -132($gp)
  lw $s6, -4($gp)
  lw $s7, -132($gp)
  move $s6, $s7
  sw $s6, -4($gp)
  j label1
label3:
  lw $t8, -12($gp)
  move $v0, $t8
  jr $ra

func2:
  move $gp, $sp
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  lw $t0, -4($gp)
  lw $t1, 8($gp)
  lw $t2, 12($gp)
  div $t2, $t1
  mflo $t0
  sw $t0, -4($gp)
  lw $t3, -8($gp)
  lw $t4, -4($gp)
  move $t3, $t4
  sw $t3, -8($gp)
  lw $t5, -4($gp)
  lw $t6, 8($gp)
  lw $t7, -8($gp)
  mul $t5, $t7, $t6
  sw $t5, -4($gp)
  lw $s0, -16($gp)
  lw $s1, -4($gp)
  move $s0, $s1
  sw $s0, -16($gp)
  lw $s2, -4($gp)
  lw $s3, -16($gp)
  lw $s4, 12($gp)
  sub $s2, $s4, $s3
  sw $s2, -4($gp)
  lw $s5, -24($gp)
  lw $s6, -4($gp)
  move $s5, $s6
  sw $s5, -24($gp)
  lw $s7, -24($gp)
  move $v0, $s7
  jr $ra

main:
  move $gp, $sp
  addi $sp, $sp, -4
  addi $sp, $sp, -36
  sw $sp, -4($sp)
  addi $sp, $sp, -4
  addi $sp, $sp, -12
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
  li $t0, 3
  sw $t0, -4($gp)
  lw $t1, -64($gp)
  li $t1, 0
  sw $t1, -64($gp)
  lw $t2, -68($gp)
  li $t2, 0
  sw $t2, -68($gp)
label6:
  lw $t3, -64($gp)
  lw $t4, -4($gp)
  blt $t3, $t4, label7
  j label8
label7:
  lw $t5, -72($gp)
  li $t5, 0
  sw $t5, -72($gp)
  lw $t6, -68($gp)
  lw $t7, -72($gp)
  move $t6, $t7
  sw $t6, -68($gp)
label9:
  lw $s0, -68($gp)
  lw $s1, -4($gp)
  blt $s0, $s1, label10
  j label11
label10:
  lw $s2, -80($gp)
  li $s3, 12
  lw $s4, -64($gp)
  mul $s2, $s4, $s3
  sw $s2, -80($gp)
  lw $s5, -84($gp)
  lw $s5, -44($gp)
  sw $s5, -84($gp)
  lw $s6, -88($gp)
  lw $s7, -80($gp)
  lw $t8, -84($gp)
  add $s6, $t8, $s7
  sw $s6, -88($gp)
  lw $t9, -92($gp)
  li $t0, 4
  lw $t1, -68($gp)
  mul $t9, $t1, $t0
  sw $t9, -92($gp)
  lw $t2, -96($gp)
  lw $t3, -92($gp)
  lw $t4, -88($gp)
  add $t2, $t4, $t3
  sw $t2, -96($gp)
  lw $t5, -100($gp)
  lw $t6, -68($gp)
  lw $t7, -64($gp)
  add $t5, $t7, $t6
  sw $t5, -100($gp)
  lw $s0, -104($gp)
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
  lw $s1, -4($gp)
  sw $s1, 0($sp)
  lw $s2, -100($gp)
  sw $s2, 4($sp)
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $gp, 4($sp)
  jal func2
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
  sw $s0, -104($gp)
  lw $s3, -96($gp)
  lw $s4, -104($gp)
  sw $s4, 0($s3)
  lw $s5, -108($gp)
  li $s5, 1
  sw $s5, -108($gp)
  lw $s6, -112($gp)
  lw $s7, -108($gp)
  lw $t8, -68($gp)
  add $s6, $t8, $s7
  sw $s6, -112($gp)
  lw $t9, -68($gp)
  lw $t0, -112($gp)
  move $t9, $t0
  sw $t9, -68($gp)
  j label9
label11:
  lw $t1, -120($gp)
  li $t2, 4
  lw $t3, -64($gp)
  mul $t1, $t3, $t2
  sw $t1, -120($gp)
  lw $t4, -124($gp)
  lw $t4, -60($gp)
  sw $t4, -124($gp)
  lw $t5, -128($gp)
  lw $t6, -120($gp)
  lw $t7, -124($gp)
  add $t5, $t7, $t6
  sw $t5, -128($gp)
  lw $s0, -132($gp)
  li $s1, 12
  lw $s2, -64($gp)
  mul $s0, $s2, $s1
  sw $s0, -132($gp)
  lw $s3, -136($gp)
  lw $s3, -44($gp)
  sw $s3, -136($gp)
  lw $s4, -140($gp)
  lw $s5, -132($gp)
  lw $s6, -136($gp)
  add $s4, $s6, $s5
  sw $s4, -140($gp)
  lw $s7, -144($gp)
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
  lw $t8, -140($gp)
  sw $t8, 0($sp)
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $gp, 4($sp)
  jal func1
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
  move $s7, $v0
  sw $s7, -144($gp)
  lw $t9, -128($gp)
  lw $t0, -144($gp)
  sw $t0, 0($t9)
  lw $t1, -148($gp)
  li $t1, 1
  sw $t1, -148($gp)
  lw $t2, -152($gp)
  lw $t3, -148($gp)
  lw $t4, -64($gp)
  add $t2, $t4, $t3
  sw $t2, -152($gp)
  lw $t5, -64($gp)
  lw $t6, -152($gp)
  move $t5, $t6
  sw $t5, -64($gp)
  j label6
label8:
  lw $t7, -160($gp)
  li $t7, 0
  sw $t7, -160($gp)
  lw $s0, -164($gp)
  li $s1, 12
  lw $s2, -160($gp)
  mul $s0, $s2, $s1
  sw $s0, -164($gp)
  lw $s3, -168($gp)
  lw $s3, -44($gp)
  sw $s3, -168($gp)
  lw $s4, -172($gp)
  lw $s5, -164($gp)
  lw $s6, -168($gp)
  add $s4, $s6, $s5
  sw $s4, -172($gp)
  lw $s7, -176($gp)
  li $s7, 0
  sw $s7, -176($gp)
  lw $t8, -180($gp)
  li $t9, 4
  lw $t0, -176($gp)
  mul $t8, $t0, $t9
  sw $t8, -180($gp)
  lw $t1, -184($gp)
  lw $t2, -180($gp)
  lw $t3, -172($gp)
  add $t1, $t3, $t2
  sw $t1, -184($gp)
  lw $t4, -188($gp)
  lw $t5, -184($gp)
  lw $t4, 0($t5)
  sw $t4, -188($gp)
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $t6, -188($gp)
  move $a0, $t6
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $t7, -192($gp)
  li $t7, 0
  sw $t7, -192($gp)
  lw $s0, -196($gp)
  li $s1, 12
  lw $s2, -192($gp)
  mul $s0, $s2, $s1
  sw $s0, -196($gp)
  lw $s3, -200($gp)
  lw $s3, -44($gp)
  sw $s3, -200($gp)
  lw $s4, -204($gp)
  lw $s5, -196($gp)
  lw $s6, -200($gp)
  add $s4, $s6, $s5
  sw $s4, -204($gp)
  lw $s7, -208($gp)
  li $s7, 1
  sw $s7, -208($gp)
  lw $t8, -212($gp)
  li $t9, 4
  lw $t0, -208($gp)
  mul $t8, $t0, $t9
  sw $t8, -212($gp)
  lw $t1, -216($gp)
  lw $t2, -212($gp)
  lw $t3, -204($gp)
  add $t1, $t3, $t2
  sw $t1, -216($gp)
  lw $t4, -220($gp)
  lw $t5, -216($gp)
  lw $t4, 0($t5)
  sw $t4, -220($gp)
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $t6, -220($gp)
  move $a0, $t6
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $t7, -224($gp)
  li $t7, 1
  sw $t7, -224($gp)
  lw $s0, -228($gp)
  li $s1, 12
  lw $s2, -224($gp)
  mul $s0, $s2, $s1
  sw $s0, -228($gp)
  lw $s3, -232($gp)
  lw $s3, -44($gp)
  sw $s3, -232($gp)
  lw $s4, -236($gp)
  lw $s5, -228($gp)
  lw $s6, -232($gp)
  add $s4, $s6, $s5
  sw $s4, -236($gp)
  lw $s7, -240($gp)
  li $s7, 0
  sw $s7, -240($gp)
  lw $t8, -244($gp)
  li $t9, 4
  lw $t0, -240($gp)
  mul $t8, $t0, $t9
  sw $t8, -244($gp)
  lw $t1, -248($gp)
  lw $t2, -244($gp)
  lw $t3, -236($gp)
  add $t1, $t3, $t2
  sw $t1, -248($gp)
  lw $t4, -252($gp)
  lw $t5, -248($gp)
  lw $t4, 0($t5)
  sw $t4, -252($gp)
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $t6, -252($gp)
  move $a0, $t6
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $t7, -256($gp)
  li $t7, 1
  sw $t7, -256($gp)
  lw $s0, -260($gp)
  li $s1, 12
  lw $s2, -256($gp)
  mul $s0, $s2, $s1
  sw $s0, -260($gp)
  lw $s3, -264($gp)
  lw $s3, -44($gp)
  sw $s3, -264($gp)
  lw $s4, -268($gp)
  lw $s5, -260($gp)
  lw $s6, -264($gp)
  add $s4, $s6, $s5
  sw $s4, -268($gp)
  lw $s7, -272($gp)
  li $s7, 1
  sw $s7, -272($gp)
  lw $t8, -276($gp)
  li $t9, 4
  lw $t0, -272($gp)
  mul $t8, $t0, $t9
  sw $t8, -276($gp)
  lw $t1, -280($gp)
  lw $t2, -276($gp)
  lw $t3, -268($gp)
  add $t1, $t3, $t2
  sw $t1, -280($gp)
  lw $t4, -284($gp)
  lw $t5, -280($gp)
  lw $t4, 0($t5)
  sw $t4, -284($gp)
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $t6, -284($gp)
  move $a0, $t6
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $t7, -288($gp)
  li $t7, 0
  sw $t7, -288($gp)
  lw $s0, -292($gp)
  li $s1, 4
  lw $s2, -288($gp)
  mul $s0, $s2, $s1
  sw $s0, -292($gp)
  lw $s3, -296($gp)
  lw $s3, -60($gp)
  sw $s3, -296($gp)
  lw $s4, -300($gp)
  lw $s5, -292($gp)
  lw $s6, -296($gp)
  add $s4, $s6, $s5
  sw $s4, -300($gp)
  lw $s7, -304($gp)
  lw $t8, -300($gp)
  lw $s7, 0($t8)
  sw $s7, -304($gp)
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $t9, -304($gp)
  move $a0, $t9
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $t0, -308($gp)
  li $t0, 1
  sw $t0, -308($gp)
  lw $t1, -312($gp)
  li $t2, 4
  lw $t3, -308($gp)
  mul $t1, $t3, $t2
  sw $t1, -312($gp)
  lw $t4, -316($gp)
  lw $t4, -60($gp)
  sw $t4, -316($gp)
  lw $t5, -320($gp)
  lw $t6, -312($gp)
  lw $t7, -316($gp)
  add $t5, $t7, $t6
  sw $t5, -320($gp)
  lw $s0, -324($gp)
  lw $s1, -320($gp)
  lw $s0, 0($s1)
  sw $s0, -324($gp)
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $s2, -324($gp)
  move $a0, $s2
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $s3, -328($gp)
  li $s3, 0
  sw $s3, -328($gp)
  lw $s4, -328($gp)
  move $v0, $s4
  jr $ra
