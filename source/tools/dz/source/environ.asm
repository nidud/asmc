include io.inc
include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc
include crtl.inc
include malloc.inc
include dzlib.inc

extern _pgmpath:dword
public envpath
public cp_temp
public envtemp

    .data
    envpath dd curpath
    envtemp dd 0
    curpath db ".",0
    cp_temp db "TEMP",0

    .code


; expand '%TEMP%' to 'C:\TEMP'

expenviron PROC USES ecx string:LPSTR

  local buffer

    mov buffer,alloca(0x8000)
    ExpandEnvironmentStrings(string, buffer, 0x8000-1 )
    strcpy(string, buffer)
    ret

expenviron ENDP


getenvp proc uses ecx edx enval:LPSTR

  local buf[2048]:byte

    .if GetEnvironmentVariable(enval, &buf, 2048)

        _strdup(&buf)
    .endif
    ret

getenvp endp


GetEnvironmentSize proc EnvironmentStrings:LPSTR

    mov edx,edi
    mov edi,EnvironmentStrings
    xor eax,eax
    mov ecx,-1
    .while al != [edi]
        repnz scasb
    .endw
    mov edi,edx
    sub eax,ecx
    ret

GetEnvironmentSize endp


GetEnvironmentPATH proc

    .if getenvp("PATH")

        mov ecx,envpath
        mov envpath,eax
        .if ecx != offset envpath
            free(ecx)
        .endif
    .endif
    mov eax,envpath
    ret

GetEnvironmentPATH endp


GetEnvironmentTEMP proc

    free(envtemp)
    getenvp(&cp_temp)
    mov envtemp,eax
    .if !eax
        mov eax,_pgmpath
        .if eax
            mov envtemp,_strdup(eax)
            SetEnvironmentVariable(&cp_temp, eax)
            mov eax,envtemp
        .endif
    .endif
    ret
GetEnvironmentTEMP endp


removefile proc file:LPSTR

    setfattr(file, 0)
    remove(file)
    ret

removefile endp


removetemp proc path:LPSTR

  local nbuf[_MAX_PATH]:byte

    removefile(strfcat(&nbuf, envtemp, path))
    ret

removetemp endp


.pragma init(GetEnvironmentPATH, 101)
.pragma init(GetEnvironmentTEMP, 102)

    END
