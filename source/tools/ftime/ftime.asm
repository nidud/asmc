include io.inc
include fcntl.inc
include direct.inc
include time.inc
include stdio.inc
include string.inc
include stdlib.inc
include strlib.inc
include winbase.inc

WMAXPATH        equ 2048

.data

time_access     dd 0    ; new time and date
time_create     dd 0
time_modified   dd 0
ff_path         db _MAX_PATH dup(0)
ff_mask         db _MAX_PATH dup(0)
ff_block        _finddata_t <>
do_subdir       dd 0
ex_subdir       dd 0
count           dd 0
fp_maskp        LPSTR 0
scan_fblock     dd 0
scan_curpath    dd 0
scan_curfile    dd 0
DOFILECMD_T     typedef proto __cdecl :LPSTR, :ptr _finddata_t
SUBDIRCMD_T     typedef proto __cdecl :LPSTR
LPDOFILECMD     typedef ptr DOFILECMD_T
LPSUBDIRCMD     typedef ptr SUBDIRCMD_T
fp_directory    LPSUBDIRCMD 0
fp_fileblock    LPDOFILECMD 0

.code

print_usage proc
    printf( "USAGE:     FTIME [-option] [file]\n"
            "\n"
            "/S         Process subfolders\n"
            "/I         Include directories\n"
            "\n"
            "/CD<date>  Creation date:      -cdDD.MM.YY\n"
            "/CT<time>  Creation time:      -ctHH:MM:SS\n"
            "/MD<date>  Modification date:  -mdDD.MM.YY\n"
            "/MT<time>  Modification time:  -mtHH:MM:SS\n"
            "/AD<date>  Last access date:   -adDD.MM.YY\n"
            "\n"
    )
    xor eax,eax
    ret
print_usage endp

scan_directory PROC USES esi edi ebx directory:LPSTR
local result
    xor eax,eax
    mov result,eax
    mov edi,scan_fblock
    add strlen(directory),scan_curpath
    mov ebx,eax
    .if _findfirst(strfcat(scan_curpath, directory, "*.*"), edi) != -1
        mov esi,eax
        .if !_findnext(edi, esi)
            .while !_findnext(edi, esi)
                .continue .if !( BYTE PTR [edi]._finddata_t.attrib & _A_SUBDIR )
                strcpy(&[ebx+1], &[edi]._finddata_t._name)
                scan_directory(scan_curpath)
                mov result,eax
                .break .if eax
            .endw
        .endif
        _findclose(esi)
        mov BYTE PTR [ebx],0
    .endif
    mov eax,result
    .if !eax
        fp_directory(directory)
    .endif
    ret
scan_directory ENDP

scan_files PROC USES esi edi ebx directory:LPSTR
    xor edi,edi
    mov ebx,scan_fblock
    .if _findfirst(strfcat(scan_curfile, directory, fp_maskp), ebx) != -1
        mov esi,eax
        .repeat
            .if !( BYTE PTR [ebx] & _A_SUBDIR )
                fp_fileblock(directory, ebx)
                mov  edi,eax
                .break .if eax
            .endif
        .until _findnext(ebx, esi)
        _findclose(esi)
    .endif
    mov eax,edi
    ret
scan_files ENDP


setftime PROC h:SINT, t:SIZE_T
local FileTime:FILETIME
    .if getosfhnd(h) != -1
        mov edx,eax
        .if SetFileTime(edx, 0, 0, __TimeToFT(t, &FileTime))
            xor eax,eax
        .else
            osmaperr()
        .endif
    .endif
    ret
setftime ENDP

setftime_access PROC h:SINT, t:SIZE_T
local FileTime:FILETIME
    .if getosfhnd(h) != -1
        mov edx,eax
        .if SetFileTime(edx, 0, __TimeToFT(t, &FileTime), 0)
            xor eax,eax
        .else
            osmaperr()
        .endif
    .endif
    ret
