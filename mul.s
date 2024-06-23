section .text
global mul

mul:

    mov eax, [esp+4]
    movd mm0, eax

    mov eax, [esp+8]
    movd mm1, eax

    pmuludq mm0, mm1

    movd eax, mm0

    emms

    ret