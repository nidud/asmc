include string.inc
include malloc.inc
include cfini.inc
include stdlib.inc
include winbase.inc
include dzlib.inc
include io.inc
include process.inc
include iost.inc
include consx.inc
include stdio.inc
include crtl.inc

extern  __comspec:byte

    .data
    __CFBase LPINI 0

    .code

__CFExpandCmd proc uses esi edi ini:LPINI, buffer:LPSTR, file:LPSTR

  local tmp

    mov tmp,alloca(0x8000)
    mov edi,eax
    mov esi,eax

    .if strrchr(strcpy(esi, strfn(file)), '.')

        .if byte ptr [eax+1] == 0

            mov byte ptr [eax],0
        .else

            lea esi,[eax+1]
        .endif
    .endif

    .if INIGetEntry(ini, esi)

        mov esi,eax
        strcpy(edi, eax)

        ExpandEnvironmentStrings(esi, edi, 0x8000 - 1)
        CFExpandMac(edi, file)
        strxchg(edi, ", ", "\r\n")
        strcpy(buffer, edi)
    .endif
    ret

__CFExpandCmd endp


__CFGetComspec proc uses esi edi ebx ini:LPINI, value:UINT

  local buffer[512]:byte

    mov esi,value
    mov comspec_type,esi

    __initcomspec()
    strcpy(__pCommandArg, "/C")

    .if esi

        .if INIGetSection(ini, addr __comspec)

            mov esi,eax
            lea ebx,buffer

            .if INIGetEntryID(esi, 0)

                .if !_access(expenviron(strcpy(ebx, eax)), 0)

                    free(__pCommandCom)
                    mov __pCommandCom,_strdup(ebx)

                    mov eax,__pCommandArg
                    mov byte ptr [eax],0

                    .if INIGetEntryID(esi, 1)

                        expenviron(strcpy(ebx, eax))
                        strncpy(__pCommandArg, eax, 64-1)
                    .endif
                .endif
            .endif
        .endif
    .endif
    mov eax,__pCommandCom
    ret

__CFGetComspec endp



CFError proc section:LPSTR, entry:LPSTR

    ermsg("Bad or missing Entry in .INI file",
        "Section: [%s]\nEntry: [%s]", section, entry)
    ret

CFError endp


CFRead proc file:LPSTR

    mov __CFBase,INIRead(__CFBase, file)
    ret

CFRead endp


CFReadFileName proc uses esi edi ebx ini:LPINI, index:PVOID, file_flag:UINT

  local buffer[1024]:sbyte

    mov eax,index
    mov ebx,[eax]
    xor edi,edi

    .while INIGetEntryID(ini, ebx)

        mov esi,eax
        inc ebx

        mov edi,index
        add edi,4

        .while strchr(esi, ',')

            mov ecx,esi
            lea esi,[eax+1]
            __xtol(ecx)
            stosd
        .endw
        xor edi,edi

        ExpandEnvironmentStrings(esi, strcpy(&buffer, esi), 1024)

        lea esi,buffer
        .if filexist(esi) == file_flag

            mov edi,_strdup(esi)
            .break
        .endif
    .endw

    mov eax,index
    mov [eax],ebx
    mov eax,edi
    ret

CFReadFileName endp


CFWrite proc file:LPSTR

    mov eax,__CFBase
    .if eax

        INIWrite(eax, file)
    .endif
    ret

CFWrite endp


CFGetSection proc section:LPSTR

    mov eax,__CFBase
    .if eax

        INIGetSection(eax, section)
    .endif
    ret

CFGetSection endp


CFGetSectionID proc section:LPSTR, id:UINT

    mov eax,__CFBase
    .if eax

        .if INIGetSection(eax, section)

            INIGetEntryID(eax, id)
        .endif
    .endif
    ret

CFGetSectionID endp


CFAddSection proc __section:LPSTR

    mov eax,__CFBase
    .if eax

        INIAddSection(eax, __section)
    .endif
    ret

CFAddSection endp


CFAddSectionX proc C format:LPSTR, argptr:VARARG


    mov eax,__CFBase
    .if eax

        .if ftobufin(format, addr argptr)

            INIAddSection(__CFBase, edx)
        .endif
    .endif
    ret

CFAddSectionX endp


CFGetComspec proc value:UINT

    mov eax,__CFBase
    .if eax

        __CFGetComspec(eax, value)
    .endif
    ret

CFGetComspec endp


