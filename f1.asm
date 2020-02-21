section .text
global f1
f1:
    push ebp
    mov ebp, esp
    xor ecx, ecx
    mov ecx, [ebp + 8]
start:
    mov al, byte[ecx]
    mov bl, '.'
    cmp al, bl
    je end
        mov bl, 'A'
        cmp al, bl
        jge bukva
        jl cifra
        cifra:
            inc ecx            
            jmp start
        bukva:
            mov bl, 'M'
            cmp al, bl
            jle zaglavnaya1
            mov bl, 'Z'
            cmp al, bl
            jle zaglavnaya2
            jmp cifra
       zaglavnaya1:
            neg al
            mov bl, 155
            add al, bl
            mov byte[ecx], al
            inc ecx
            jmp start
       zaglavnaya2:
            mov bl, 'Z'
            neg al
            add al, bl
            mov bl, 'A'
            add al, bl
            mov byte[ecx], al
            inc ecx
            jmp start
end:
    ;mov esp, ebp
    ;pop ebp
    ;xor eax, eax
    leave
    ret