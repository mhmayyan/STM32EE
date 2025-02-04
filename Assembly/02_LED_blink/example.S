@LD1 is connected to PA5 (ARD.D13)
@LD2 is connected to PB14

.syntax unified
.cpu cortex-m4
.thumb

@ -----------------------------------------------------------------------------
@ Symbols

@ Peripheral base addresses
GPIOA_BASE = 0x48000000
RCC_BASE   = 0x40021000

@ GPIOC peripheral register addresses
GPIOA_MODER = GPIOA_BASE + 0x0
GPIOA_BSSR  = GPIOA_BASE + 0x18

@ RCC peripheral register addresses
RCC_AHB2ENR = RCC_BASE + 0x4C

@ Bit definitions for GPIO_MODER register
GPIOA_MODER_MODER05_MASK   = 3 << 10
GPIOA_MODER_MODER05_OUTPUT = 1 << 10

@ Bit definitions for GPIO_BSSR register
GPIOA_BSSR_BR05 = 1 << 21	@ to reset the bit
GPIOA_BSSR_BS05 = 1 << 5	@ to set the bit

@ Bit definitions for RCC_AHB2ENR register
RCC_AHB2ENR_GPIOAEN = 1

@ LED blink delay
LED_BLINK_DELAY = 1000000

@ -----------------------------------------------------------------------------
@ Vector table

.word 0x200A0000    @ Top of stack (end od RAM)
.word _start        @ Reset handler
.space 0x400-4*2    @fill al vector table with zeros

@ -----------------------------------------------------------------------------
@ Program start

.type start, "function"
.global _start
_start:
    @ Enable GPIOA
    ldr r0,=RCC_AHB2ENR
    ldr r2, [r0]
    ldr r1, =RCC_AHB2ENR_GPIOAEN
    orr r2, r1
    str r2, [r0]

    @ Set GPIOA pin 5 mode to output
    ldr r0, =GPIOA_MODER
    ldr r2, [r0]
    ldr r1, =GPIOA_MODER_MODER05_MASK
    bic r2, r1
    ldr r1, =GPIOA_MODER_MODER05_OUTPUT
    orr r2, r1
    str r2, [r0]

    @ GPIOC pin 5 type is set to push-pull (this is default after reset)
    @ GPIOC pin 5 output speed is set to slow (this is default after reset)
    @ GPIOC pin 5 no pull-up nor pull-down (this is default after reset)

led_off:
    ldr r0, =GPIOA_BSSR
    ldr r1, =GPIOA_BSSR_BR05
    str r1, [r0]

    ldr r0, =LED_BLINK_DELAY
delay1:
    subs r0, #1
    bne delay1

led_on:
    ldr r0, =GPIOA_BSSR
    ldr r1, =GPIOA_BSSR_BS05
    str r1, [r0]

    ldr r0, =LED_BLINK_DELAY
delay2:
    subs r0, #1
    bne delay2

    b led_off
.end
