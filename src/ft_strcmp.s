section .text
	global _ft_strcmp
	default rel

_ft_strcmp:
	xor	rdx, rdx
	xor rcx, rcx

_loop:
	movzx dx, byte [rdi + rcx]
	movzx ax, byte [rsi + rcx]

	cmp dx, ax
	jne	_return

	test dx, ax
	jz _return

	inc rcx
	jmp _loop

_return:
	sub dx, ax
	movsx eax, dx	
	ret
