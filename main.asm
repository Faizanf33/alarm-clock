INCLUDE Irvine32.inc
INCLUDE Inputmod.inc
	
.code
	main proc
	xor eax, eax
	xor ebx, ebx

	mov  eax,  black +(green + 10)
	call SetTextColor
	
        
        call WELCOMESCR
        
        mov eax, 2000
        call delay
	call clrscr
	
  	RETRY:       
        call LOCALTIME
        
        call crlf

	GETDATA hrstr, hr
	
	GETDATA minstr, mnt
	
	CHECK hr,mnt,bh
	
	; if users enter wrong time
	.IF(flg > 0)
		call clrscr	
		jmp RETRY

	.ENDIF
	
	SNOOZE:
	call clrscr
	call LEFTTIME
	
	.WHILE(ebx > 0)
		call LOCALTIME
		call LEFTTIME
	        mov eax, 300
		call delay
	.ENDW
	
	mov eax, green
	call SetTextColor

	mov ebx, sysMin
	inc ebx
	
	call clrscr
	call LOCALTIME
	PRINTBT

	.WHILE (ebx > sysMin)
		INVOKE PlaySound, OFFSET file, NULL, SND_FILENAME
		call LOCALTIME
	
	.ENDW
	
	.IF (sysMin > 55)
		mov mnt, 0
		inc hr
	
	.ELSE
		add mnt, 5

	.ENDIF

	jmp SNOOZE
	
	call crlf
	exit
    	main endp


end main
