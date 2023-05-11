section .text
global _start


;-----------------------------------------------------------------------------
; Prints string to stdout
;-----------------------------------------------------------------------------
%macro  prStdout 2

        mov rax, 0x01   ; stdout
        mov rdi, 1      ; func id
        mov rsi, %1     ; rsi (pointer to str)
        mov rdx, %2     ; rdx (msgLen)

        syscall
        
%endmacro

section .data
zerBuf:     times 64 db 0

oneChar:  db 0
section .text

;-----------------------------------------------------------
; Print dec of value
;-----------------------------------------------------------
; Entry: 	    [RBP] = value to convert to
; Exit:		    None
; Destroys: 	    RAX, RBX, RCX, RDX, RDI, R10, R11
;-----------------------------------------------------------
ToDec:
                mov rax, rbp                ; moving from [rbp] to rax

                mov r10, 0x01                   
                shl r10, 63d                  ; setting r10 = 1 and 63 0 (bin)
                and r10, rax                  ; flag if rax is negative or not

                cmp r10, 0x00
                je .ParsePos

                neg rax                       ; if rax < 0 rax = abs(rax)

.ParsePos:
                mov rcx, 0x12		      ; amount of digits (16d)
                mov rbx, zerBuf + 0x12        ; rbx = end of zerobuf

                xor rdx, rdx                  ; rdx = 0
	
.PrintSymb:
                mov rdi, 0xA		      ; rcx = 10
                div rdi			      ; rax = rax / 10, rdx = rax % 10
                                        
                add rdx, 0x30		      ; edx += 30 (symb ascii)

                mov byte [rbx], dl            ; add to buffer
                dec rbx			      ; bx --

                xor rdx, rdx                  ; rdx = 0

                cmp rax, 0
                je .Exit                      ; exit if no more digits in number

                loop .PrintSymb

.Exit:		
                cmp r10, 00
                je .PrintPos

                pushar
                mov rbx, "-"
                mov [oneChar], rbx
                prStdout oneChar, 1
                popar                         ; print '-' if value is hegative

ToDec.PrintPos:               
                mov rbx, 0x13
                sub rbx, rcx                  ; amount of values to print

                mov r10, zerBuf
                add r10, rcx                  ; rax = pointer to beginning of decimal
                prStdout r10, rbx
                ret


; rdi and rsi first and second strings rdx, rcx - lens
strcmp:
    xor rax, rax
    cmp rcx, rdx
    jne .difLens

    cld

    repe cmpsb
    je .notEq
    jmp .exit

.notEq:
    mov al, byte [rdi]
    sub al, byte [rsi]
    jmp .exit

.difLens:
    mov rax, rcx
    sub rax, rdx

.exit:
    ret


_start:
    mov rdi, string1
    mov rsi, string2
    mov rdx, 4
    mov rcx, 4

    call strcmp

    mov rbp, rax
    call ToDec

    mov rax, 0x3C
    syscall 

section .data
string1: db "Test2", 0
string2: db "Test3", 0