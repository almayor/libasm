section .text
	global _ft_list_push_front
	extern _malloc
	default rel

_ft_list_push_front:
	push rdi					
	push rsi					
	mov rdi, 16
	sub rsp, 8					; align stack
	call _malloc
	add rsp, 8					; restore stack
	pop rsi
	pop rdi
	test rax, rax
	jz	_return					; malloc failed
	mov [rax], rsi				; set data
	mov rcx, [rdi]				
	mov [rax + 8], rcx			; set next
	mov [rdi], rax				; change head

_return:
	ret