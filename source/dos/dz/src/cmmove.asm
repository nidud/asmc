; CMMOVE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include dos.inc
include string.inc
include errno.inc
include conio.inc
include progress.inc

init_copy PROTO pascal :DWORD, :WORD

_COPY_TOZIP	equ 0004h
_COPY_TOARCHIVE equ _COPY_TOZIP

_DZIP	segment

move_initfiles PROC pascal PRIVATE filename:DWORD
	invoke strfcat,addr __outfile,addr __outpath,filename
	invoke strfcat,addr __srcfile,addr __srcpath,filename
	ret
move_initfiles ENDP

move_deletefile PROC pascal PRIVATE result:WORD, flag:WORD
	mov ax,result
	add ax,copy_jump
	.if ax
	    mov ax,result
	    .if !ax
		mov copy_jump,ax
		inc jmp_count
	    .endif
	.else
	    .if BYTE PTR flag & _A_RDONLY
		invoke _dos_setfileattr,addr __srcfile,0
	    .endif
	    invoke remove,addr __srcfile
	    mov ax,result
	.endif
	ret
move_deletefile ENDP

fp_movedirectory PROC _CType PRIVATE directory:DWORD
	.if !progress_set(0,directory,0)
	    invoke _dos_setfileattr,directory,ax
	    .if rmdir(directory)
		sub ax,ax
		.if jmp_count == ax
		    invoke erdelete,directory
		.endif
	    .endif
	.endif
	ret
fp_movedirectory ENDP

fp_movefile PROC _CType PRIVATE directory:DWORD, wfblk:DWORD
	invoke fp_copyfile, directory, wfblk
	les bx,wfblk
	invoke move_deletefile,ax,WORD PTR es:[bx].S_WFBLK.wf_attrib
	ret
fp_movefile ENDP

fblk_movefile PROC pascal PRIVATE fblk:DWORD
	les bx,fblk
	.if !progress_set(addr es:[bx].S_FBLK.fb_name,addr __outpath,es:[bx].S_FBLK.fb_size)
	    .if rename(addr __srcfile,addr __outfile)
		les bx,fblk
		invoke copyfile,es:[bx].S_FBLK.fb_size,WORD PTR es:[bx].S_FBLK.fb_time[2], \
			WORD PTR es:[bx].S_FBLK.fb_time,es:[bx].S_FBLK.fb_flag
		les bx,fblk
		invoke move_deletefile,ax,es:[bx].S_FBLK.fb_flag
	    .endif
	.endif
	ret
fblk_movefile ENDP

fblk_movedirectory PROC pascal PRIVATE USES si di fblk:DWORD
local path[WMAXPATH]:BYTE, fname:DWORD
	lodm fblk
	add ax,S_FBLK.fb_name
	stom fname
	.if !progress_set(dx::ax,addr __outpath,0)
	    invoke move_initfiles,fname
	    .if rename(dx::ax,addr __outfile)
		lea di,path
		invoke strfcat,addr path,addr __srcpath,fname
		movp fp_directory,fp_copydirectory
		.if scansub(addr path,addr cp_stdmask,1)
		    mov ax,-1
		.else
		    .if copy_jump == ax
			movp fp_directory,fp_movedirectory
			invoke scansub,addr path,addr cp_stdmask,0
		    .else
			mov copy_jump,ax
			inc jmp_count
		    .endif
		.endif
	    .endif
	.endif
	ret
fblk_movedirectory ENDP

cmmove PROC _CType PUBLIC
	push si
	push di
	call cpanel_findfirst
	mov di,bx
	mov si,dx
	.if dx
	    .if cx & (_A_ARCHZIP or _A_UPDIR)
		jmp @F
	    .endif
	    .if init_copy(si::di,0)
		.if !(copy_flag & _COPY_IARCHIVE or _COPY_OARCHIVE)
		    mov jmp_count,0
		    movp fp_fileblock,fp_movefile
		    invoke progress_open,addr cp_move,addr cp_move
		    mov es,si
		    mov ax,es:[di]
		    .if ax & _A_SELECTED
			.repeat
			    .if ax & _A_SUBDIR
				invoke fblk_movedirectory,si::di
			    .else
				mov ax,di
				add ax,S_FBLK.fb_name
				invoke move_initfiles,si::ax
				invoke fblk_movefile,si::di
			    .endif
			    .break .if ax
			    mov es,si
			    mov ax,not _A_SELECTED
			    and es:[di],ax
			    mov ax,cpanel
			    .break .if !panel_findnext()
			    mov di,bx
			    mov si,dx
			    mov ax,cx
			.until 0
		    .else
			push si
			push di
			.if ax & _A_SUBDIR
			    call fblk_movedirectory
			.else
			    call fblk_movefile
			.endif
		    .endif
		.else
		    jmp @F
		.endif
		call ret_update_AB
		mov ax,1
	    .endif
	.endif
      @@:
	pop di
	pop si
	ret
cmmove	ENDP

_DZIP	ENDS

_DATA	segment

jmp_count dw 0

_DATA	ENDS

	END
