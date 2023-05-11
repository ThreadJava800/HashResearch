global myStrcmp

myStrcmp:
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