CFExpandCmd proc buffer:LPSTR, file:LPSTR, section:LPSTR

    mov eax,__CFBase
    .if eax

        .if INIGetSection(eax, section)

            __CFExpandCmd(eax, buffer, file)
        .endif
    .endif
    ret

CFExpandCmd endp


CFExecute proc uses esi ini:LPINI

  local cmd[256]:byte

    xor esi,esi

    .while INIGetEntryID(ini, esi)

        mov edx,eax
        system(strcpy(addr cmd, edx))
        inc esi
    .endw
    ret

CFExecute endp

;
; File macros:
;
;    !!     !
;    !:     Drive + ':'
;    !\     Long path
;    !      Long file name
;    .!     Long extension
;    .!~    Short extension
;    !~\    Short path
;    ~!     Short file name
;

CFExpandMac proc uses esi edi ebx string:LPSTR, file:LPSTR

  local longpath, longfile, shortpath, shortfile, S2, S1, drive

    .if !strchr(string, '!')

        ; "<string> <file>"
        ; "<string> "<file name>""

        lea ebx,S1
        mov eax,'" '
        mov [ebx],eax
        mov esi,strchr(file, ' ')

        .if !eax

            mov [ebx+1],al
        .endif

        strcat(strcat(string, ebx), file)

        .if esi

            inc ebx
            strcat(eax, ebx)
        .endif
        .return
    .endif

    mov longpath,alloca(WMAXPATH*2)
    mov edi,eax
    mov ecx,WMAXPATH*2
    add eax,WMAXPATH
    mov shortpath,eax
    xor eax,eax
    rep stosb

    GetFullPathName(file, WMAXPATH, strcpy(longpath, file), 0)

    xor eax,eax
    mov drive,eax
    mov edi,longpath
    mov ebx,[edi]

    .if bl != '\' && bh != ':'

        .return .if !GetCurrentDirectory(WMAXPATH, shortpath)

        strfcat(longpath, shortpath, file)
    .endif

    GetShortPathName(edi, strcpy(shortpath, edi), WMAXPATH)

    .if bh == ':'

        mov word ptr drive,bx
        strcpy(edi, addr [edi+3])
        mov ecx,shortpath
        strcpy(ecx, addr [ecx+3])
    .endif

    lea esi,S1
    lea edi,S2
    mov ebx,string

    ; remove <!!>

    mov dword ptr [esi],"!!"
    mov dword ptr [edi],"››"
    strxchg(ebx, esi, edi)

    ; xchg <!:> -- <<drive>:>

    mov byte ptr [esi+1],':'
    strxchg(ebx, esi, addr drive)

    ; xchg <.!~> -- <Short extension>

    xor eax,eax
    mov [edi],eax
    mov dword ptr [esi],"~!."
    strext(shortpath)
    mov edx,edi
    .if eax
        mov edx,eax
    .endif
    push edx
    strxchg(ebx, esi, edx)
    pop edx

    ; remove short extension

    .if edx != edi

        mov byte ptr [edx],0
    .endif

    ; xchg <.!> -- <Long extension>

    mov dword ptr [esi],"!."
    strext(longpath)
    mov edx,edi
    .if eax
        mov edx,eax
    .endif
    push    edx
    strxchg(ebx, esi, edx)
    pop edx

    ; remove long extension

    .if edx != edi

        mov byte ptr [edx],0
    .endif

    mov shortfile,strfn(shortpath)
    .if eax == shortpath

        mov shortpath,edi
    .else

        mov byte ptr [eax-1],0
    .endif

    mov longfile,strfn(longpath)
    .if eax == longpath

        mov longpath,edi
    .else

        mov byte ptr [eax-1],0
    .endif

    ; xchg <!\> -- <Long path>

    mov dword ptr [esi],"\!"
    strxchg(ebx, esi, longpath)

    ; xchg <!~\> -- <Short path>

    mov dword ptr [esi],"\~!"
    strxchg(ebx, esi, shortpath)

    ; xchg <!~> -- <Short file>

    mov dword ptr [esi],"!~"
    strxchg(ebx, esi, shortfile)

    ; xchg <!> -- <Long file>

    mov dword ptr [esi],"!"
    strxchg(ebx, esi, longfile)

    ; xchg <››> -- <!>

    mov dword ptr [esi],"››"
    mov dword ptr [edi],"!"
    strxchg(ebx, esi, edi)
    ret

CFExpandMac endp


CFClose proc

    mov eax,__CFBase
    .if eax

        INIClose(eax)
        mov __CFBase,0
    .endif
    ret

CFClose endp

    END
