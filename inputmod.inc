; DATA SECTION AND A MACROS DEFIND HERE

.data
	hrstr BYTE "Enter hour: ", 0
	minstr BYTE "Enter minute: ", 0	
	
	hr BYTE ?
	mnt BYTE ?

	laststr BYTE "Your alarm is set to ", 0


; MACRO FOR OUTPUT AND INPUT VALUE
GETDATA MACRO string, var, opt
	mov dl, 10
	mov dh, 5
	call Gotoxy

	mov edx, offset string
	call writestring

	.IF (opt == 0)
		call readint
		mov var, al

	.ELSE
		mov al, var
		call writedec

		mov al, ':'
		call writechar

		mov al, opt
		call writedec
		call crlf

	.ENDIF		
ENDM