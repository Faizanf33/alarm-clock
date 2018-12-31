INCLUDE irvine32.inc
INCLUDE module.inc

.data
	hrstr BYTE "Enter hour: ", 0
	minstr BYTE "Enter minute: ", 0
	
	
	hr BYTE ?
	mnt BYTE ?

	laststr BYTE "Alarm set to ", 0
	
.code
	main proc
	mov  eax, green
	xor ebx, ebx
	
	call SetTextColor

	GETDATA hrstr, hr, bh
	
	GETDATA minstr, mnt, bh	
		
	GETDATA laststr, hr, mnt
	
	exit
    	main endp


end main
