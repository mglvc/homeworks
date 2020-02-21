section .text
global f2
f2:
    push ebp
    mov ebp, esp
    xor ecx, ecx
    mov ecx, [ebp + 8]
    mov edx, ecx
start:
    mov al, byte[ecx]
    mov bl, '.'
    cmp al, bl
    je end
        mov bl, 58
        cmp al, bl
        jge bukva
        jl cifra1
        bukva:
            inc ecx            
            jmp start
        cifra1:
            mov bl, 48
            cmp al, bl
            jge cifra2
            inc ecx
            jmp start
        cifra2:
            mov  bl, al
            mov al, byte[edx]
            mov byte[edx], bl
            mov byte[ecx], al
            inc edx
            inc ecx
            jmp start
end:
    ;mov esp, ebp
    ;pop ebp
    ;xor eax, eax
    leave
    ret
