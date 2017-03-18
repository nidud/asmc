include basetsd.inc

	.code

	mov	eax,MAXUINT_PTR
	mov	eax,MAXINT_PTR
	mov	eax,MININT_PTR

	mov	eax,MAXULONG_PTR
	mov	eax,MAXLONG_PTR
	mov	eax,MINLONG_PTR

	mov	eax,MAXUHALF_PTR
	mov	eax,MAXHALF_PTR
	mov	eax,MINHALF_PTR

	mov	eax,SIZE_T
	mov	eax,PSIZE_T

	mov	eax,SSIZE_T
	mov	eax,PSSIZE_T

if  _WIN32_WINNT GE 0x0600

	mov	eax,MAXUINT8
	mov	eax,MAXINT8
	mov	eax,MININT8

	mov	eax,MAXUINT16
	mov	eax,MAXINT16
	mov	eax,MININT16

	mov	eax,MAXUINT32
	mov	eax,MAXINT32
	mov	eax,MININT32


	mov	eax,MAXULONG32
	mov	eax,MAXLONG32
	mov	eax,MINLONG32

	mov	eax,MAXSIZE_T
	mov	eax,MAXSSIZE_T
	mov	eax,MINSSIZE_T

	mov	eax,MAXUINT
	mov	eax,MAXINT
	mov	eax,MININT

	mov	eax,MAXDWORD32
endif
	END
