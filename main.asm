INCLUDE Irvine32.inc
INCLUDE Inputmod.inc

	
.code
	main proc
	xor eax, eax
	mov  eax, green
	xor ebx, ebx
	
	call SetTextColor

	GETDATA hrstr, hr, bh
	
	GETDATA minstr, mnt, bh	
		
	GETDATA laststr, hr, mnt
	
	exit
    	main endp


end main
