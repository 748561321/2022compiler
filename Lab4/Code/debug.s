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
  lw $t0, -4($gp)
  lw $t1, 12($gp)
  addi $t0, $t1, 0
  sw $t0, -4($gp)
  lw $t2, -8($gp)
  lw $t3, 8($gp)
  addi $t2, $t3, 0
  sw $t2, -8($gp)
  lw $t4, -12($gp)
  lw $t5, -4($gp)
  lw $t4, 0($t5)
  sw $t4, -12($gp)
  lw $t6, -16($gp)
  lw $t7, -8($gp)
  lw $t6, 0($t7)
  sw $t6, -16($gp)
  lw $s0, -20($gp)
  lw $s1, -16($gp)
  lw $s2, -12($gp)
  mul $s0, $s2, $s1
  sw $s0, -20($gp)
  lw $s3, -24($gp)
  lw $s4, -20($gp)
  move $s3, $s4
  sw $s3, -24($gp)
  lw $s5, -28($gp)
  lw $s6, 12($gp)
  addi $s5, $s6, 4
  sw $s5, -28($gp)
  lw $s7, -32($gp)
  lw $t8, 8($gp)
  addi $s7, $t8, 4
  sw $s7, -32($gp)
  lw $t9, -36($gp)
  lw $t0, -28($gp)
  lw $t9, 0($t0)
  sw $t9, -36($gp)
  lw $t1, -40($gp)
  lw $t2, -32($gp)
  lw $t1, 0($t2)
  sw $t1, -40($gp)
  lw $t3, -20($gp)
  lw $t4, -40($gp)
  lw $t5, -36($gp)
  mul $t3, $t5, $t4
  sw $t3, -20($gp)
  lw $t6, -48($gp)
  lw $t7, -20($gp)
  move $t6, $t7
  sw $t6, -48($gp)
  lw $s0, -52($gp)
  lw $s1, -48($gp)
  lw $s2, -24($gp)
  add $s0, $s2, $s1
  sw $s0, -52($gp)
  lw $s3, -52($gp)
  move $v0, $s3
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
  lw $s7, -48($gp)
  sw $s7, -80($gp)
  lw $t8, -84($gp)
  lw $t9, -76($gp)
  lw $t0, -80($gp)
  add $t8, $t0, $t9
  sw $t8, -84($gp)
  lw $t1, -88($gp)
  lw $t2, -84($gp)
  addi $t1, $t2, 4
  sw $t1, -88($gp)
  lw $t3, -92($gp)
  li $t4, 8
  lw $t5, -56($gp)
  mul $t3, $t5, $t4
  sw $t3, -92($gp)
  lw $t6, -96($gp)
  lw $t7, -92($gp)
  lw $s0, -88($gp)
  add $t6, $s0, $t7
  sw $t6, -96($gp)
  lw $s1, -100($gp)
  lw $s2, -96($gp)
  addi $s1, $s2, 0
  sw $s1, -100($gp)
  lw $s3, -104($gp)
  lw $s4, -56($gp)
  lw $s5, -52($gp)
  mul $s3, $s5, $s4
  sw $s3, -104($gp)
  lw $s6, -108($gp)
  lw $s7, -56($gp)
  lw $t8, -104($gp)
  add $s6, $t8, $s7
  sw $s6, -108($gp)
  lw $t9, -100($gp)
  lw $t0, -108($gp)
  sw $t0, 0($t9)
  lw $t1, -112($gp)
  li $t2, 20
  lw $t3, -52($gp)
  mul $t1, $t3, $t2
  sw $t1, -112($gp)
  lw $t4, -116($gp)
  lw $t4, -48($gp)
  sw $t4, -116($gp)
  lw $t5, -120($gp)
  lw $t6, -112($gp)
  lw $t7, -116($gp)
  add $t5, $t7, $t6
  sw $t5, -120($gp)
  lw $s0, -124($gp)
  lw $s1, -120($gp)
  addi $s0, $s1, 4
  sw $s0, -124($gp)
  lw $s2, -128($gp)
  li $s3, 8
  lw $s4, -56($gp)
  mul $s2, $s4, $s3
  sw $s2, -128($gp)
  lw $s5, -132($gp)
  lw $s6, -128($gp)
  lw $s7, -124($gp)
  add $s5, $s7, $s6
  sw $s5, -132($gp)
  lw $t8, -136($gp)
  lw $t9, -132($gp)
  addi $t8, $t9, 4
  sw $t8, -136($gp)
  lw $t0, -140($gp)
  lw $t1, -52($gp)
  lw $t2, -52($gp)
  mul $t0, $t2, $t1
  sw $t0, -140($gp)
  lw $t3, -144($gp)
  lw $t4, -56($gp)
  lw $t5, -140($gp)
  mul $t3, $t5, $t4
  sw $t3, -144($gp)
  lw $t6, -148($gp)
  lw $t7, -56($gp)
  lw $s0, -144($gp)
  add $t6, $s0, $t7
  sw $t6, -148($gp)
  lw $s1, -136($gp)
  lw $s2, -148($gp)
  sw $s2, 0($s1)
  lw $s3, -152($gp)
  li $s3, 1
  sw $s3, -152($gp)
  lw $s4, -156($gp)
  lw $s5, -152($gp)
  lw $s6, -56($gp)
  add $s4, $s6, $s5
  sw $s4, -156($gp)
  lw $s7, -56($gp)
  lw $t8, -156($gp)
  move $s7, $t8
  sw $s7, -56($gp)
  j label14
