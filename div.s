section .text
global divi

divi:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    mov ebx, [ebp + 12]

    push esi
    push edi
    push ecx

    xor ecx, ecx
    mov esi, eax
    mov edi, ebx

    cdq
    xor eax, edx
    sub eax, edx
    mov edx, eax

    cmp edi, 0
    jge div_loop
    neg edi

div_loop:
    cmp edx, edi
    jb analizar_signo
    sub edx, edi
    inc ecx
    jmp div_loop

analizar_signo:
    xor esi, ebx
    jns fin_div
    neg ecx

fin_div:
    mov eax, ecx

    pop ecx
    pop edi
    pop esi

    mov esp, ebp
    pop ebp

    ret
