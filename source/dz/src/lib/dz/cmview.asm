; CMVIEW.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include cfini.inc
include tview.inc
include string.inc
include stdlib.inc
include process.inc

    .code

; type 4: F4	- edit
; type 3: Alt	- edit/view
; type 2: Ctrl	- edit/view
; type 1: Shift - edit/view
; type 0: F3	- view

loadiniproc proc uses esi edi section, filename, itype

  local path[_MAX_PATH]:byte

    mov edi,filename
    mov eax,itype
    mov esi,@CStr("F3")

    .switch al
      .case 4 : mov esi,@CStr("F4")    : .endc
      .case 3 : mov esi,@CStr("Alt")   : .endc
      .case 2 : mov esi,@CStr("Ctrl")  : .endc
      .case 1 : mov esi,@CStr("Shift") : .endc
    .endsw

    .if CFGetSection(section)

	.if INIGetEntry(eax, esi)

	    mov esi,eax
	    mov esi,strlen(strnzcpy(addr path, esi, _MAX_PATH - 1))
	    add strlen(edi),esi

	    .if eax < _MAX_PATH

		CFExpandMac(addr path, edi)
		command(addr path)
		mov eax,1
	    .else
		xor eax,eax
	    .endif
	.endif
    .endif
    ret

loadiniproc endp

load_tview proc uses esi edi filename, etype

  local offs
    mov edi,filename

    .if !loadiniproc("View", edi, etype)

	clrcmdl()
	mov esi,edi
	xor eax,eax
	mov offs,eax

	.while	1   ; %view% [-options] [file]

	    lodsb
	    .break .if !al

	    .if al == '"'

		mov edi,esi ; start of "file name"
		.repeat
		    lodsb
		    test al,al
		    jz error
		.until	al == '"'

		xor eax,eax
		mov [esi-1],al
		.break

	    .elseif al == '/' && byte ptr [esi-2] == ' '

		lodsb
		or  al,20h
		.if al == 't'

		    and tvflag,not _TV_HEXVIEW
		.elseif al == 'h'

		    or	tvflag,_TV_HEXVIEW
		.elseif al == 'o'	; -o<offset> - Start offset

		    strtolx(esi)
		    mov offs,eax
		.else
		    jmp error
		.endif

		.repeat
		    lodsb
		.until	al <= ' '

		.break .if !al
		mov edi,esi
	    .endif
	.endw
	tview(edi, offs)
	xor eax,eax
    .endif

toend:
    ret

error:
    ermsg(0, "TVIEW error: %s", edi)
    xor eax,eax
    jmp toend

load_tview endp

TVGetCurrentFile proc uses edi buffer

    xor edi,edi	    ; 0 (F3 or F4)
    mov eax,keyshift
    mov eax,[eax]

    .if eax & SHIFT_KEYSPRESSED

	mov edi,1
    .elseif al & KEY_CTRL   ; 2 (Ctrl)

	mov edi,2
    .elseif al & KEY_ALT    ; 3 (Alt)

	mov edi,3
    .endif

    .if panel_curobj(cpanel)

	xchg eax,ecx
	.if eax & _FB_ARCHIVE

	    .if eax & _A_SUBDIR

		xor eax,eax	; 0 (subdir in archive)
	    .else

		.if eax & _FB_ARCHEXT

		    mov eax,4	; 4 (plugin)
		.else

		    mov eax,2	; 2 (zip)
		.endif
	    .endif
	.elseif eax & _A_SUBDIR

	    mov eax,3		; 3 (subdir)
	.else

	    mov eax,cpanel	    ; 1 (file)
	    mov eax,[eax].S_PANEL.pn_wsub
	    mov eax,[eax].S_WSUB.ws_path

	    strfcat(buffer, eax, ecx)

	    mov eax,1
	.endif
    .endif
    mov ecx,edi
    ret

TVGetCurrentFile endp

unzip_to_temp proc uses esi edi fblk, name_buffer

    mov edi,fblk

    .if envtemp

	progress_open("Unzip file to TEMP", addr cp_copy)
	progress_set(addr [edi].S_FBLK.fb_name, envtemp, [edi].S_FBLK.fb_size)
	mov eax,cpanel
	wsdecomp([eax].S_PANEL.pn_wsub, edi, envtemp)

	.if !progress_close()

	    add edi,S_FBLK.fb_name
	    strfcat(name_buffer, envtemp, edi)
	.else

	    xor eax,eax
	.endif
    .else

	ermsg(0, "Bad or missing TEMP directory")
    .endif

    test eax,eax
    ret

unzip_to_temp endp

viewzip proc uses edi

    mov edi,ecx

    .if unzip_to_temp(edx, ebx)

	load_tview(eax, edi)
	setfattr(ebx, 0)
	remove(ebx)
	mov eax,1
    .endif
    ret

viewzip endp

cmview proc uses ebx

  local fname[_MAX_PATH*2]:byte

    lea ebx,fname

    .switch TVGetCurrentFile(ebx)

      .case 1
	load_tview(ebx, ecx)
	.endc
      .case 2
	viewzip()
	.endc
      .case 4
	mov eax,cpanel
	mov eax,[eax].S_PANEL.pn_wsub
	warcview(eax, edx)
	.endc
      .case 3
	cmsubsize()
	.endc
    .endsw
    ret

cmview endp

    END