label16:
  lw $t9, -164($gp)
  li $t0, 20
  lw $t1, -52($gp)
  mul $t9, $t1, $t0
  sw $t9, -164($gp)
  lw $t2, -168($gp)
  lw $t2, -48($gp)
  sw $t2, -168($gp)
  lw $t3, -172($gp)
  lw $t4, -164($gp)
  lw $t5, -168($gp)
  add $t3, $t5, $t4
  sw $t3, -172($gp)
  lw $t6, -176($gp)
  lw $t7, -172($gp)
  addi $t6, $t7, -12
  sw $t6, -176($gp)
  lw $s0, -180($gp)
  li $s1, 20
  lw $s2, -52($gp)
  mul $s0, $s2, $s1
  sw $s0, -180($gp)
  lw $s3, -184($gp)
  lw $s3, -48($gp)
  sw $s3, -184($gp)
  lw $s4, -188($gp)
  lw $s5, -180($gp)
  lw $s6, -184($gp)
  add $s4, $s6, $s5
  sw $s4, -188($gp)
  lw $s7, -192($gp)
  lw $t8, -188($gp)
  addi $s7, $t8, 4
  sw $s7, -192($gp)
  lw $t9, -196($gp)
  li $t9, 0
  sw $t9, -196($gp)
  lw $t0, -200($gp)
  li $t1, 8
  lw $t2, -196($gp)
  mul $t0, $t2, $t1
  sw $t0, -200($gp)
  lw $t3, -204($gp)
  lw $t4, -200($gp)
  lw $t5, -192($gp)
  add $t3, $t5, $t4
  sw $t3, -204($gp)
  lw $t6, -208($gp)
  li $t7, 20
  lw $s0, -52($gp)
  mul $t6, $s0, $t7
  sw $t6, -208($gp)
  lw $s1, -212($gp)
  lw $s1, -48($gp)
  sw $s1, -212($gp)
  lw $s2, -216($gp)
  lw $s3, -208($gp)
  lw $s4, -212($gp)
  add $s2, $s4, $s3
  sw $s2, -216($gp)
  lw $s5, -220($gp)
  lw $s6, -216($gp)
  addi $s5, $s6, 4
  sw $s5, -220($gp)
  lw $s7, -224($gp)
  li $s7, 1
  sw $s7, -224($gp)
  lw $t8, -228($gp)
  li $t9, 8
  lw $t0, -224($gp)
  mul $t8, $t0, $t9
  sw $t8, -228($gp)
  lw $t1, -232($gp)
  lw $t2, -228($gp)
  lw $t3, -220($gp)
  add $t1, $t3, $t2
  sw $t1, -232($gp)
  lw $t4, -236($gp)
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
  lw $t5, -232($gp)
  sw $t5, 0($sp)
  lw $t6, -204($gp)
  sw $t6, 4($sp)
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
  move $t4, $v0
  sw $t4, -236($gp)
  lw $t7, -176($gp)
  lw $s0, -236($gp)
  sw $s0, 0($t7)
  lw $s1, -240($gp)
  li $s1, 1
  sw $s1, -240($gp)
  lw $s2, -244($gp)
  lw $s3, -240($gp)
  lw $s4, -52($gp)
  add $s2, $s4, $s3
  sw $s2, -244($gp)
  lw $s5, -52($gp)
  lw $s6, -244($gp)
  move $s5, $s6
  sw $s5, -52($gp)
  j label11
label13:
  lw $s7, -252($gp)
  li $s7, 0
  sw $s7, -252($gp)
  lw $t8, -256($gp)
  li $t9, 20
  lw $t0, -252($gp)
  mul $t8, $t0, $t9
  sw $t8, -256($gp)
  lw $t1, -260($gp)
  lw $t1, -48($gp)
  sw $t1, -260($gp)
  lw $t2, -264($gp)
  lw $t3, -256($gp)
  lw $t4, -260($gp)
  add $t2, $t4, $t3
  sw $t2, -264($gp)
  lw $t5, -268($gp)
  lw $t6, -264($gp)
  addi $t5, $t6, -12
  sw $t5, -268($gp)
  lw $t7, -272($gp)
  li $t7, 1
  sw $t7, -272($gp)
  lw $s0, -276($gp)
  li $s1, 20
  lw $s2, -272($gp)
  mul $s0, $s2, $s1
  sw $s0, -276($gp)
  lw $s3, -280($gp)
  lw $s3, -48($gp)
  sw $s3, -280($gp)
  lw $s4, -284($gp)
  lw $s5, -276($gp)
  lw $s6, -280($gp)
  add $s4, $s6, $s5
  sw $s4, -284($gp)
  lw $s7, -288($gp)
  lw $t8, -284($gp)
  addi $s7, $t8, -12
  sw $s7, -288($gp)
  lw $t9, -292($gp)
  lw $t0, -268($gp)
  lw $t9, 0($t0)
  sw $t9, -292($gp)
  lw $t1, -296($gp)
  lw $t2, -288($gp)
  lw $t1, 0($t2)
  sw $t1, -296($gp)
  lw $t3, -300($gp)
  lw $t4, -296($gp)
  lw $t5, -292($gp)
  add $t3, $t5, $t4
  sw $t3, -300($gp)
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $t6, -300($gp)
  move $a0, $t6
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $t7, -304($gp)
  li $t7, 0
  sw $t7, -304($gp)
  lw $s0, -304($gp)
  move $v0, $s0
  jr $ra
