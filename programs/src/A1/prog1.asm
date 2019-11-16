//
// a1_prog1.asm -- test program of task 1
//

// writeInteger((3 + 4) * (10 - 6));
// writeCharacter('\n');

	pushc	3
	pushc	4
	add
	pushc	10
	pushc	6
	sub
	mul
	wrint
	pushc	10
	wrchr
	halt
  