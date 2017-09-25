; CMEGALINE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include cfini.inc
include stdlib.inc

SWPFLAG equ SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER

.code

cmegaline proc uses esi edi

local	bz:COORD,
	rc:SMALL_RECT,
	ci:CONSOLE_SCREEN_BUFFER_INFO,
	x, y, col, row

    doszip_hide()

    xor eax,eax
    mov x,eax
    mov y,eax
    mov eax,DZMINCOLS
    mov edx,DZMINROWS

    .if !(cflag & _C_EGALINE)

	mov edx,GetLargestConsoleWindowSize(hStdOutput)
	shr edx,16
	movzx	eax,ax
	and eax,-2

	.if eax < DZMINCOLS || edx < DZMINROWS

	    mov eax,DZMINCOLS
	    mov edx,DZMINROWS

	.elseif eax > DZMAXCOLS || edx > DZMAXROWS

	    .if eax > DZMAXCOLS

		mov eax,DZMAXCOLS
	    .endif
	    .if edx > DZMAXROWS

		mov edx,DZMAXROWS
	    .endif
	.endif
    .endif

    mov col,eax
    mov row,edx

    .if CFGetSection(".consolesize")

	mov esi,eax
	mov edi,4
	.if cflag & _C_EGALINE

	    xor edi,edi
	.endif
	.if INIGetEntryID(esi, edi)

	    mov x,atol(eax)
	.endif
	.if INIGetEntryID(esi, &[edi+1])

	    mov y,atol(eax)
	.endif
	.if INIGetEntryID(esi, &[edi+2])

	    mov col,atol(eax)
	.endif
	.if INIGetEntryID(esi, &[edi+3])

	    mov row,atol(eax)
	.endif
    .endif

    .if GetConsoleScreenBufferInfo(hStdOutput, &ci)
	;
	; japheth 2014-01-10 - reposition to desktop position 0,0
	;
	SetWindowPos(GetConsoleWindow(),0,x,y,0,0,SWPFLAG)

	xor eax,eax
	mov rc.Left,ax
	mov rc.Top,ax
	mov eax,col
	mov bz.x,ax
	dec eax
	mov rc.Right,ax
	mov edx,row
	mov bz.y,dx
	dec edx
	mov rc.Bottom,dx

	SetConsoleWindowInfo(hStdOutput, 1, &rc)
	SetConsoleScreenBufferSize(hStdOutput, bz)
	SetConsoleWindowInfo(hStdOutput, 1, &rc)

	.if GetConsoleScreenBufferInfo(hStdOutput, &ci)

	    mov eax,ci.dwSize
	    movzx   edx,ax
	    mov _scrcol,edx
	    shr eax,16
	    dec eax
	    mov _scrrow,eax
	.endif
    .endif

    apiega()
    doszip_show()
    ret

cmegaline endp

    END
