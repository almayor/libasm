section .text
	global _ft_strcmp
	default rel

_ft_strcmp:
	xor	rdx, rdx
	xor rcx, rcx

_loop:
	mov dl, byte [rdi + rcx]
	sub dl, byte [rsi + rcx]
	jnz return

	mov al, byte [rdi + rcx]
	and al, byte [rsi + rcx]
	jz	return

	inc rcx
	jmp _loop

return:
	movsx rax, dl	
	ret
	