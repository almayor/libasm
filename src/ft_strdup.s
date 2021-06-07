section .text
	global _ft_strdup
	extern _ft_strlen, _ft_strcpy
	extern _malloc
	default rel

_ft_strdup:
	push rdi			
	call _ft_strlen
	mov rdi, rax
	inc	rdi					; extra byte for NULL termination
	call _malloc
	cmp rax, 0				; malloc returns NULL
	jz error
	pop rsi
	mov rdi, rax
	sub rsp, 8				; aligning stack at 16-byte boundary
	call _ft_strcpy
	add rsp, 8				; restoring stack
	ret

error:
	xor rax, rax
	ret
	