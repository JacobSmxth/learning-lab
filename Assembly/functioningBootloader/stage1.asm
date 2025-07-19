use16

ORG 0x7C00

cli
xor ax, ax
mov sp, 0x7C00
mov es, ax
mov ds, ax
mov ss, ax
sti

mov ax, 0x0000
mov es, ax
mov bx, 0x8000
mov dh, 3

call DiskRead

jmp 0x0000:0x8000


DiskRead:
pusha
push dx

mov ah, 0x02
mov al, dh
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, 0x00
int 0x13

jc DiskError

pop dx
cmp al, dh
jne DiskError

popa
ret



DiskError:
popa
mov ah, 0x00
int 0x13
mov bx, ErrorMsg
call PrintText
jmp _halt



_halt:
jmp $


PrintText:
pusha

.printLoop:
mov al, [bx]
test al, al
jz .done
mov ah, 0x0e
int 0x10
inc bx
jmp .printLoop

.done:
popa
ret

; Strings

ErrorMsg: db "Disk Loading Error...", 0




times 510-($-$$) db 0
dw 0xAA55
