INCLUDE Irvine32.inc
INCLUDE Inputmod.inc

        
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
	
	exit
    	main endp


end main
