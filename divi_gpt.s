section .text
global divi

divi:
    push ebp             ; Save the base pointer
    mov ebp, esp         ; Set the base pointer to the current stack pointer

    ; Function parameters
    ; nro1 is [ebp + 8]
    ; nro2 is [ebp + 12]

    mov eax, [ebp + 8]   ; Load nro1 into eax
    mov ebx, [ebp + 12]  ; Load nro2 into ebx

    ; Save esi, edi, and ecx
    push esi
    push edi
    push ecx

    ; Initialize variables
    xor ecx, ecx         ; Clear ecx (quotient)
    mov esi, eax         ; Copy nro1 to esi
    mov edi, ebx         ; Copy nro2 to edi

    ; Prepare for division
    cdq                  ; Sign-extend eax into edx:eax
    xor eax, edx         ; If negative, get absolute value
    sub eax, edx
    mov edx, eax         ; Copy absolute value of nro1 to edx

    cmp edi, 0           ; Check if nro2 is zero
    je div_by_zero       ; Handle division by zero

    ; Handle negative divisor
    cmp edi, 0
    jge div_loop
    neg edi              ; If negative, make it positive

div_loop:
    cmp edx, edi         ; Compare absolute(nro1) with absolute(nro2)
    jb analyze_sign      ; If less, exit loop
    sub edx, edi         ; Subtract absolute(nro2) from absolute(nro1)
    inc ecx              ; Increment quotient
    jmp div_loop

analyze_sign:
    ; Determine the sign of the result
    xor esi, ebx         ; Check if the signs of nro1 and nro2 are different
    jns done             ; If same, result is positive
    neg ecx              ; If different, negate the quotient

done:
    mov eax, ecx         ; Move the quotient to eax (return value)

    ; Restore esi, edi, and ecx
    pop ecx
    pop edi
    pop esi

    mov esp, ebp         ; Restore the original stack pointer
    pop ebp              ; Restore the base pointer
    ret

div_by_zero:
    ; Handle division by zero (you can set a specific error code or behavior)
    xor eax, eax         ; Set eax to 0 (or any error code you prefer)
    jmp done
