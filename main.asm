INCLUDE Irvine32.inc
INCLUDE Inputmod.inc

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
        
.code
	main proc
	xor eax, eax
	mov  eax, green
	xor ebx, ebx
	
	call SetTextColor
        
        FILEHANDLING
        
        mov eax, 5000
        call delay
        
	GETDATA hrstr, hr, bh
	
	GETDATA minstr, mnt, bh	
		
	GETDATA laststr, hr, mnt
	
	exit
    	main endp


end main
