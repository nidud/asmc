
include winnt.inc

	.code

	mov	rax,MAXUINT_PTR
	mov	rax,MAXINT_PTR
	mov	rax,MININT_PTR

	mov	rax,MAXULONG_PTR
	mov	rax,MAXLONG_PTR
	mov	rax,MINLONG_PTR

	mov	eax,MAXUHALF_PTR
	mov	eax,MAXHALF_PTR
	mov	eax,MINHALF_PTR

	mov	al,SIZE_T
	mov	al,PSIZE_T

	mov	al,SSIZE_T
	mov	al,PSSIZE_T

if  _WIN32_WINNT GE 0x0600

	mov	al,MAXUINT8
	mov	al,MAXINT8
	mov	al,MININT8

	mov	ax,MAXUINT16
	mov	ax,MAXINT16
	mov	ax,MININT16

	mov	eax,MAXUINT32
	mov	eax,MAXINT32
	mov	eax,MININT32


	mov	eax,MAXULONG32
	mov	eax,MAXLONG32
	mov	eax,MINLONG32

	mov	rax,MAXSIZE_T
	mov	rax,MAXSSIZE_T
	mov	rax,MINSSIZE_T

	mov	eax,MAXUINT
	mov	eax,MAXINT
	mov	eax,MININT

	mov	eax,MAXDWORD32
	mov	rax,MAXDWORD64

	mov	rax,MAXUINT64
	mov	rax,MAXINT64
	mov	rax,MININT64
	mov	rax,MAXULONG64
	mov	rax,MAXLONG64
	mov	rax,MINLONG64
	mov	rax,MAXULONGLONG
	mov	rax,MINLONGLONG
endif
	END