setftime_access ENDP

setftime_create PROC h:SINT, t:SIZE_T
local FileTime:FILETIME
    .if getosfhnd(h) != -1
        mov edx,eax
        .if SetFileTime(edx, __TimeToFT(t, &FileTime), 0, 0)
            xor eax,eax
        .else
            osmaperr()
        .endif
    .endif
    ret
setftime_create ENDP

        assume ebx:ptr _finddata_t

do_file proc uses esi ebx directory:LPSTR, ff:ptr _finddata_t
local fname[_MAX_PATH]:byte,taccess,tcreate,tmodified

    mov ebx,ff
    .repeat
        .if !cmpwarg(&[ebx]._name, &ff_mask)
            inc eax
            .break
        .endif
        .if ff
            printf("  %s\n", strfcat(&fname, directory, &[ebx]._name))
            mov taccess,__FTToTime(&[ebx].time_access)
            mov tcreate,__FTToTime(&[ebx].time_create)
            mov tmodified,__FTToTime(&[ebx].time_write)
        .else
            printf("%s\n", strcpy(&fname, directory))
        .endif
        .if _open(&fname,O_WRONLY,NULL) != -1
            mov esi,eax
            mov eax,time_modified
            .if eax
                mov edx,tmodified
                .if ax
                    and edx,0FFFF0000h
                .endif
                .if eax & 0FFFF0000h
                    and edx,00000FFFFh
                .endif
                or edx,eax
                setftime(esi, edx)
            .endif
            mov eax,time_create
            .if eax
                mov edx,tcreate
                .if ax
                    and edx,0FFFF0000h
                .endif
                .if eax & 0FFFF0000h
                    and edx,00000FFFFh
                .endif
                or edx,eax
                setftime_create(esi, edx)
            .endif
            mov eax,time_access
            .if eax
                mov edx,taccess
                .if ax
                    and edx,0FFFF0000h
                .endif
                .if eax & 0FFFF0000h
                    and edx,00000FFFFh
                .endif
                or edx,eax
                setftime_access(esi, edx)
            .endif
            _close(esi)
            inc count
            sub eax,eax
        .endif
    .until  1
    ret
do_file endp

do_files proc directory, ff
    .if do_file(directory,ff) != -1
        sub eax,eax
    .endif
    ret
do_files endp

do_directory proc directory
    .if !scan_files(directory)
        .if !ex_subdir
            do_file(directory, 0)
        .endif
    .else
        mov eax,-1
    .endif
    ret
do_directory endp

set_directory proc directory
local path[_MAX_PATH]:byte
    strfcat(&path, &ff_path, directory)
    .if do_subdir
        scan_directory(&path)
    .elseif ex_subdir
        xor eax,eax
    .else
        do_file(&path, 0)
    .endif
    ret
set_directory endp

readfiles proc uses esi ebx
local ffmask[256]:byte
    lea ebx,ff_block
    mov esi,_findfirst(strfcat(&ffmask, &ff_path, "*.*"), ebx)
    .if esi != -1
        .repeat
            .if [ebx]._name == '.' && [ebx]._name[1] == 0
                .break .if _findnext(esi, ebx)
            .endif
            .if [ebx]._name == '.' && [ebx]._name[2] == 0
                .break .if _findnext(esi, ebx)
            .endif
            .repeat
                .if [ebx].attrib & _A_SUBDIR
                    .break .if set_directory(&[ebx]._name)
                .else
                    do_file(&ff_path, ebx)
                .endif
            .until _findnext(esi, ebx)
        .until 1
        _findclose(esi)
    .endif
    ret
readfiles endp

TTimeToString PROC string:ptr sbyte, tptr:time_t
local SystemTime:SYSTEMTIME

    __TimeToST(tptr, &SystemTime)
    SystemTimeToString(string, &SystemTime)
    ret

TTimeToString ENDP

