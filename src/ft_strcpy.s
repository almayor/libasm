section .text
	global _ft_strcpy
	default rel

_ft_strcpy:
	xor	rcx, rcx

_loop:
	cmp [rdi + rcx], byte 0
	jz	done
	mov dl, [rdi + rcx]
	mov [rsi + rcx], dl
	inc	rcx
	jmp _loop

done:
	mov [rsi + rcx], byte 0
	mov rax, rsi
	ret
	