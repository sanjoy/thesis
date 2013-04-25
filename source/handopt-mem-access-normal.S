	.text
	.globl access_memory
	.type access_memory, @function

access_memory:
	movq	(%rdi), %rax
	addq	8(%rdi), %rax
	addq	16(%rdi), %rax
	addq	24(%rdi), %rax
	addq	32(%rdi), %rax
	addq	40(%rdi), %rax
	addq	48(%rdi), %rax
	addq	56(%rdi), %rax
	ret
