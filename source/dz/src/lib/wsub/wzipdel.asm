include string.inc
include wsub.inc
include iost.inc
include zip.inc
include confirm.inc
include progress.inc
include errno.inc

extern  cp_ziptemp:BYTE

        .code

        assume edi:ptr S_FBLK
        assume ebx:ptr S_WSUB

wzipdel PROC USES esi edi ebx wsub, fblk

    mov ebx,wsub    ; EBX = wsub
    mov edi,fblk    ; EDI = fblk
    xor esi,esi     ; ESI set if repeated call with same directory

    .while 1
        mov eax,entryname
        .if !esi
            mov ecx,[edi].fb_flag
            lea eax,[edi].fb_name
            .if cl & _A_SUBDIR
                confirm_delete_sub(eax)
            .else
                confirm_delete_file(eax, ecx)
            .endif
            .break .if !eax      ; 0: Skip file
            .break .if eax == -1 ; -1: Cancel
            strfcat(__srcfile, [ebx].ws_path, [ebx].ws_file)
            setfext(strcpy(__outfile, eax), addr cp_ziptemp)
            strfcat(__outpath, [ebx].ws_arch, addr [edi].fb_name)
            dostounix(eax)
            .if BYTE PTR [edi].fb_flag & _A_SUBDIR
                strcat(eax, "/")
            .endif
            .if !strcmp(__srcfile, __outfile)
                erdelete(__outpath)
                .break
            .endif
            mov eax,__outpath
        .endif

        mov edx,zip_flength
        xor ecx,ecx
        .break .if progress_set(eax, __srcfile, ecx::edx)
        .break .if wscopyopen(__srcfile, __outfile) == -1
        and STDO.ios_flag,IO_GLMEM
        or  STDO.ios_flag,IO_UPDTOTAL or IO_USEUPD
        .if eax
            ;
            ; copy compressed data to temp file
            ;
            ; 0: match directory\*.*
            ; 1: exact match -- file or directory/
            ;
            xor esi,1
            .if zip_copylocal(esi) != -1
                ;
                ; local offset to Central directory in DX
                ;
                mov eax,DWORD PTR STDO.ios_total
                add eax,STDO.ios_i
                mov ecx,zip_endcent.ze_off_cent
                mov zip_endcent.ze_off_cent,eax
                sub ecx,eax
                .if zip_copycentral(edx, ecx, esi) == 1
                    ;
                    ; must be found..
                    ;
                    ;-------- End Central Directory
                    ;
                    dec zip_endcent.ze_entry_dir
                    dec zip_endcent.ze_entry_cur
                    mov eax,__srcfile
                    mov edx,__outfile
                    zip_copyendcentral()
                    test eax,eax
                    jz next
                .endif
            .endif
        .endif
        ioclose(addr STDI)
        wscopyremove(__outfile)
        xor esi,1
        mov eax,esi
        .if eax && !([edi].fb_flag & _A_SUBDIR)
            erdelete(__outpath)
        .endif
        .break .if eax
next:
        .break .if !([edi].fb_flag & _A_SUBDIR)
        mov esi,1
    .endw
    ret

wzipdel endp

        end
