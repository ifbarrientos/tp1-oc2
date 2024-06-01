section .text
global divide

divide:
    mov eax, [esp+4]
    mov ebx, [esp+8]
    div ebx
    ret