INCLUDE Irvine32.inc
INCLUDE Inputmod.inc

includelib Winmm.lib

PlaySound PROTO,
        pszSound:PTR BYTE, 
        hmod:DWORD, 
        fdwSound:DWORD

.data
	deviceConnect BYTE "DeviceConnect",0

	SND_ALIAS    DWORD 00010000h
	SND_RESOURCE DWORD 00040005h
	SND_FILENAME DWORD 00020000h

	file BYTE "c:\\Windows\media\Alarm01.wav"
	
.code
	main proc
	xor eax, eax
	mov  eax,  black +(green + 10)
	xor ebx, ebx
	call SetTextColor
	
        
        FILEHANDLING
        
        mov eax, 5000
        call delay
  L1:       
        call clrscr
        
        LOCALTIME
        
        call crlf

	GETDATA hrstr, hr, bh
	
	GETDATA minstr, mnt, bh	
	
	CHECK hr,mnt,bh

	.IF(flg>0)
	   jmp L1
	.ENDIF
	
	GETDATA laststr, hr, mnt
	
	INVOKE PlaySound, OFFSET file, NULL, SND_FILENAME
	
	exit
    	main endp


end main
