section .text
	global _ft_strcpy
	default rel

_ft_strcpy:
	xor	rcx, rcx

_loop:
	cmp [rsi + rcx], byte 0
	jz	done
	mov dl, [rsi + rcx]
	mov [rdi + rcx], dl
	inc	rcx
	jmp _loop

done:
	mov [rdi + rcx], byte 0
	mov rax, rdi
	ret
	