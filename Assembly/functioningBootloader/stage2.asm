use16

ORG 0x8000


_start:
jmp _menu



_menu:
call Clear
mov bx, Welcome
call PrintText

mov bx, OptionOne
call PrintText

mov bx, OptionTwo
call PrintText

mov bx, OptionThree
call PrintText



call TakeChoice





_halt:
call Clear
mov bx, HaltMsg
call PrintText
jmp $


TakeChoice:
mov bx, MakeSelection
call PrintText

mov ah, 0x0
int 0x16
mov ah, 0x0e
int 0x10

cmp al, '1'
jz GetName

cmp al, '2'
jz _testTwo

cmp al, '3'
jz _halt

mov ah, 0x0e
mov al, 0x0d
int 0x10
mov ah, 0x0e
mov al, 0x0a
int 0x10

mov bx, WrongInput
call PrintText
call WaitForKey
jmp _menu




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


_test:
call Clear
mov bx, Welcome
call PrintText
mov bx, PressToContinue
call PrintText
call WaitForKey
jmp _menu


_testTwo:
call Clear
mov bx, PressToContinue
call PrintText
call WaitForKey
jmp _menu

GetName:
call Clear
mov bx, EnterName
call PrintText


mov si, NameBuffer
.writeLoop:
mov ah, 0x0
int 0x16
mov ah, 0x0e
mov [si], al
inc si
int 0x10

cmp al, 13
jz .showName
jmp .writeLoop

.showName:
mov byte [si], 0

call Clear
mov bx, HelloThere
call PrintText
mov bx, NameBuffer
call PrintText

mov ah, 0x0e
mov al, 0x0d
int 0x10
mov ah, 0x0e
mov al, 0x0a
int 0x10

call WaitForKey
jmp _menu


Clear:
mov ah, 0x00
mov al, 0x03
int 0x10
ret


WaitForKey:
mov bx, PressToContinue
call PrintText
mov ah, 0x0
int 0x16
ret



NameBuffer: times 32 db 0

; Welcome Text
Welcome: db "Welcome to the working bootloader!", 0x0d, 0x0a, 0
HelloThere: db "Hello there, ", 0

; Menu Options
OptionOne: db "[1] Define Name", 0x0d, 0x0a, 0
OptionTwo: db "[2] Bootloader Version", 0x0d, 0x0a, 0
OptionThree: db "[3] Halt System", 0x0d, 0x0a, 0


; Error Texts
WrongInput: db "Please press a number (1-3)!", 0

; Other Texts
PressToContinue: db "Press any key to continue...", 0
MakeSelection: db "Make a selection: ", 0
HaltMsg: db "Halting System...", 0
EnterName: db "Please Enter your name: ", 0

