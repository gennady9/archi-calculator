 
section .data                    	; data section, read-write
        an:    DQ 0              	; this is a temporary var
	blabla: DQ 123456789
	highnum: DQ 0
	lownum: DQ 0
	size: DQ 0
	res: DQ 0
	counter: DQ 0
	tmpres: DQ 0
	tmpsub: DQ 0
	tmphigh: DQ 0
	divres: DB 0
	pointer: DQ 0
	forchecking: DQ 0
section .text                    	; our code is always in the .text section
        global asm_add          	    ; makes the function appear in global scope
        extern printf            	; tell linker that printf is defined elsewhere 							; (not used in the program)
        global asm_sub
	global asm_mul
	global asm_div
asm_add:                        	    ; functions are defined as labels
        push    rbp              	; save Base Pointer (bp) original value
        mov     rbp, rsp         	; use base pointer to access stack contents
			    ; get function argument

;;;;;;;;;;;;;;;; FUNCTION EFFECTIVE CODE STARTS HERE ;;;;;;;;;;;;;;;; 
        mov	qword [an], 0	
	mov al, 0   ;carry flag
	;add rcx,
	dec rdx
	add rdi, rdx
	add rsi, rdx
	add rcx, rdx
	mov r10, rdx
	contreading:
		mov r8b,byte [rdi]
		sub r8b,0X30
		mov r9b,byte [rsi]
		sub r9b,0X30
		add r8b,r9b
		add r8b,al
		mov al,0
		cmp r8b, 10
		jl notcarry
        carry:
                sub r8b,10
                mov al,1
        notcarry:
                add r8b,0X30
                mov byte [rcx],r8b
                dec rsi
                dec rdi
                ;dec rcx
                dec rcx
                dec r10
                cmp r10,0
                jge contreading
                cmp al,0
                je end
                add rcx,rdx
                inc rcx

       move_right:
                mov r8b, byte [rcx]
                mov byte [rcx+1], r8b
                dec rcx
                dec rdx
                cmp rdx,0
                jge move_right
                mov byte [rcx+1], '1'
    end:
         mov     rax, r8         ; return an (returned values are in rax)
         mov     rsp, rbp
         pop     rbp
         ret 
         
asm_sub:                        	    ; functions are defined as labels
        push    rbp              	; save Base Pointer (bp) original value
        mov     rbp, rsp         	; use base pointer to access stack contents
			    ; get function argument

;;;;;;;;;;;;;;;; FUNCTION EFFECTIVE CODE STARTS HERE ;;;;;;;;;;;;;;;; 
        mov	qword [an], 0	
	mov al, 0   ;carry flag
	dec rdx
	add rdi, rdx
	add rsi, rdx
	add rcx,rdx
	mov r10, rdx
    cont_sub:
        mov r8b,byte [rdi]
        sub r8b,0X30
        mov r9b,byte [rsi]
        sub r9b,0X30
        cmp al,0
        je dont_take
        cmp r8b,r9b
        jl cont_borow
        dec r8b
        mov al,0
        jmp dont_take
    cont_borow:
        add r8b, 10
        dec r8b
    dont_take:
        cmp r8b,r9b
        jge dont_borrow
        add r8b,10
        mov al,1
    dont_borrow:
        sub r8b,r9b
        add r8b,0X30
        mov byte [rcx],r8b
        dec rsi
        dec rdi
        dec rcx
        dec r10
        cmp r10,0
        jge cont_sub
        
	
    end1:
         mov     rax, r8         ; return an (returned values are in rax)
         mov     rsp, rbp
         pop     rbp
         ret

         
asm_mul:
        push    rbp              	; save Base Pointer (bp) original value
        mov     rbp, rsp         	; use base pointer to access stack contents
			    ; get function argument

;;;;;;;;;;;;;;;; FUNCTION EFFECTIVE CODE STARTS HERE ;;;;;;;;;;;;;;;; 
        mov	qword [an], 0	
	mov al, 0   ;carry flag for mul action
	mov r14,rdx
	add r14,rdx
	dec rdx
	mov r13, rsi
	add rsi, rdx
	mov r10, rdx
    init_rcx:
    	mov byte [rcx],0
        mov byte [rcx], '0'
        inc rcx
        dec r14
        cmp r14, 0
        jne init_rcx
        dec rcx ;rcx is point to the start of the number
        mov bl,0 ;carry of add after mul
	mov r15,rcx
	start_mul:
		mov r8b,byte [rsi]
		sub r8b,0X30
		mov r10, rdx
	mul_by_num:
		mov r9b,byte [rdi+r10]
		sub r9b,'0'
		mov r11b,r8b
		mov al,r11b
		mul r9b
		mov r11b,al
		mov al,0
		cmp r11b,10
		jl mul_add
	dec_num:
		inc al
		sub r11b,10
		cmp r11b,10
		jge dec_num
		mov bl,0
	mul_add:
		mov r14, rcx
		mov bl,0 ;initialize carry flag
	start_add:
		mov r12b,byte [r14]
		sub r12b,0X30
		add r11b,r12b
		add r11b,bl
		mov bl,0
		cmp r14,rcx
		je not_add_carry
	add_carry:
		add r11b,al
		mov al,0
	not_add_carry:
		cmp r11b, 10
		jl add_to
		sub r11b,10
		mov bl,1
	add_to:
		add r11b,'0'
		mov byte [r14],r11b
		mov r11b,0
		dec r14
		cmp al,0
		jg start_add
		cmp bl,0
		jg start_add
		dec r10
		cmp r10,0
		jl next_mul
		dec rcx
		jmp mul_by_num
	next_mul:
		dec r15
		mov rcx,r15
		dec rsi
		cmp rsi,r13
		jge start_mul

    end2:
         mov     rax, r11         ; return an (returned values are in rax)
         mov     rsp, rbp
         pop     rbp
         ret



