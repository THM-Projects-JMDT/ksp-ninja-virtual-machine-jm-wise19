//
// a1_prog2.asm -- test program of task 1
//

// writeInteger(-2 * readInteger() + 3);
// writeCharacter('\n');

	pushc	-2
	rdint
	mul
	pushc	3
	add
	wrint
	pushc	'\n'
	wrchr
	halt
