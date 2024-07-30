[org 0x7c00]
KERNEL_OFFSET equ 0x1000

; CODE ;
   mov [boot_drive], dl
   mov bp, 0x9000
   mov sp, bp


   ;mov bx, tkpos_message
   ;call print
   ;call print_nl

   call load_kernel
   call switch_to_pm
   jmp $ 

[bits 16]
load_kernel:
   mov bx, loading_kernel_msg
   ;call print
   call print_nl
   
   mov ax, 0x13
   int 0x10

   mov bx, KERNEL_OFFSET
   mov dh, 16
   mov dl, [boot_drive]
   call disk_load
   ret

; INCLUDES ;

%include "bootloader/32bgdt.asm"
%include "bootloader/32bit-switch.asm"
%include "bootloader/32bprint.asm"
%include "bootloader/boot_print.asm"
%include "bootloader/disk.asm"
; DATA ;

attempt_pm_msg db "Attempting to load pm", 0
loading_kernel_msg db "Loading Kernel", 0
tkpos_message db "WELCOME TO TKP OS!", 0
boot_drive db 0

; 32 BIT ;

[bits 64]
BEGIN_PM:
   call KERNEL_OFFSET
   jmp $


; PADDING ;

times 510-($-$$) db 0
dw 0xaa55
