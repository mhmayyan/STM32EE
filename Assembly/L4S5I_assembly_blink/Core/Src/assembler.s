/*
 * assembler.s
 *
 */
 
  .syntax unified
 
  .text
  .global ASM_Function
  .thumb_func
 
  .equ  RCC_BASE_ADDR,  0x40021000	//
  .equ  RCC_AHB2ENR,  0x4C       //


  .equ  GPIOB_BASE_ADDR,0x48000400 //
  .equ  GPIOB_MODER,  GPIOB_BASE_ADDR+0x00
  .equ  GPIOB_BSRR,     GPIOB_BASE_ADDR+0x18 // GPIOB Bit set reset register
 
  .equ  COUNTER,        0xFFFF
 
//------------------------------------------------------------------------------------------------
  ASM_Function:
  LDR R1, =RCC_BASE_ADDR           // Load RCC configuration register address in R1
  LDR R0, =0x00000002
  STR R0, [R1, RCC_AHB2ENR]

  LDR R1, =GPIOB_MODER
  LDR R0, [R1]
  MOV R2, #0xD0
  LSL R2, #24
  AND R0, R2, R0
  STR R0, [R1]
 
  turnON:
  // Set output high
  LDR R1, =GPIOB_BSRR
  LDR R0, =0x00004000
  STR R0, [R1]
 
  MOV R2, #COUNTER
  LSL R2, #4                       // Logical Shift Left
  delay1:
  SUBS R2, R2, #1                  // R2 = R2 - 1, R2 = 0?
  BNE delay1                       // stay in loop delay1 if not equal to zero
 
  turnOFF:
  // Set output low
  LDR R0, =0x40000000
  STR R0, [R1]
 
  MOV R2, #COUNTER
  LSL R2, #4                       // Logical Shift Left

  delay2:
  SUBS R2, R2, #1                  // R2 = R2 - 1, R2 = 0?
  BNE delay2                       // stay in loop delay1 if not equal to zero
 
  delayDone:
  B turnON                         // Jump to turnON
