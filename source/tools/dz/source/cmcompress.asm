; CMCOMPRESS.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include cfini.inc
include string.inc
include crtl.inc

cpyevent_filter proto

PUBLIC	cp_mkzip

    .data

externdef   IDD_DZDecompress:dword
default_arc db "default.7z"
	    db 128-11 dup(0)
cp_backslash db '\',0
cp_alfa	    db '@',0
cp_mkzip    db 'Create archive',0

    .code

PackerGetSection proc private uses esi edi ebx section, result

    .if rsopen(IDD_DZHistory)

	mov ebx,eax
	xor esi,esi

	.if CFGetSection(section)

	    push    ebx
	    mov edi,eax
	    mov ebx,[ebx].S_DOBJ.dl_object

	    .while  INIGetEntryID(edi, esi)

		strnzcpy([ebx].S_TOBJ.to_data, eax, 128-1)
		and [ebx].S_TOBJ.to_flag,not (_O_STATE or _O_LLIST)
		inc esi
		add ebx,sizeof(S_TOBJ)
	    .endw
	    pop ebx
	.endif

	mov eax,esi
	.if eax

	    mov [ebx].S_DOBJ.dl_count,al

	    dlinit(ebx)
	    dlshow(ebx)

	    mov eax,[ebx].S_DOBJ.dl_rect
	    add eax,8
	    mov cl,ah
	    scputf(eax, ecx, 0, 0, "Select External Tool")

	    .if rsevent(IDD_DZHistory, ebx)

		shl eax,4
		strcpy(result, [ebx+eax].S_TOBJ.to_data)
	    .endif
	.endif

	dlclose(ebx)
	mov eax,edx
    .endif
    ret
PackerGetSection endp

cmcompress proc uses esi edi ebx

    local section[128]:byte
    local list[_MAX_PATH]:byte
    local archive[_MAX_PATH]:byte
    local cmd[_MAX_PATH]:byte

    lea esi,archive
    lea edi,default_arc
    lea ebx,cp_compress

    .if cpanel_findfirst() && !(ecx & _FB_ROOTDIR or _FB_ARCHIVE)

	.if cpanel_gettarget()

	    strfcat(esi, eax, edi)

	    .if PackerGetSection(ebx, addr section)

		.if CFGetSectionID(eax, 2)

		    setfext(esi, eax)
		.endif

		.if rsopen(IDD_DZCopy)

		    mov filter,0
		    mov [eax].S_TOBJ.to_data[16],esi
		    mov byte ptr [eax].S_TOBJ.to_count[16],16
		    mov [eax].S_TOBJ.to_proc[3*16],cpyevent_filter

		    wcenter([eax].S_DOBJ.dl_wp, 59, ebx)

		    .if dlmodal(eax)

			;------------------------------------------
			; no unix path, no mask in directory\[*.*]
			;------------------------------------------

			mov eax,mklist.mkl_flag
			and eax,not (_MKL_UNIX or _MKL_MASK)
			mov mklist.mkl_flag,eax

			.if mkziplst_open()

			    strcpy(addr list, edx)
			    .if mkziplst()

				xor eax,eax
			    .else

				or  eax,mklist.mkl_count
			    .endif
			.endif

			.if eax

			    strcpy(edi, strfn(esi))
			    lea ebx,section

			    .if CFGetSectionID(ebx, 0)

				lea edi,cmd
				lea edx,cp_space
				strcat(strcat(strcat(strcpy(edi, eax), edx), esi), edx)

				.if !CFGetSectionID(ebx, 1)

				    lea eax,cp_alfa
				.endif

				strcat(edi, eax)
				command(strcat(edi, addr list))
			    .endif
			.endif
		    .endif
		.endif
	    .endif
	.endif
    .endif
    ret
cmcompress endp

cmdecompress proc uses esi edi ebx

    local archive:dword
    local section[128]:byte
    local cmd[_MAX_PATH]:byte
    local path[_MAX_PATH]:byte

    lea esi,path
    lea ebx,section

    .if cpanel_findfirst() && !(ecx & _A_SUBDIR or _FB_ROOTDIR or _FB_ARCHIVE)

	mov archive,eax

	.if cpanel_gettarget()

	    strcpy(esi, eax)

	    .if PackerGetSection(addr cp_decompress, ebx)

		.if rsopen(IDD_DZDecompress)

		    mov edi,eax
		    mov [edi].S_TOBJ.to_count[16],256/16
		    mov [edi].S_TOBJ.to_data[16],esi

		    dlinit(edi)
		    dlshow(edi)

		    mov ax,[edi+4]
		    add ax,020Eh
		    mov dl,ah
		    scpath(eax, edx, 50, archive)

		    .if dlmodal(edi)

			.if CFGetSectionID(ebx, 0)

			    lea edi,cmd
			    strcat(strcpy(edi, eax), addr cp_space)

			    .if CFGetSectionID(ebx, 1)

				lea edx,path
				lea esi,cp_space
				mov ebx,archive
			    .else

				mov eax,archive
				lea edx,cp_space
				lea ebx,cp_backslash
			    .endif

			    strcat(strcat(strcat(edi, eax), edx), ebx)
			    command(strcat(eax, esi))
			.endif
		    .endif
		.endif
	    .endif
	.endif
    .endif
if 0
    .switch
      .case !cpanel_findfirst()
      .case ecx & _A_SUBDIR or _FB_ROOTDIR or _FB_ARCHIVE
	.endc
      .default
	mov archive,eax
	.endc .if !cpanel_gettarget()
	strcpy(esi, eax)

	.endc .if !PackerGetSection(addr cp_decompress, ebx)
	.endc .if !rsopen(IDD_DZDecompress)
	mov edi,eax

	mov [edi].S_TOBJ.to_count[16],256/16
	mov [edi].S_TOBJ.to_data[16],esi
	dlinit(edi)
	dlshow(edi)
	mov ax,[edi+4]
	add ax,020Eh
	mov dl,ah
	scpath(eax, edx, 50, archive)

	.endc .if !dlmodal(edi)
	.endc .if !inientryid(ebx, 0)

	lea edi,cmd
	strcat(strcpy(edi, eax), addr cp_space)
	.if inientryid(ebx, 1)
	    lea edx,path
	    lea esi,cp_space
	    mov ebx,archive
	.else
	    mov eax,archive
	    lea edx,cp_space
	    lea ebx,cp_backslash
	.endif
	strcat(strcat(strcat(edi, eax), edx), ebx)
	command(strcat(eax, esi))
	.endc
    .endsw
endif
    ret
cmdecompress endp

    END
