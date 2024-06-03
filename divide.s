section .text
global divide

divide:
    mov eax, [esp+4]
    mov ebx, [esp+8]

    xor edx,edx
    div ebx

    ret