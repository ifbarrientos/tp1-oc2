section .text
global multiply

mul:
    mov eax, [esp+4]
    mov ebx, [esp+8]

    imul ebx

    ret