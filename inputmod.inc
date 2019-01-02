
.data
  sysTime SYSTEMTIME <>
  consoleHandle DWORD ?
  colonStr BYTE ":",0
  TheTimeIs BYTE "The Local Time Is : ",0
  hrstr BYTE "Enter hour: ", 0
  minstr BYTE "Enter minute: ", 0

	hr BYTE ?
	mnt BYTE ?
flg dword 0
	laststr BYTE "Your alarm is set to : ", 0

  arr BYTE 500 DUP(0)
	filename BYTE "data.txt",0
	Bytes_Written DWORD ?
  handle DWORD ?


; MACRO For Local System Time
SYTIME MACRO
  xor eax,eax
  xor edx,edx

  mov dh, 4
  mov dl, 20
  call Gotoxy

  INVOKE GetLocalTime,ADDR sysTime
  mov edx,OFFSET TheTimeIs ; "Local Time Is : "
  call WriteString

; Below Code Display the system time (hh:mm:ss).

  movzx eax,sysTime.wHour ; hours
  call WriteDec
  mov edx,offset colonStr ; ":"
  call WriteString

  movzx eax,sysTime.wMinute ; minutes
  call WriteDec
  mov edx,offset colonStr ; ":"
  call WriteString

  movzx eax,sysTime.wSecond ; seconds
  call WriteDec
  call Crlf
  call Crlf
ENDM



; MACRO FOR OUTPUT AND INPUT VALUE
GETDATA MACRO string, var, opt
	mov dl, 20
	mov dh, 6
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
		call crlf

	.ENDIF
ENDM

FILEHANDLING MACRO
                mov edx,offset filename
                INVOKE CREATEFILE, edx, GENERIC_read, NULL, NULL, open_existing, FILE_ATTRIBUTE_NORMAL, 0
		mov handle,eax
		mov edx,offset arr
		mov ecx,lengthof arr
		mov eax,handle
		INVOKE READFILE,eax,edx,ecx,Addr Bytes_Written,0
		mov edx, OFFSET arr
		call writestring
ENDM
CHECK MACRO ho,min,opt
		mov flg,0
		.IF(ho>12)
		    add flg,1
		.ENDIF
		
		.IF(min>60)
		    add flg,1
		.ENDIF
		
		.IF(ho<1)
		    add flg,1
		.ENDIF
		
		.IF(min<1)
		    add flg,1 
		.ENDIF
ENDM