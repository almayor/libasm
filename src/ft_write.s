section .text
	global _ft_write
	extern ___error
	default rel

_ft_write:
	mov	 rax, 0x02000004
	syscall
	jnc _return
_error:
	push rax					; aligning stack at 16-byte boundary
	call ___error
	pop rdx
	mov [rax], edx				; setting errno
	mov rax, -1
_return:
	ret
