#include <task.h>

void dispatch( struct TCB * old, struct TCB * new )
{
	__asm__ __volatile__(
		"stmfd	sp!, {r4 - r11,lr};\n\t" /* レジスタの退避 */
		"str	sp, [%0];\n\t"
		"adr	r0, 1f;\n\t"
		"str	r0, [%1];\n\t"
		"mov	sp, %2;\n\t"
		"mov	pc, %3;\n\t"
		"1:\n\t"
		"ldmfd	sp!, {r4 - r11, lr};\n\t" /* レジスタの復元 */
		:
		: "r"(&(old->sp)), "r"(&(old->pc)), "r"(new->sp), "r"(new->pc)
		: "r0", "cc", "memory"
	);
}

