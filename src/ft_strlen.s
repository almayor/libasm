section .text
	global _ft_strlen
	default rel

_ft_strlen:
	xor	rax, rax

_loop:
	cmp [rdi + rax], byte 0
	jz	done
	inc	rax
	jmp _loop
	
done:
	ret
	