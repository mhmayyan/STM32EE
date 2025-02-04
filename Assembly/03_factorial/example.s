/*
	2015 Hohl and Hinds, ARM ASSEMBLY LANGUAGE Fundamentals and Techniques 2nd ed.pdf
	3.4 PROGRAM 2: FACTORIAL CALCULATION
*/
.syntax	unified
.cpu cortex-m4
.thumb
.word 0x200A0000	@set SP to end of stack
.word _start	@our main routine starts at main
.space 0x400-4*2        @fill al vector table with zeros
.type _start,"function"
.global _start
_start:
	mov	r6, #10
	mov	r7, #1
loop:	cmp	r6, #0
	ITTT	GT
	mulgt	r7, r6, r7
	subgt	r6, #1
	bgt	loop
	b _start
.end
