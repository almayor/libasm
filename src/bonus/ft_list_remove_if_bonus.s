section .text
	global _ft_list_remove_if
	extern _free
	default rel

_ft_list_remove_if:
	push r12
	push r13
	push r14
	push r15
	push rbx
	mov r12, rdi				; pointer to beginning of list
	mov r13, rsi				; value to compare against
	mov r14, rdx				; cmp function
	mov r15, rcx				; free function
_get_head:
	mov rbx, [r12]
	test rbx, rbx
	jz _return					; return if list is empty
	mov rdi, [rbx]
	mov rsi, r13
	call r14
	test rax, rax
	jnz	_start_looping			; found new head – start iterating
	mov rdx, [rbx + 8]
	mov [r12], rdx				; otherwise examine next link
	mov rdi, rbx				; and delete old head
	call _delete_link
	jmp _get_head
_start_looping:
	mov r12, [r12]				; from now on r12 is the beginning of list
_loop:
	mov rbx, [r12 + 8]			; examine next link
	test rbx, rbx				; if next link is zero, return
	jz _return
	mov rdi, [rbx]
	mov rsi, r13
	call r14
	test rax, rax
	jnz _advance				; next link is valid, can advance pointer
	mov rax, [rbx + 8]			; otherwise, delete link
	mov [r12 + 8], rax
	mov rdi, rbx
	call _delete_link
	jmp _loop
_advance:
	mov r12, rbx
	jmp _loop
_return:
	pop rbx						; restoring all callee-preserved registers
	pop r15
	pop r14
	pop r13
	pop r12
	ret 


_delete_link:
	push r12
	mov r12, rdi
	mov rdi, [rdi]
	sub rsp, 8
	call r15
	mov rdi, r12
	call _free
	add rsp, 8
	pop r12
	ret
