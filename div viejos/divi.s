section .text
global divi

divi:
    mov ebp, esp; for correct debugging
    mov eax, [esp+4]
    mov ebx, [esp+8]
    mov ecx, 0

    mov esi, eax
    mov edi, ebx

    cdq
    xor eax, edx
    sub eax, edx

    mov edx, eax

    cmp ebx, 0
    jl invertir_signo

div_loop:
    cmp eax, ebx
    jb analizar_signo
    sub eax, ebx
    inc ecx
    jmp div_loop

analizar_signo:
    xor esi,edi
    jns fin_div
    
    neg ecx
    
    jmp fin_div

invertir_signo:
    neg ebx
    jmp div_loop

fin_div:
    mov eax, ecx

    pop ecx
    pop edi
    pop esi

    mov esp, ebp         ; Restore the original stack pointer
    pop ebp

    ret

