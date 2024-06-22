section .text
global divide

div:
    mov eax, [esp+4]
    mov ebx, [esp+8]

    cdq
    idiv ebx

    ret