main proc argc:SINT, argv:ptr
local b[64]:byte

    mov edi,argc
    mov esi,argv

    printf("FTIME Version 1.03\n\n")

    .repeat

        .if edi == 1

            print_usage()
            .break
        .endif

        mov scan_fblock,malloc( sizeof(_finddata_t) + 2 * WMAXPATH )
        add eax,sizeof(_finddata_t)
        mov scan_curfile,eax
        add eax,WMAXPATH
        mov scan_curpath,eax

        mov ff_mask,0
        mov ex_subdir,1
        dec edi
        lodsd

        .repeat

            lodsd
            mov ebx,eax
            mov eax,[ebx]
            .if al == '?'

                print_usage()
                .break(1)
            .endif

            .if al == '/' || al == '-'

                shr eax,8
                or  eax,202020h
                .if al == 'c'

                    .if ah == 'd'

                        atodate(&[ebx+3])
                        or  eax,time_create
                        mov time_create,eax
                    .else
                        atotime(&[ebx+3])
                        or  eax,time_create
                        mov time_create,eax
                    .endif
                .elseif al == 'm'
                    .if ah == 'd'

                        atodate(&[ebx+3])
                        or  eax,time_modified
                        mov time_modified,eax
                    .else
                        atotime(&[ebx+3])
                        or  eax,time_modified
                        mov time_modified,eax
                    .endif
                .elseif al == 'a'
                    .if ah == 'd'

                        atodate(&[ebx+3])
                        or  eax,time_access
                        mov time_access,eax
                    .else
                        atotime(&[ebx+3])
                        or  eax,time_access
                        mov time_access,eax
                    .endif
                .elseif al == 's'
                    inc do_subdir
                .elseif al == 'i'
                    mov ex_subdir,0
                .else
                    print_usage()
                    .break(1)
                .endif
            .else
                strcpy(&ff_path, ebx)
                strfn(eax)
                push eax
                strcpy(&ff_mask, eax)
                pop eax
                .if eax > offset ff_path && byte ptr [eax-1] == '\'

                    mov byte ptr [eax-1],0
                .else
                    mov byte ptr [eax],0
                .endif
            .endif
            dec edi
        .until !edi

        mov eax,time_access
        add eax,time_create
        add eax,time_modified
        .if !eax || !ff_mask

            perror("Nothing to do..")
            sub eax,eax
            .break
        .endif

        .if !ff_path

            .if !_getcwd(&ff_path, _MAX_PATH)

                perror("Error init current path")
                mov eax,1
                .break
            .endif
        .endif

        mov ecx,time_create
        .if ecx & 0x0000FFFF
            printf("   Creation time:       %s\n", TTimeToString(&b, ecx))
        .endif
        mov ecx,time_create
        .if ecx & 0xFFFF0000
            printf("   Creation date:       %s\n", TDateToString(&b, ecx))
        .endif
        mov ecx,time_modified
        .if ecx & 0x0000FFFF
            printf("   Modification time:       %s\n", TTimeToString(&b, ecx))
        .endif
        mov ecx,time_modified
        .if ecx & 0xFFFF0000
            printf("   Modification date:       %s\n", TDateToString(&b, ecx))
        .endif
        mov ecx,time_access
        .if ecx & 0x0000FFFF
            printf("   Last access date time:   %s\n", TTimeToString(&b, ecx))
        .endif
        mov ecx,time_access
        .if ecx & 0xFFFF0000
            printf("   Last access date date:   %s\n", TDateToString(&b, ecx))
        .endif

        printf("\nFile(s):   %s\n", &ff_mask)
        printf("Directory: %s\n\n", &ff_path)
        mov eax,offset ff_mask
        mov fp_maskp,eax
        mov eax,do_files
        mov fp_fileblock,eax
        mov eax,do_directory
        mov fp_directory,eax
        readfiles()
        printf("\nTotal %d files updated\n", count)
        xor eax,eax
    .until 1
    ret

main endp

    end
