section .data
one:
    dd 1  ; Constante de uno en 32 bits

section .text
global div_mmx

div_mmx:
    push ebp
    mov ebp, esp

    mov eax, [esp+4]
    movd mm0, eax

    mov eax, [esp+8]
    movd mm1, eax
    
    xor edx, edx         ; Inicializar el cociente a 0 en edx

    ; Bucle de restas sucesivas
.divide_loop:
    movd mm2, mm0         ; Copiar el dividendo a mm2
    pcmpgtd mm2, mm1      ; mm2 = 0xFFFFFFFF si mm0 >= mm1, 0 si mm0 < mm1
    pmovmskb eax, mm2     ; Mover la máscara de bits más significativos a eax
    test eax, eax
    jz .end_division

    ; Restar divisor del dividendo
    psubd mm0, mm1

    ; Incrementar el cociente
    inc edx

    jmp .divide_loop

.end_division:
    ; Mover el cociente a eax para retorno
    mov eax, edx

    ; Restaurar el estado original
    mov esp, ebp
    pop ebp

    ; Limpiar el estado MMX para evitar conflictos con la FPU
    emms

    ret