; This file contains data section,
; code section, procedures,
; prototypes, macros, and libraries
; required for "main.asm" file

INCLUDELIB Winmm.lib

PlaySound PROTO,
        pszSound:PTR BYTE,
        hmod:DWORD,
        fdwSound:DWORD

;::::::::::::: START OF DATA SECTION ::::::::::::::::
.data
	; system time variables
	sysTime SYSTEMTIME <>
	consoleHandle DWORD ?

	sysHour DWORD ?
	sysMin DWORD ?

	; Strings to display
	colonStr BYTE ":",0
	TheTimeIs BYTE "SYSTEM TIME ",0
	hrstr BYTE "Enter hour: ", 0
	minstr BYTE "Enter minute: ", 0
	tleftstr BYTE "Time left until alarm: ", 0

	btstr BYTE "[snooze]	[stop]", 0

	; variables for user inputs
	hr BYTE ?
	mnt BYTE ?
        flg dword 0

	; variables for file handling
  	arr BYTE 1000 DUP(0)
	filename BYTE "data.txt",0
	Bytes_Written DWORD ?
  	handle DWORD ?

	; sound variables for alarm sound
	SND_ALIAS    DWORD 00010000h
	SND_RESOURCE DWORD 00040005h
	SND_FILENAME DWORD 00020000h

	; system path for sound file
	; change Alarm01 to Alarm02, 03, ..., 10
	; for different sounds
	file BYTE "c:\\Windows\media\Alarm01.wav"

;::::::::::::: END OF DATA SECTION ::::::::::::::::

; MACRO FOR OUTPUT STRING AND INPUT VALUE
GETDATA MACRO string, var
	mov dl, 20
	mov dh, 6
	call Gotoxy

	mov edx, offset string
	call writestring

	call readint
	mov var, al
ENDM

; Check user input values
CHECK MACRO ho,min,opt
	mov flg, 0
	.IF(ho > 23)
	    add flg, 1
	.ENDIF

	.IF(min > 59)
	    add flg, 1
	.ENDIF

	.IF(ho < 0)
	    add flg, 1
	.ENDIF

	.IF(min < 0)
	    add flg, 1
	.ENDIF
ENDM

PRINTBT MACRO
	mov dl, 20
	mov dh, 6
	call Gotoxy

	mov edx, offset btstr
	call writestring

ENDM

;::::::::::::: START OF CODE SECTION ::::::::::::::::

.code

WELCOMESCR PROC
	mov edx, offset filename
	INVOKE CREATEFILE, edx, GENERIC_read, NULL, NULL, open_existing, FILE_ATTRIBUTE_NORMAL, 0
	mov handle, eax
	mov edx, offset arr
	mov ecx, lengthof arr
	mov eax, handle
	INVOKE READFILE, eax, edx, ecx, Addr Bytes_Written, 0
	mov edx, OFFSET arr
	call writestring

	ret
WELCOMESCR ENDP

LOCALTIME PROC
	xor eax,eax
	xor edx,edx

	mov dh, 4
	mov dl, 20
	call Gotoxy

	INVOKE GetLocalTime,ADDR sysTime
	mov edx,OFFSET TheTimeIs             ; "Local Time Is : "
	call WriteString

	; Below Code Display the system time (hh:mm:ss).

	movzx eax,sysTime.wHour              ; hours
	mov sysHour, eax
	call WriteDec

	mov edx,offset colonStr              ; ":"
	call WriteString

	movzx eax,sysTime.wMinute ; minutes
	mov sysMin, eax
	call WriteDec

	mov edx,offset colonStr              ; ":"
	call WriteString

	movzx eax,sysTime.wSecond            ; seconds
	call WriteDec
	ret
LOCALTIME ENDP

LEFTTIME proc
	xor eax, eax
	xor ebx, ebx
	xor edx, edx

	mov al, hr
	mov bl, mnt

	.IF (eax < sysHour)
		add eax, 23

	.ELSEIF (eax == sysHour && ebx < sysMin)
		add eax, 23

	.ENDIF

	.IF (ebx < sysMin)
		add ebx, 60

	.ENDIF
	
	dec eax
	sub eax, sysHour
	sub ebx, sysMin

	mov dh, 7
	mov dl, 20
	call gotoxy

	mov edx, offset tleftstr
	call writestring
	call writedec
	mov eax, 'h'
	call writechar
	mov eax, ebx
	call writedec
	mov eax, 'm'
	call writechar

	ret
LEFTTIME ENDP
