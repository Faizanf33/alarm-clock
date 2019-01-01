.data
	hrstr BYTE "Enter hour: ", 0
	minstr BYTE "Enter minute: ", 0	
	
	hr BYTE ?
	mnt BYTE ?

	laststr BYTE "Your alarm is set to ", 0
        
        arr BYTE 500 DUP(0)
	filename BYTE "data.txt",0
	Bytes_Written DWORD ?
        handle DWORD ?

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

FILEHANDLING MACRO
                mov edx,offset filename
                INVOKE CREATEFILE, edx, GENERIC_read, NULL, NULL, open_existing, FILE_ATTRIBUTE_NORMAL, 0
                ;call open_file_Read_mode
		mov handle,eax
		mov edx,offset arr
		mov ecx,lengthof arr
		mov eax,handle
		INVOKE READFILE,eax,edx,ecx,Addr Bytes_Written,0
		;call Read_from_file
		mov edx, OFFSET arr
		call writestring
ENDM