asm_div:
        push    rbp              	; save Base Pointer (bp) original value
        mov     rbp, rsp         	; use base pointer to access stack contents
			    ; get function argument

;;;;;;;;;;;;;;;; FUNCTION EFFECTIVE CODE STARTS HERE ;;;;;;;;;;;;;;;; 
	mov byte [divres],0
	mov qword [highnum],0
	mov qword [lownum], 0
	mov qword [size], 0
	mov qword [res], 0
	mov qword [counter], 0
	mov qword [tmpres], 0
	mov qword [tmpsub], 0
	mov qword [tmphigh], 0
	mov byte [divres], 0
	mov qword [pointer], 0
	mov al, 0   ;carry flag for mul action
	initial:
		mov [highnum],rdi
		mov [lownum],rsi
		mov [size],rdx
		mov r11,rdx
		mov [res],rcx
	length:
		cmp byte [rsi], '0'
		jne stop_count
		inc rsi
		dec r11
		jmp length
	stop_count:
		mov [counter],r11
		inc r11
		mov rdi,r11
		extern malloc
		call malloc
		mov [tmpres],rax
		mov rcx,[tmpres]
		mov rdi,r11
		call malloc
		mov [tmpsub],rax
		mov r12,[tmpsub]
		mov byte [r12],'0'
		inc r12
		mov rsi,[lownum]
		mov r9,[size]
		sub r9,[counter]
	init_sub:
		mov r8b,byte [rsi+r9]
		mov byte [r12], r8b
		inc r9
		inc r12
		cmp r9,[size]
		jl init_sub
		mov rdi,r11
		call malloc
		mov [tmphigh],rax
		mov r12,[tmphigh]
		mov r9,0
	init_acc:
		mov r8b,0X30
		mov byte [r12+r9],r8b
		inc r9
		cmp r9,[counter]
		jl init_acc
		mov rdi,[highnum]
		mov r14b,byte [rdi]
		
		mov byte [r12+r9],r14b
		mov rdi,[tmphigh]
		mov r15b,byte[rdi+2]
		mov rdx,[counter]
		inc rdx
		mov rsi,[tmpsub]
		mov r15b,byte[rsi+2]
		mov rcx,[tmpres]
		jmp cmpnum
	inc_ptr:
		inc rsi
		inc rdi
	cmpnum:
		dec rdx
		cmp rdx,0
		jl contsub
		mov r8b,byte [rdi]
		cmp byte [rsi],r8b
		je inc_ptr
		cmp byte [rsi],r8b
		jg next_digit
		mov r8b,byte[rdi]
		;sub r8b,0X30
		mov [forchecking], r8b
	contsub:
		mov rdx,[counter]
		inc rdx
		mov rsi,[tmpsub]
		mov rdi,[tmphigh]
		mov rcx,[tmpres]
		mov al,[divres]
		inc al
		mov [divres],al
		call asm_sub
		mov rdx,[counter]
		inc rdx
		mov rsi,[tmpsub]
		mov rdi,[tmphigh]
		mov rcx,[tmpres]
	copynum:
		mov r8b,byte [rcx]
		mov byte [rdi],r8b
		mov byte [rcx],'0'
		dec rdx
		inc rcx
		inc rdi
		cmp rdx,0
		jne copynum
		mov rdx,[counter]
		inc rdx
		mov rsi,[tmpsub]
		mov rdi,[tmphigh]
		mov rcx,[tmpres]
		jmp cmpnum
	next_digit:
		mov r8b,[divres]
		add r8b,'0'
		mov al,[divres]
		mov al,0
		mov [divres],al
		mov r9,[pointer]
		mov rcx,[res]
		mov byte [rcx+r9],r8b
		mov r8,[size]
		inc r9
		mov [pointer],r9
		cmp r9,r8
		je end3
		mov rdx,[counter]
		mov rsi,[tmpsub]
		mov rdi,[tmphigh]
		mov rcx,[tmpres]
	copynextdigit:
		mov r8b,byte [rdi+1]
		mov byte [rdi],r8b
		inc rdi
		dec rdx
		cmp rdx,0
		jg copynextdigit
		mov rcx,[highnum]
		mov r8b ,byte [rcx+r9]
		mov byte [rdi],r8b
		mov rdx,[counter]
		inc rdx
		mov rsi,[tmpsub]
		mov rdi,[tmphigh]
		mov rcx,[tmpres]
		jmp cmpnum

end3:
		 mov rdi, [tmphigh]
		 extern free
		 call free
		 mov rdi, [tmpsub]
		 call free
		 ;mov rdi, [tmpres]
		 ;call free
		 mov rcx,[highnum]
         mov     rax, r15         ; return an (returned values are in rax)
         mov     rsp, rbp
         pop     rbp
         ret
