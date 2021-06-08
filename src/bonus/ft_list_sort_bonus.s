section .text
	global _ft_list_sort
	extern _ft_list_size, _print_list
	default rel

; using bubble sort as it's the easiest to implement in assembly

_ft_list_sort:
	push r12			; linkA
	push r13			; linkB
	push r14			; head pointer
	push r15			; cmp function
	push rbx			; size of list

	mov r14, rdi
	mov r15, rsi

	mov rdi, [r14]
	call _ft_list_size
	mov rcx, rax		; list_size

	cmp rcx, 1
	jng _return			; list with less than two links

_start_from_head:
	mov r13, [r14]
	mov rbx, rcx

_advance:
	mov r12, r13
	mov r13, [r12 + 8]

	test r13, r13
	jz _loop			; reached end of list

	mov rdi, [r12]
	mov rsi, [r13]
	call r15
	test eax, eax
	jng _advance

	mov rdx, [r12]
	mov rcx, [r13]
	mov [r12], rcx
	mov [r13], rdx
	jmp _advance

_loop:
	mov rcx, rbx
	loop _start_from_head
	
_return:
	pop rbx				; restoring callee-preserved registers
	pop r15
	pop r14
	pop r13
	pop r12
	ret
