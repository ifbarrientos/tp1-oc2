section .text
global suma

sum:
    mov eax, [esp+4]
    mov ebx, [esp+8]

    add eax, ebx
    
    ret