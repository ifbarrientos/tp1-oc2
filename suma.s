section .text
global suma

suma:
    mov eax, [esp+4]
    mov ebx, [esp+8]
    add eax, ebx
    ret