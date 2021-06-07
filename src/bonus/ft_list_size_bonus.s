section .text
	global _ft_list_size
	default rel

_ft_list_size:
	xor rax, rax
_loop:
	test rdi, rdi				; `next` is 8 bytes long
	jz	_return
	inc rax
	mov rdi, [rdi + 8]
	jmp _loop
_return:
	ret