INCLUDE Irvine32.inc
INCLUDE GraphWin.inc
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

	.WHILE (ebx > sysMin)
		INVOKE PlaySound, OFFSET file, NULL, SND_FILENAME
		INVOKE MessageBox, NULL, ADDR PopupText, ADDR PopupTitle, MB_OKCANCEL
				
		.IF (eax == 1)
			jmp PASS			
		
		.ELSE
			jmp STOP_ALARM

		.ENDIF
		
		call LOCALTIME
	
	.ENDW

	PASS:
	.IF (sysMin > 55)
		mov al, 60
		sub al, mnt
		mov mnt, al
		inc hr
	
	.ELSE
		add mnt, 5

	.ENDIF
	
	jmp SNOOZE

	STOP_ALARM:
	
	call crlf
	exit
    	main endp


end main
