section .text
	global _ft_read
	extern ___error
	default rel

_ft_read:
	mov	 rax, 0x2000003
	syscall
	jnc return
error:
	push rax					; aligning stack at 16-byte boundary
	call ___error
	pop rdx
	mov [rax], edx				; setting errno
	mov rax, -1
return:
	ret
	