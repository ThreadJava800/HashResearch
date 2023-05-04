global rotlHash

rotlHash:
    xor rax, rax    ; rax = 0 (hash)
    xor rcx, rcx

.rotlLoop:
    mov cl, byte [rdi]

    rol rax, 1
    xor rax, rcx
    inc rdi

    cmp byte [rdi], 0
    jne .rotlLoop

    ret