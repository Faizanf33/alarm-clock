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