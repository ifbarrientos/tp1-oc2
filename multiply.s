section .text
global multiply

multiply:
    mov eax, [esp+4]
    mov ebx, [esp+8]
    imul ebx
    ret