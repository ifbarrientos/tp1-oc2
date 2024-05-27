section .text
global resta

resta:
    mov eax, [esp+4]
    mov ebx, [esp+8]
    sub eax, ebx
    ret