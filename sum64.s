section .text
global sum64

sum64:
    push ebp
    mov ebp, esp

    movq mm0, [ebp+8]   ; Cargar el primer argumento (primer número de 64 bits)
    movq mm1, [ebp+16]  ; Cargar el segundo argumento (segundo número de 64 bits)
    
    paddq mm0, mm1
    
    movq [ebp+8], mm0

    mov esp, ebp
    pop ebp
    ret