[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f
CYAN_ON_BLACK equ 0x0B

print_string:
   pusha
   mov edx, VIDEO_MEMORY

print_string_loop:
   mov al, [ebx]
   mov ah, ch
   
   cmp al, 0
   je print_string_done

   mov [edx], ax
   add ebx, 1
   add edx, 2

   jmp print_string_loop

print_string_done:
   popa
   ret
