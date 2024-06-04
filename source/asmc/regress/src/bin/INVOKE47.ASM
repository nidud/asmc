
	.286
	.model small
	.386

Enable proto far pascal :far ptr, :word

	.code

ReEnable proc far pascal lpDev:far ptr, a2:far ptr
	invoke Enable, lpDev, 0
	ret
ReEnable endp

Enable proc far pascal lpDev:far ptr, wStyle:word
	ret
Enable endp

end
