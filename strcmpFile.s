global mstrcmp

mstrcmp:

    xor eax, eax
    xor ecx, ecx

_loop:
    mov al, byte [rdi]
    mov cl, byte [rsi]

    cmp al, 0
    je _retNeg

    cmp cl, 0
    je _ret1

    cmp al, cl
    jne _default_ret

    inc rsi
    inc rdi

    jmp _loop

_ret0:
    mov eax, 0
    ret

_ret1:
    cmp al, cl
    je _ret0
    mov eax, 1
    ret
        
_retNeg:
    cmp al, cl
    je _ret0

    mov eax, 1
    ret

_default_ret:
    sub eax, ecx
    ret