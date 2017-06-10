include time.inc

	.code

DaysInMonth PROC year, month

	mov ecx,month
	mov eax,31

	.switch ecx

	  .case 2
		mov eax,year
		DaysInFebruary(eax)
		.endc

	  .case 4, 6, 9, 11:
		sub eax,1
		.endc

	.endsw
	ret

DaysInMonth ENDP

	END
