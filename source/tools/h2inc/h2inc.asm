; H2INC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2024-04-11 - Added switch -Fo <path>
; 2024-04-09 - Added RECORD/ENDS handling
; 2024-03-30 - Added Linux GLIB and LIBASMC
; 2023-03-08 - added namespace and interface for Windows 10
;

include stdio.inc
include stdlib.inc
include string.inc
include io.inc
include malloc.inc
include direct.inc
ifdef __UNIX__
define __USE_GNU
include ucontext.inc
else
include winbase.inc
endif
include signal.inc
include setjmp.inc
include tchar.inc

define LTYPE_INLINE
include ltype.inc

    option dllimport:none

define __H2INC__    112

define MAXLINE      512
define MAXBUF       0x100000
define MAXARGS      20
define MAXLSTRUCTS  2048

define FL_STBUF     0x01
define FL_STRUCT    0x02
define FL_ENUM      0x04
define FL_TYPEDEF   0x08
define FL_RECORD    0x10

.enum token_type {
    T_EOF,
    T_BLANK,
    T_ID,
    T_STRUCT,
    T_UNION,
    T_TYPEDEF,
    T_ENUM,
    T_IF,
    T_ELSE,
    T_ENDIF,
    T_ENDS,
    T_INCLUDE,
    T_DEFINE,
    T_UNDEF,
    T_ERROR,
    T_PRAGMA,
    T_NAMESPACE,
    T_INTERFACE,
    T_MIDL_INTERFACE, ; Windows 10
    T_EXTERN,
    T_INLINE,
    T_DEFINE_GUID
    }

parseline proto

.data

 jmpenv     _JUMP_BUFFER <>
 ercount    dd 0

 banner     db 0
 option_q   db 0            ; -q
 option_n   db 0            ; -nologo
 option_m   db 0            ; -nomacro
 option_b   db 0            ; -b
 stoptions  db 0

 align 8
 option_c   string_t NULL   ; -c<calling_convention>
 option_v   string_t NULL   ; -v<calling_convention>
 option_f   string_t MAXARGS dup(NULL)
 option_w   string_t MAXARGS dup(NULL)
 option_s   string_t MAXARGS dup(NULL)
 option_r   string_t MAXARGS*2 dup(NULL)
 option_o   string_t MAXARGS*2 dup(NULL)
 option_Fo  string_t NULL

 tokpos     string_t ?
 linebuf    string_t NULL
 filebuf    string_t NULL
 tempbuf    string_t NULL
 srcfile    ptr FILE NULL
 outfile    ptr FILE NULL
 curfile    string_t NULL
 curline    dd 1
 csize      dd ?
 cflags     db ?
 ctoken     db ?
 clevel     db ?
 cstart     db 0
 cblank     db 0
 unicode    db 0


T macro s
% exitm<@CStr("&s&")>
  endm
  align 8
reswords string_t \
    T(add),
    T(addr),
    T(ax),
    T(bp),
    T(bx),
    T(byte),
    T(ch),
    T(comment),
    T(cx),
    T(di),
    T(div),
    T(dr0),
    T(dr1),
    T(dr2),
    T(dr3),
    T(dr4),
    T(dr5),
    T(dr6),
    T(dr7),
    T(dword),
    T(dx),
    T(eax),
    T(ebp),
    T(ebx),
    T(ecx),
    T(edi),
    T(edx),
    T(eip),
    T(end),
    T(enter),
    T(esi),
    T(esp),
    T(fabs),
    T(far),
    T(fs),
    T(group),
    T(highword),
    T(if),
    T(in),
    T(int),
    T(invoke),
    T(lock),
    T(mm),
    T(mul),
    T(near),
    T(offset),
    T(out),
    T(pascal),
    T(proc),
    T(push),
    T(rcl),
    T(segment),
    T(si),
    T(sp),
    T(st),
    T(str),
    T(tbyte),
    T(wait),
    T(word),
    NULL

knownstructs string_t \
    T(ACE_HEADER),
    T(AD_GENERAL_PARAMS),
    T(AD_GUARANTEED),
    T(BITMAP),
    T(BITMAPCOREHEADER),
    T(BITMAPINFOHEADER),
    T(CERT_ALT_NAME_INFO),
    T(CERT_NAME_BLOB),
    T(CERT_PUBLIC_KEY_INFO),
    T(CERT_RDN_VALUE_BLOB),
    T(CIEXYZ),
    T(CIEXYZTRIPLE),
    T(CLSID),
    T(CMSG_SIGNED_ENCODE_INFO),
    T(CMSG_ENVELOPED_ENCODE_INFO),
    T(COLORADJUSTMENT),
    T(CONTROL_SERVICE),
    T(CONVCONTEXT),
    T(COORD),
    T(CREATE_PROCESS_DEBUG_INFO),
    T(CREATE_THREAD_DEBUG_INFO),
    T(CRL_DIST_POINT_NAME),
    T(CRYPT_ALGORITHM_IDENTIFIER),
    T(CRYPT_ATTRIBUTES),
    T(CRYPT_DATA_BLOB),
    T(CRYPT_OBJID_BLOB),
    T(CTL_USAGE),
    T(DCB),
    T(DDEML_MSG_HOOK_DATA),
    T(DESIGNVECTOR),
    T(ELEMDESC),
    T(EMR),
    T(EMRTEXT),
    T(ENUMLOGFONTEXA),
    T(ENUMLOGFONTEXW),
    T(EVENTLOGRECORD),
    T(EXCEPTION_DEBUG_INFO),
    T(EXCEPTION_RECORD),
    T(EXIT_PROCESS_DEBUG_INFO),
    T(EXIT_THREAD_DEBUG_INFO),
    T(EXTLOGFONTW),
    T(EXTLOGPEN),
    T(FILETIME),
    T(FIXED),
    T(FLOATING_SAVE_AREA),
    T(FLOWSPEC),
    T(FOCUS_EVENT_RECORD),
    T(FONTSIGNATURE),
    T(GUID),
    T(HARDWAREINPUT),
    T(IDLDESC),
    T(IID),
    T(IMAGE_DATA_DIRECTORY),
    T(IMAGE_FILE_HEADER),
    T(IMAGE_OPTIONAL_HEADER32),
    T(IMAGE_OPTIONAL_HEADER64),
    T(IMAGE_ROM_OPTIONAL_HEADER),
    T(IN_ADDR_IPV4),
    T(IN_ADDR_IPV6),
    T(KEYBDINPUT),
    T(KEY_EVENT_RECORD),
    T(LARGE_INTEGER),
    T(LIST_ENTRY),
    T(LOAD_DLL_DEBUG_INFO),
    T(LOGBRUSH),
    T(LOGCOLORSPACEW),
    T(LOGFONTA),
    T(LOGFONTW),
    T(LOGPALETTE),
    T(LOGPEN),
    T(LUID),
    T(LUID_AND_ATTRIBUTES),
    T(MENU_EVENT_RECORD),
    T(MESSAGE_RESOURCE_BLOCK),
    T(MOUSEINPUT),
    T(MOUSE_EVENT_RECORD),
    T(NEWTEXTMETRICA),
    T(NEWTEXTMETRICW),
    T(NEWTEXTMETRICEXA),
    T(NEWTEXTMETRICEXW),
    T(NMHDR),
    T(OUTPUT_DEBUG_STRING_INFO),
    T(PALETTEENTRY),
    T(PANOSE),
    T(PARAMDESC),
    T(PARAM_BUFFER),
    T(PIXELFORMATDESCRIPTOR),
    T(POINT),
    T(POINTFLOAT),
    T(POINTFX),
    T(POINTL),
    T(POINTS),
    T(PRINTER_NOTIFY_INFO_DATA),
    T(QOS_OBJECT_HDR),
    T(RECT),
    T(RECTL),
    T(RGBQUAD),
    T(RGBTRIPLE),
    T(RGNDATAHEADER),
    T(RIP_INFO),
    T(RSVP_FILTERSPEC_V4),
    T(RSVP_FILTERSPEC_V4_GPI),
    T(RSVP_FILTERSPEC_V6),
    T(RSVP_FILTERSPEC_V6_FLOW),
    T(RSVP_FILTERSPEC_V6_GPI),
    T(SECURITY_QUALITY_OF_SERVICE),
    T(SERVICE_STATUS),
    T(SID_AND_ATTRIBUTES),
    T(SID_IDENTIFIER_AUTHORITY),
    T(SIZEL),
    T(SMALL_RECT),
    T(SOCKET_ADDRESS),
    T(STGMEDIUM),
    T(SYSTEMTIME),
    T(TEXTMETRICA),
    T(TEXTMETRICW),
    T(TOKEN_SOURCE),
    T(TRIVERTEX),
    T(TYPEDESC),
    T(UNLOAD_DLL_DEBUG_INFO),
    T(WAVEFORMAT),
    T(WCRANGE),
    T(WINDOW_BUFFER_SIZE_RECORD),
    T(WSABUF),
    T(WSAPROTOCOLCHAIN),
    T(XFORM),
    NULL

.data?
 reswbuf    char_t 32 dup(?)
 lstructa   string_t MAXLSTRUCTS dup(?)
 lstructs   int_t ?


.code

write_logo proc

    .if ( !banner )

        mov banner,1
        printf(
            "Asmc C Include File Translator %d.%d\n"
            "Copyright (C) The Asmc Contributors. All Rights Reserved.\n\n",
            __H2INC__ / 100, __H2INC__ mod 100)
    .endif
    ret

write_logo endp


write_usage proc

    write_logo()
    printf("Usage: h2inc [ options ] filename\n")
    ret

write_usage endp


exit_usage proc

    write_usage()
    exit(0)

exit_usage endp


exit_options proc

    write_usage()
    printf(
        "\n"
        "-q              -- Operate quietly\n"
        "-nologo         -- Suppress copyright message\n"
        "-c<string>      -- Specify string (calling convention) for PROTO\n"
        "-v<string>      -- Specify string for PROTO using VARARG\n"
        "-b              -- Add <brackets> on define <ID>\n"
        "-m              -- Skip empty macro lines followed by a blank\n"
        "-f<functon>     -- Strip functon: -f__attribute__\n"
        "-Fo<path>       -- Name of output file (default is <input>.inc)\n"
        "-w<word>        -- Strip word (a valid identifier)\n"
        "-s<string>      -- Strip string\n"
        "-r<old> <new>   -- Replace string\n"
        "-o<old> <new>   -- Replace output string\n"
        "@               -- Specifies a response file or %%environ%%\n"
        "\n"
        "Note that \"quotes\" are stripped so use -r\"\\\"old\\\"\" \"\\\"new\\\"\" to replace\n"
        "actual \"quoted strings\".\n\n"
        )

    exit(0)

exit_options endp


strtrim proc string:string_t

    .if strlen(string)

        lea ecx,[rax-1]
        mov edx,eax
        add rcx,string

        .while islspace([rcx])

            mov [rcx],ah
            dec rcx
            dec edx
        .endw
        mov eax,edx
    .endif
    ret

strtrim endp


prevtok proc string:string_t, start:string_t

    ldr rcx,string
    ldr rdx,start

    .while ( rcx >= rdx && !isclabel([rcx]) )
        dec rcx
    .endw
    .while ( rcx >= rdx && isclabel([rcx]) )
        dec rcx
    .endw
    inc  rcx
    xchg rcx,rax
    ret

prevtok endp


prevtokz proc string:string_t, start:string_t

    ldr rcx,string
    ldr rdx,start

    .while ( rcx >= rdx && !isclabel([rcx]) )
        mov [rcx],ah
        dec rcx
    .endw
    .while ( rcx >= rdx && isclabel([rcx]) )
        dec rcx
    .endw
    inc  rcx
    xchg rcx,rax
    ret

prevtokz endp


nexttok proc string:string_t

    ldr rcx,string
    .repeat
        .if ( isclabel([rcx]) )
            inc rcx
            .while isclabel([rcx])
                inc rcx
            .endw
            .break
        .endif
        .if ( islpunct([rcx]) )
            inc rcx
        .endif
    .until 1
    ltokstart(rcx)
    ret

nexttok endp


toksize proc string:string_t

    ldr rcx,string
    mov rdx,rcx
    .if ( isclabel0([rcx]) )
        inc rcx
        .while isclabel([rcx])
            inc rcx
        .endw
    .endif
    xchg rax,rcx
    sub rax,rdx
    ret

toksize endp


stripval proc uses rbx string:string_t

    ; strip (0U-199U) | 0x40000000000UI64

    ldr rbx,string
    .while [rbx]

        .while !isldigit([rbx])
            mov rbx,nexttok(rbx)
            .break(1) .if !cl
        .endw
        inc rbx
        .if ( [rbx] == 'x' )
            inc rbx
        .endif

        .for ( : islxdigit([rbx]) : rbx++ )
        .endf
        .break .if !al
        .continue .if !islalpha([rbx])

        mov rcx,rbx
        .for ( : islalnum([rbx]) : rbx++ )
        .endf
        mov rdx,rbx
        mov rbx,rcx
        strcpy(rcx, rdx)
    .endw
    .return(string)

stripval endp


; #define CN_EVENT ((UINT)(-2))

striptype proc uses rbx string:string_t

    ldr rbx,string

    .while 1

        .break .if !strchr(rbx, '(')
        .ifd ( ltokstartc(&[rax+1]) != '(' )
            mov rbx,rcx
           .continue
        .endif
        mov rbx,rcx
        mov rdx,ltokstart(&[rcx+1])
        .if ( cl == '(' )
            mov rbx,rax
            mov rdx,ltokstart(&[rax+1])
        .endif

        .ifd ( !isclabel0([rdx]) )
            mov rbx,rdx
           .continue
        .endif
        inc rdx
        .while isclabel([rdx])
            inc rdx
        .endw
        .whiled ( ltokstartc(rdx) == '*' )
            inc rdx
        .endw
        .if ( al != ')' )
            mov rbx,rcx
            .continue
        .endif
        inc rdx
        .ifd ( ltokstartc(rdx) != '(' )
            lea rbx,[rdx+1]
           .continue
        .endif
        mov rcx,rbx
        lea rbx,[rdx+1]
        strcpy(rcx, rdx)
    .endw
    ret

striptype endp


wordxchg proc uses rbx r12 r13 r14 string:string_t, token:string_t, new:string_t

   .new retval:int_t = 0

    ldr r12,string
    ldr rcx,token
    mov r14,tempbuf
    mov ebx,strlen(rcx)

    .while strstr(r12, token)

        mov r13,rax

        .ifd !isclabel([r13-1])

            .ifd !isclabel([r13+rbx])

                inc retval
                mov [r13],0
                strcpy(r12, strcat(strcat(strcpy(r14, r12), new), &[r13+rbx]))
            .endif
        .endif
        lea r12,[r13+rbx]
    .endw
    .return(retval)

wordxchg endp


strxchg proc uses rbx r12 r13 r14 r15 string:string_t, token:string_t, new:string_t

    ldr r12,string
    ldr r14,token
    ldr r15,new
    mov ebx,strlen(r14)

    .while strstr(r12, r14)

        mov r13,rax
        strcpy(tempbuf, &[r13+rbx])
        lea r12,[r13+strlen(strcpy(r13, r15))]
        strcat(r13, tempbuf)
    .endw
    ret

strxchg endp


arg_option_f proc uses rbx r12 r13 r14 string:string_t

    ldr r13,string

    .for ( r12d = 0 : r12d < MAXARGS : r12d++ )

        lea rax,option_f
        mov r14,[rax+r12*8]

        .break .if !r14
        .continue .if !strstr(r13, r14)

        mov rbx,rax
        mov rdx,strlen(r14)
        .if ( [rbx-1] == ' ' )
            dec rbx
            inc rdx
        .endif
        add rdx,rbx
        mov rdx,ltokstart(rdx)

        mov al,[rdx]
        .if ( al == '(' )

            .for ( ecx = 0 : al : rdx++, al = [rdx] )

                .if ( al == '(' )
                    inc ecx
                .elseif ( al == ')' )
                    dec ecx
                    .ifz
                        inc rdx
                        .break
                    .endif
                .endif
            .endf
        .endif
        strcpy(rbx, rdx)
    .endf
    ret

arg_option_f endp


arg_option_s proc uses rbx r12 string:string_t

    ldr r12,string

    .for ( ebx = 0 : ebx < MAXARGS : ebx++ )

        lea rax,option_s
        mov rcx,[rax+rbx*8]

        .break .if !rcx

        strxchg(r12, rcx, "")
    .endf
    ret

arg_option_s endp


arg_option_w proc uses rbx r12 string:string_t

    ldr r12,string

    .for ( ebx = 0 : ebx < MAXARGS : ebx++ )

        lea rax,option_w
        mov rcx,[rax+rbx*8]

        .break .if !rcx

        wordxchg(r12, rcx, "")
    .endf
    ret

arg_option_w endp


arg_option_r proc uses rbx r12 string:string_t

    ldr r12,string
    .for ( ebx = 0 : ebx < MAXARGS : ebx++ )

        lea rax,option_r
        lea rdx,[rbx*8]
        mov rcx,[rax+rdx*2]

        .break .if !rcx
        mov rdx,[rax+rdx*2+8]
        strxchg(r12, rcx, rdx)
    .endf
    ret

arg_option_r endp


arg_option_o proc uses rbx r12 string:string_t

    ldr r12,string
    .for ( ebx = 0 : ebx < MAXARGS : ebx++ )

        lea rax,option_o
        lea rdx,[rbx*8]
        mov rcx,[rax+rdx*2]

        .break .if !rcx
        mov rdx,[rax+rdx*2+8]
        strxchg(r12, rcx, rdx)
    .endf
    ret

arg_option_o endp


operator proc uses rbx r12 r13 r14 string:string_t, token:string_t, new:string_t

    ldr r12,string
    ldr r13,token
    mov ebx,strlen(r13)

    .while strstr(r12, r13)

        mov [rax],0
        mov r14,ltokstart(&[rax+rbx])
        strtrim(r12)
        strcpy(r12, strcat(strcat(strcpy(tempbuf, r12), new), r14))
    .endw
    ret

operator endp


convert proc uses rbx string:string_t

    ldr rbx,string

    striptype(rbx)
    stripval(rbx)

    operator(rbx, "<<", " shl ")
    operator(rbx, ">>", " shr ")
    operator(rbx, "==", " eq ")
    operator(rbx, ">=", " ge ")
    operator(rbx, "<=", " le ")
    operator(rbx, "->", ".")
    operator(rbx, "||", " or ")
    operator(rbx, "&&", " and ")
    operator(rbx, ">",  " gt ")
    operator(rbx, "<",  " lt ")
    operator(rbx, "|",  " or ")
    operator(rbx, "&",  " and ")
    operator(rbx, "!=", " ne ")
    operator(rbx, "!",  " not ")
    operator(rbx, "~",  " not ")
    arg_option_o(rbx)
   .return(rbx)

convert endp


oprintf proc format:string_t, args:vararg

    mov cblank,0
    .if ( cflags & FL_STBUF )

        mov rcx,strlen(filebuf)
        add rcx,filebuf
        .return vsprintf(rcx, format, &args)
    .endif

     mov cstart,1
    .return vfprintf(outfile, format, &args)

oprintf endp


error proc string:string_t

    ldr rcx,string
    inc ercount
    printf("%s(%d) : error : %s\n", curfile, curline, rcx)
    ret

error endp


errexit proc string:string_t

    .if ( srcfile )
        fclose(srcfile)
    .endif
    .if ( outfile )
        fclose(outfile)
    .endif
    printf("%s(%d) : fatal error : %s\n", curfile, curline, string)
    exit(1)
    ret

errexit endp


eofexit proc

    .if ( cflags & FL_STBUF )

        fprintf(outfile, filebuf)
    .endif
    longjmp(&jmpenv, 1)
    ret

eofexit endp


getline proc uses rbx r12 buffer:string_t

   .new comment_section:byte = 0

    ldr rbx,buffer

    .while 1

        .if !fgets(rbx, MAXLINE, srcfile)
            eofexit()
        .endif

        inc curline

        .if comment_section
            .if strstr(rbx, "*/")
                strcpy(rbx, &[rax+2])
                dec comment_section
            .else
                .continue
            .endif
        .elseif strstr(rbx, "/*")
            mov byte ptr [rax],0
            mov r12,rax
            inc rax
            .if strstr(rax, "*/")
                add rax,2
                strcpy(r12, rax)
               .continue .if !strtrim(rbx)
            .else
                inc comment_section
            .endif
        .endif
        .if comment_section
            .continue
        .endif
        .if strstr(rbx, "//")
            mov byte ptr [rax],0
            .continue .if !strtrim(rbx)
        .endif
        strtrim(rbx)
        .if ( eax && stoptions )
            arg_option_s(rbx)
            arg_option_w(rbx)
            arg_option_f(rbx)
            arg_option_r(rbx)
            strtrim(rbx)
        .endif
        .return rbx
    .endw
    ret

getline endp


concat proc uses rbx r12 string:string_t

    ldr rbx,string
    lea r12,[rbx+strtrim(rbx)+1]
    mov [r12-1],' '
    getline(r12)
    strcpy(r12, ltokstart(r12))
   .return(rbx)

concat endp


concatf proc uses rbx string:string_t

    ldr rbx,string
    lea rcx,[rbx+strlen(rbx)-1]

    .if ( [rcx] == '\' )

        .while 1

            mov [rcx],0
            lea rcx,[rbx+strlen(concat(rbx))-1]
            .break .if ( [rcx] != '\' )
        .endw
    .endif
    .return(rbx)

concatf endp


tokenize proc uses rbx r12 string:string_t

    ldr r12,string

    .while 1

        mov rbx,ltokstart(r12)
        mov tokpos,rbx

        .if ( [rbx] == 0 )
            mov csize,0
            mov ctoken,T_BLANK
           .return(T_BLANK)
        .endif

        .if ( [rbx] == '#' )

            inc rbx
            mov rdx,ltokstart(rbx)
            .if ( rdx != rbx )
                strcpy(rbx, rdx)
            .endif
            dec rbx

            mov eax,[rbx+1]
            bswap eax
            .switch eax
            .case 'incl'
                mov csize,8
                mov ctoken,T_INCLUDE
                .return(T_INCLUDE)
            .case 'defi'
                mov csize,7
                mov ctoken,T_DEFINE
                .return(T_DEFINE)
            .case 'unde'
                mov csize,6
                mov ctoken,T_UNDEF
                .return(T_UNDEF)
            .case 'prag'
                mov csize,7
                mov ctoken,T_PRAGMA
                .return(T_PRAGMA)
            .case 'erro'
                mov csize,6
                mov ctoken,T_ERROR
                .return(T_ERROR)
            .case 'endi'
                mov csize,6
                mov ctoken,T_ENDIF
                .return(T_ENDIF)
            .case 'elif'
                strcpy(tempbuf, "#elseif")
                strcat(rax, &[rbx+5])
                strcpy(rbx, rax)
                mov csize,7
                mov ctoken,T_IF
                .return(T_IF)
            .case 'else'
                movzx eax,byte ptr [rbx+5]
                .if !islalpha(eax)
                    mov csize,5
                    mov ctoken,T_ELSE
                    .return(T_ELSE)
                .endif
            .default
                .for ( rbx++, ecx = 1 : islalpha([rbx]) : rbx++, ecx++ )
                .endf
                mov csize,ecx
                mov ctoken,T_IF
                .return(T_IF)
            .endsw
        .endif

        .if ( byte ptr [rbx] == '}' )
            mov csize,1
            mov ctoken,T_ENDS
            .return(T_ENDS)
        .endif

        .switch toksize(rbx)
        .case 4
            mov eax,[rbx]
            .if eax == 'mune'
                mov csize,4
                mov ctoken,T_ENUM
               .return(T_ENUM)
            .endif
            .endc
        .case 5
            .if !memcmp(rbx, "union", 5)
                mov csize,5
                mov ctoken,T_UNION
               .return(T_STRUCT)
            .endif
            .endc
        .case 6
            .if !memcmp(rbx, "struct", 6)
                mov csize,6
                mov ctoken,T_STRUCT
               .return(T_STRUCT)
            .endif
            .if !memcmp(rbx, "extern", 6)
                mov csize,6
                mov ctoken,T_EXTERN
               .return(T_EXTERN)
            .endif
            .endc
        .case 7
            .endc .if memcmp(rbx, "typedef", 7)
            mov csize,7
            mov ctoken,T_TYPEDEF
           .return(T_TYPEDEF)
        .case 8
            .if !memcmp(rbx, "EXTERN_C", 8)
                mov csize,8
                mov ctoken,T_EXTERN
                .if !memcmp(&[rbx+9], "const IID IID_", 14)
                    mov ctoken,T_INTERFACE
                    .return(T_INTERFACE)
                .endif
               .return(T_EXTERN)
            .endif
            .if !memcmp(rbx, "__inline", 8)
                mov csize,8
                mov ctoken,T_INLINE
               .return(T_INLINE)
            .endif
            .endc
        .case 9
            .if !memcmp(rbx, "namespace", 9)
                mov csize,9
                mov ctoken,T_NAMESPACE
               .return(T_NAMESPACE)
            .endif
            .endc
        .case 11
            .if !memcmp(rbx, "DEFINE_GUID", 11)
                mov csize,11
                mov ctoken,T_DEFINE_GUID
               .return(T_DEFINE_GUID)
            .endif
            .endc
        .case 14
            .if !memcmp(rbx, "DECLARE_HANDLE", 14)
                mov csize,14
                mov ctoken,T_DEFINE_GUID
               .return(T_DEFINE_GUID)
            .endif
            .if !memcmp(rbx, "MIDL_INTERFACE", 14)
                mov csize,14
                mov ctoken,T_MIDL_INTERFACE
               .return(T_MIDL_INTERFACE)
            .endif
            .endc
        .endsw
        mov csize,eax
        mov ctoken,T_ID
       .return(T_ID)
    .endw
    ret

tokenize endp


parse_blank proc

    .if ( cstart )
        inc cblank
        .if ( cblank == 1 )

            .if ( cflags & FL_STBUF )

                strcat(filebuf, "\n")
            .else
                fprintf(outfile, "\n")
            .endif
        .endif
    .endif
    ret

parse_blank endp


; #[else]if[n]def

parse_if proc uses rbx

    mov rbx,tokpos
    .if !memcmp(rbx, "#ifdef UNICODE", 14)
        oprintf("ifdef _UNICODE\n")
        inc unicode
       .return
    .endif
    convert(concatf(rbx))
    oprintf("%s\n", &[rbx+1])
    ret

parse_if endp


; #else/#endif/#undef

parse_else proc

    .if ( ctoken == T_ENDIF )
        mov unicode,0
    .endif
    mov rdx,tokpos
    oprintf("%s\n", &[rdx+1])
    ret

parse_else endp


; #error

parse_error proc uses rbx

    mov rbx,tokpos
    .if strchr(rbx, '<')

        lea rdx,[rax+1]
        strcpy(rax, rdx)
        .if strchr(rbx, '>')
            lea rdx,[rax+1]
            strcpy(rax, rdx)
        .endif
    .endif
    oprintf(".err <%s>\n", &[rbx+7])
    ret

parse_error endp


; #pragma

parse_pragma proc uses rbx

    mov rbx,tokpos
    convert(concatf(rbx))
    oprintf(";.%s\n", &[rbx+1])
    ret

parse_pragma endp


; #include <name.h>

stripchr proc string:string_t, chr:int_t

    ldr rcx,string
    ldr edx,chr

    .if strchr(rcx, edx)
        lea rdx,[rax+1]
        strcpy(rax, rdx)
    .endif
    ret

stripchr endp


parse_include proc uses rbx

    mov rbx,tokpos
    mov rbx,ltokstart(&[rbx+8])

    .if stripchr(rbx, '<')
        stripchr(rbx, '>')
    .elseif stripchr(rbx, '"')
        stripchr(rbx, '"')
    .endif
    .if strrchr(rbx, '.')
        mov [rax],0
    .endif

    strcat(rbx, ".inc")
    oprintf("include %s\n", rbx)
    ret

parse_include endp


exit_macro proc string:string_t

    ldr rcx,string
    .return oprintf("  exitm<%s>\n  endm\n", convert(rcx))

exit_macro endp


; guess:
; #define n (x) - value
; #define n(x)  - macro

parse_define proc uses rbx r12 r13 r14

    mov r13,tokpos
    mov r12,ltokstart(&[r13+7])
    mov r14,nexttok(rax)
    mov al,[r14-1]

    .if ( cl != '(' || ( cl == '(' && ( al == ' ' || al == 9 ) ) )

        convert(concatf(r13))

        xor ebx,ebx
        mov eax,[r14]
        movzx ecx,al
        .if ( al == '"' || ( al == 'L' && ah == '"' ) )
            inc ebx
        .elseif ( [r15+rcx] & _LABEL )
            toksize(r14)
            .if ( [r14+rax] == 0 && ( option_b || unicode ) )
                inc ebx
            .endif
        .endif
        .if ( ebx )
            strcpy(r14, strcat(strcat(strcpy(tempbuf, "<"), r14), ">"))
        .endif
        oprintf("%s\n", &[r13+1])
       .return
    .endif

    mov [r14],0
    inc r14
    xor ebx,ebx

    .if strchr(r14, ')')
        mov [rax],0
        mov rbx,ltokstart(&[rax+1])
    .endif

    oprintf("%s macro %s\n", r12, r14)

    .if ( !rbx )
        .return error(r14)
    .endif
    strcpy(r13, rbx)

    .while ( [r13] == '\' )
        getline(r13)
        mov r13,ltokstart(r13)
    .endw

    .if ( [r13] == 0 )
        .return exit_macro(r13)
    .endif


    ;
    ; macro(arg1, \
    ;       ..., \
    ;       argn)
    ;
    .while 1

        .break .if !strrchr(r13, ',')

        lea r14,[rax+1]
        .break .ifd ltokstartc(r14) != '\'
        .break .if ( [rcx+1] != 0 )

        mov [r14],0
        concat(r13)
    .endw
    .if ( [r13+strlen(r13)-1] != '\' )

        ; strip <(macro(...))> --> <macro(...)>

        .if ( [r13] == '(' )
            mov rbx,ltokstart(&[r13+1])
            .if isclabel0([rbx])
                .for ( rdx = rbx, ecx = 1 : [rdx] : rdx++ )
                    .if ( [rdx] == '(' )
                        inc ecx
                    .elseif ( [rdx] == ')' )
                        dec ecx
                        .break .ifz
                    .endif
                .endf
                .if ( word ptr [rdx] == ')' )
                    dec rdx
                    .if ( rdx != rbx && [rdx] == ')' )
                        mov [rdx+1],0
                        strcpy(r13, rbx)
                    .endif
                .endif
            .endif
        .endif
        .return exit_macro(r13)
    .endif

    .repeat

        mov [r13+rax-1],0
        strtrim(r13)
        convert(r13)
        oprintf("    %s\n", ltokstart(r13))
    .until ( [r13+strlen(getline(r13))-1] != '\' )

    convert(r13)
    oprintf("    %s\n", ltokstart(r13))
   .return exit_macro("")

parse_define endp


; [typedef] enum [name] {

parse_enum proc uses rbx

    mov rbx,tokpos
    .if ( !strchr(rbx, '{') )
        concat(rbx)
    .endif
    mov rbx,nexttok(rbx)
    nexttok(rbx)

    or cflags,FL_ENUM
    .if ( cl == '{' || [rbx] == '{' ) ; enum { --> } name;
        mov rax,filebuf
        mov [rax],0
        or cflags,FL_STBUF
       .return
    .endif

    .if ( cl == '_' ) ; enum _name { ... } name;
        inc rbx
    .endif
    oprintf(".enum %s\n", rbx)
    ret

parse_enum endp


; }[name][, type];

parse_ends proc uses rbx r12

    mov r12,tokpos

    .if ( cflags & FL_STBUF )

        and cflags,not FL_STBUF
        .if ( cflags & FL_ENUM )

            and cflags,not FL_ENUM
            mov rbx,nexttok(r12)
            .if toksize(rbx)
                mov [rbx+rax],0
            .endif
            mov byte ptr [r12],0
            oprintf(".enum %s {\n%s%s}\n", rbx, filebuf, linebuf)
        .endif
    .elseif ( cflags & FL_ENUM )
        and cflags,not FL_ENUM
        oprintf("}\n")
    .endif
    ret

parse_ends endp


strip_unsigned proc uses rbx r12 r13 string:string_t

    ldr r12,string
    .while strstr(r12, "unsigned")

        mov rbx,rax
        mov r13,ltokstart(&[rax+8])
        mov ecx,toksize(rax)
        mov eax,[r13]
        add r13,rcx
        lea rdx,@CStr("dword")

        .switch ecx
        .case 7
            .if eax == 'ni__'
                lea rdx,@CStr("qword")
               .endc
            .endif
            lea r13,[rbx+8]
            .endc
        .case 4
            .if eax == 'rahc'
                lea rdx,@CStr("byte")
               .endc
            .endif
            mov eax,[r13+1]
            .if eax == 'gnol'
                add r13,5
                lea rdx,@CStr("qword")
               .endc
            .endif
            lea r13,[rbx+8]
            .endc
        .case 3
            .endc .if ax == 'ni'
            lea r13,[rax+8]
            .endc
        .case 5
            .if eax == 'rohs'
                lea rdx,@CStr("word")
               .endc
            .endif
        .default
            lea r13,[rbx+8]
        .endsw
        strcpy(tempbuf, rdx)
        strcat(rax, r13)
        strcpy(rbx, rax)
    .endw

    wordxchg(r12, "long long",   "sqword")
    wordxchg(r12, "__int64",     "sqword")
    wordxchg(r12, "long",        "sdword")
    wordxchg(r12, "int",         "sdword")
    wordxchg(r12, "INT",         "sdword")
    wordxchg(r12, "char",        "sbyte")
    wordxchg(r12, "short",       "sword")
    wordxchg(r12, "SHORT",       "sword")
    wordxchg(r12, "float",       "real4")
    wordxchg(r12, "FLOAT",       "real4")
    wordxchg(r12, "double",      "real8")
    wordxchg(r12, "...",         "vararg")
    ret

strip_unsigned endp


; type [*] name

parse_protoarg proc uses rbx r12 arg:string_t

    ldr rcx,arg
    mov r12,ltokstart(rcx)

    .if ( strchr(r12, '*') )

        mov bl,[rax+1]
        oprintf(" :ptr")
        .if ( bl == '*' )
            oprintf(" ptr")
        .endif
       .return( 1 )
    .endif

    lea rbx,[r12+strtrim(r12)]
    .if !_stricmp(r12, "void")
        .return( 0 )
    .endif

    mov rbx,prevtok(rbx, r12)
    .if ( rbx > r12 )
        dec rbx
        mov rbx,prevtokz(rbx, r12)
    .endif
    oprintf(" :%s", rbx)
   .return( 1 )

parse_protoarg endp


; args );

parse_protoargs proc uses rbx r12 r13 args:string_t, comma:int_t

     ldr r12,args
     ldr ebx,comma
     .if !strrchr(r12, ')')
        .return error(r12)
     .endif
     mov [rax],0

    .while strchr(r12, '(')
        mov r13,rax
        .for ( rcx = &[rax+1], edx = 1 : [rcx] : rcx++ )
            .if ( [rcx] == '(' )
                inc edx
            .elseif ( [rcx] == ')' )
                dec edx
                .break .ifz
            .endif
        .endf
        .if ( [rcx] == ')' )
            inc rcx
        .endif
        strcpy(r13, rcx)
    .endw
    .while strstr(r12, "const ")
        mov r13,rax
        strcpy(r13, &[rax+6])
    .endw

    .while r12
        xor r13d,r13d
        .if strchr(r12, ',')
            mov [rax],0
            lea r13,[rax+1]
        .endif
        .if ( ebx )
            oprintf(",")
        .endif
        parse_protoarg(r12)
        inc ebx
        mov r12,r13
    .endw
    ret

parse_protoargs endp


; name( args );

parse_proto proc uses rbx r12 r13 p:string_t

    ldr r12,p
    .if !strrchr(r12, ')')
        .return error(r12)
    .endif

    .for ( rax--, edx = 1 : rax > r12 : rax-- )
        .if ( [rax] == ')' )
            inc edx
        .elseif ( [rax] == '(' )
            dec edx
            .break .ifz
        .endif
    .endf
    .if ( [rax] != '(' )
        .return error(r12)
    .endif

    mov [rax],0
    mov rbx,rax
    mov r13,ltokstart(&[rax+1])

    oprintf("%s proto", prevtokz(rbx, r12))

    .ifd ( strip_unsigned(r13) && option_v )
        oprintf(" %s", option_v)
    .elseif ( option_c )
        oprintf(" %s", option_c)
    .endif

    parse_protoargs(r13, 0)
    oprintf("\n")
    ret

parse_proto endp


; (name)( args );

parse_callback proc uses rbx r12 p:string_t

    ldr rbx,p
    oprintf("CALLBACK(")

    .if !strrchr(rbx, '(')
        .return error(rbx)
    .endif
    mov [rax],0
    mov r12,ltokstart(&[rax+1])
    strip_unsigned(r12)

    .if !strrchr(rbx, ')')
        .return error(rbx)
    .endif
    oprintf("%s", prevtokz(rax, rbx))
    parse_protoargs(r12, 1)
    oprintf(")\n")
    ret

parse_callback endp


concat_line proc uses rbx buffer:string_t

    ldr rbx,buffer
    .while !strrchr(rbx, ';')
        concat(rbx)
    .endw
    .return(rbx)

concat_line endp


parse_id proc uses rbx r12 r13

    mov r12,tokpos

    .if ( cflags & FL_ENUM )

        convert(r12)
        oprintf("%s\n", linebuf)
       .return
    .endif

    mov r13,strchr(r12, ';')
    mov rbx,strchr(r12, '(')
    .if ( r13 && rbx )
        .return parse_proto(r12)
    .endif

    nexttok(r12)

    .if ( !r13 && !rbx && !cl ) ; macro ?

        fgets(tempbuf, MAXLINE, srcfile)
        .if ( !rax || [rax] == 10 )

            inc curline
            .if ( option_m == 0 )
                oprintf("%s\n\n", linebuf)
            .endif
           .return
        .endif
        tokenize(concat_line(strcpy(linebuf, tempbuf)))
       .return parseline()
    .endif

    .if ( !r13 && rbx )

        .if strrchr(r12, ')')
            .return .if ( [rax+1] == 0 )
        .endif
         ;nexttok(rdi)
        ;.return .if ( cl == '(' )
    .endif
    .if strchr(concat_line(r12), '(')
        .return parse_proto(r12)
    .endif
    .return error(r12)

parse_id endp


parse_define_guide proc uses rbx

    mov rbx,tokpos
    .if strrchr(rbx, ';')
        mov [rax],0
    .else
        .if strrchr(concat_line(rbx), ';')
            mov [rax],0
        .endif
    .endif
    oprintf("%s\n", rbx)
    ret

parse_define_guide endp


; type name[, name2, ...];
; type (*name)(args);

is_struct proc uses rbx r12 r13 string:string_t

    ldr r12,string
    lea r13,knownstructs
    .while 1
        mov rax,[r13]
        add r13,size_t
        .break .if !rax
        .if !strcmp(rax, r12)
            .return(1)
        .endif
    .endw
    lea r13,lstructa
    .for ( ebx = 0 : ebx < lstructs : ebx++ )
        mov rax,[r13]
        add r13,size_t
        .if !strcmp(rax, r12)
            .return(1)
        .endif
    .endf
    .return(0)

is_struct endp


push_struct proc uses rbx name:string_t

    ldr rbx,name

    .return .if ( [rbx] == 0 )
    .if ( lstructs >= MAXLSTRUCTS )
        .return error("buffer overflow: to many local structures")
    .endif
    .return .if is_struct(rbx)
    .return .if !_strdup(rbx)
    lea rdx,lstructa
    mov ecx,lstructs
    mov [rdx+rcx*8],rax
    inc lstructs
    ret

push_struct endp


get_resword proc uses rbx r12 r13 string:string_t

    ldr r12,string
    mov ebx,strlen(r12)
    .if ( eax > 8 || eax < 2 )
        .return(r12)
    .endif
    lea r13,reswords
    .while 1
        mov rax,[r13]
        add r13,size_t
        .break .if !rax
        .if !memcmp(rax, r12, ebx)
            .return(strcat(strcpy(&reswbuf, "_"), r12))
        .endif
    .endw
    .return(r12)

get_resword endp


parse_struct_member proc uses rbx r12 r13 r14

   .new p:string_t
   .new q:string_t = tokpos
   .new n:int_t

    mov r12d,strip_unsigned(q)

    .if strchr(q, '(')

        .if ( [ltokstart(&[rax+1])] == '*' )

            .if strchr(rax, ')')

                lea rbx,[rax+1]
                mov p,prevtokz(rax, q)
                movzx r13d,clevel
                dec r13d
                .if ( cflags & FL_RECORD )

                    dec r13d
                    dec clevel
                    and cflags,not FL_RECORD
                    oprintf("%*s\n", r13d, "ends")
                .endif
                lea ecx,[r13-23]
                oprintf("%*s%*s proc", r13d, "", ecx, p)

                .ifd ( r12d && option_v )
                    oprintf(" %s", option_v)
                .elseif ( option_c )
                    oprintf(" %s", option_c)
                .endif
                mov rbx,ltokstart(rbx)
                .if ( cl == '(' )
                    inc rbx
                .elseif strchr(rbx, '(')
                    lea rbx,[rax+1]
                .endif
                parse_protoargs(ltokstart(rbx), 0)
                oprintf("\n")
               .return
            .endif
        .endif
    .endif

    lea r12,@CStr("ptr ")
    xor ebx,ebx
    xor r13d,r13d
    .if strchr(q, ',')
        mov [rax],0
    .endif
    mov r14,rax

    .if strchr(q, '[')

        mov [rax],0
        mov rbx,ltokstart(&[rax+1])

        .if strchr(rbx, ']')

            mov [rax],0
            .if [rax+1] == '['

                mov word ptr [rax],' *'
                .if strchr(rax, ']')

                    mov [rax],0
                    .if [rax+1] == '['

                        mov word ptr [rax],' *'
                        .if strchr(rax, ']')
                            mov [rax],0
                        .endif
                    .endif
                .endif
            .endif
        .endif
        strtrim(rbx)
        strtrim(q)
        add rax,q
        dec rax
        mov p,rax

    .elseif strrchr(q, ':')

        mov [rax],0
        lea rcx,[rax-1]
        mov p,rcx
        mov r13,ltokstart(&[rax+1])

        .if strchr(r13, ';')
            mov [rax],0
        .endif
    .elseif r14
        mov p,r14
    .else
        mov p,strrchr(q, ';')
    .endif
    mov p,prevtokz(p, q)

    .if ( r13 )

        .if !( cflags & FL_RECORD )

            movzx ecx,clevel
            inc clevel
            or cflags,FL_RECORD
            dec ecx
            oprintf("%*s\n", ecx, "record")
        .endif

    .elseif ( cflags & FL_RECORD )

        dec clevel
        and cflags,not FL_RECORD
        movzx ecx,clevel
        dec ecx
        oprintf("%*s\n", ecx, "ends")
    .endif


    mov rdx,get_resword(p)
    movzx eax,clevel
    dec eax
    lea ecx,[rax-23]
    oprintf("%*s%*s ", eax, "", ecx, rdx)
    mov rax,p
    mov [rax],0

    ; reduce type to 2: [unsigned] type [*]
    strtrim(q)
    add rax,q
    mov p,prevtok(rax, q)
    .if ( rax > q )
        dec rax
        .if prevtok(rax, q) > q
            mov q,rax
        .endif
    .endif

    .if strchr(p, '*')

        mov [rax],0
        .if strtrim(p) == 4

            mov rcx,p
            mov eax,[rcx]
            or  eax,0x20202020
            .if eax == 'diov'
                mov [rcx],0
                lea r12,@CStr("ptr")
            .endif
        .endif
    .else
        add r12,4
    .endif

    .if ( p > q )
        mov q,p
    .endif

    .new isstruct:int_t = 0
    .if ( [r12] == 0 )
        mov isstruct,is_struct(q)
    .endif

    .if ( !r13 && isstruct )
        .if rbx
            oprintf("%s %s dup(<>)\n", q, rbx)
        .else
            oprintf("%s <>\n", q)
        .endif
    .else
        .if rbx
            oprintf("%s%s %s dup(?)\n", r12, q, rbx)
        .elseif r13
            oprintf("%s%s : %2s ?\n", r12, q, r13)
        .else
            oprintf("%s%s ?\n", r12, q)
        .endif
    .endif

    .while r14

        mov p,ltokstart(&[r14+1])
        mov r14,strchr(p, ',')
        .if rax
            mov [rax],0
        .elseif strrchr(p, ';')
            mov [rax],0
        .endif

        xor ebx,ebx
        .if strrchr(p, '[')
            mov [rax],0
            lea rbx,[rax+1]
            .if strchr(rbx, ']')
                mov [rax],0
            .endif
        .endif
        strtrim(p)
        movzx eax,clevel
        dec eax
        lea ecx,[rax-23]
        mov n,eax
        oprintf("%*s%*s ", n, "", ecx, p)
        .if ( isstruct )
            .if rbx
                oprintf("%s %s dup(<>)\n", q, rbx)
            .else
                oprintf("%s <>\n", q)
            .endif
        .else
            .if rbx
                oprintf("%s%s %s dup(?)\n", r12, q, rbx)
            .else
                oprintf("%s%s ?\n", r12, q)
            .endif
        .endif
    .endw

    xor  eax,eax
    test r13,r13
    setnz al
    ret

parse_struct_member endp


; [typedef] <struct|union> [name] {

parse_struct proc uses rbx r12 r13 r14

    .new name[256]:char_t
    .new type:string_t = "struct"
    .new oldfilebuf:string_t = filebuf
    .new oldflags:dword = cflags

    .if ( ctoken == T_UNION )
        mov type,&@CStr("union")
    .endif

    mov r13,tokpos
    mov rbx,nexttok(r13)
    .if ( cl == 0 )
        concat(r13)
        mov rbx,ltokstart(rbx)
    .endif
    .if !strchr(r13, '{')
        .if !strchr(r13, ';')
            concat(r13)
        .endif
    .endif
    .if strchr(r13, '{')
        mov byte ptr[rax], 0
    .endif

    xor r14d,r14d
    .if strchr(rbx, ';')
        mov r14,prevtokz(rax, rbx)
        oprintf("%-23s typedef ", r14)
        mov byte ptr [r14],0
        .if strchr(rbx, '*')
            mov byte ptr [rax],0
            oprintf("ptr ")
        .endif
    .endif
    .if strtrim(rbx)
        mov rbx,prevtokz(&[rbx+rax-1], rbx)
    .endif
    .if ( r14 )
        oprintf("%s\n", rbx)
       .return
    .endif

    strcpy(&name, rbx)

    inc clevel
    or  cflags,FL_STRUCT or FL_STBUF
    mov filebuf,malloc(MAXBUF)
    xor ecx,ecx
    mov [rax],rcx
    mov r13,linebuf

    .while 1

        .switch tokenize(getline(r13))
        .case T_BLANK
            .endc
        .case T_ID
            concat_line(r13)
            parse_struct_member()
           .endc
        .case T_STRUCT
            .if ( cflags & FL_RECORD )

                dec clevel
                and cflags,not FL_RECORD
                movzx ecx,clevel
                dec ecx
                oprintf("%*s\n", ecx, "ends")
            .endif
            parse_struct()
           .endc
        .case T_ENDS
            .new enddir:byte = 0
            .if ( cflags & FL_RECORD )

                dec clevel
                and cflags,not FL_RECORD
                movzx ecx,clevel
                dec ecx
                oprintf("%*s\n", ecx, "ends")
            .endif
            xor ebx,ebx
            .if !strrchr(r13, ';')
                concat(r13)
            .endif
            .if strchr(r13, ',')
                mov byte ptr [rax],0
                lea rbx,[rax+1]
            .elseif strrchr(r13, ';')
                inc enddir
                mov byte ptr [rax],0
                lea rbx,[rax+1]
            .endif
            mov r13,nexttok(tokpos)

            dec clevel
            .if ( clevel )
                movzx ebx,clevel
                sub ebx,1
                oprintf("%*s\n", ebx, "ends")
                strcpy(&name, r13)
               .break
            .endif

            strtrim(r13)
            lea r14,name
            .if ( name )
                oprintf("%-23s ends\n", r14)
                .if ( byte ptr [r13] )
                    .if strcmp(r14, r13)
                        oprintf("%-23s typedef %s\n", r13, r14)
                    .endif
                .endif
            .else
                oprintf("%-23s ends\n", r13)
                strcpy(&name, r13)
            .endif

            .break .if !rbx
            mov rbx,ltokstart(rbx)
            .if !byte ptr [rbx]
                .break .if enddir
            .endif
            concat_line(rbx)

            .while strchr(rbx, ',')

                mov byte ptr [rax],0
                mov r13,rbx
                lea rbx,[rax+1]
                mov r13,ltokstart(r13)
                .if ( [r13] == '#' )
                    prevtok(rbx, r13)
                    dec rax
                    .if ( [rax-1] == ' ' || [rax-1] == '*' )
                        mov [rax-1],0
                    .else
                        mov [rax],0
                        inc rax
                    .endif
                    mov r12,tempbuf
                    add r12,MAXBUF/2
                    strcpy(r12, rax)
                    tokenize(strcpy(linebuf, r13))
                    parseline()
                    mov r13,ltokstart(strcpy(r13, r12))
                .endif
                .if strrchr(r13, '*')
                    mov r13,rax
                .endif
                .if ( byte ptr [r13] == '*' )
                    oprintf("%-23s typedef ptr %s\n", ltokstart(&[r13+1]), r14)
                .else
                    push_struct(r13)
                    oprintf("%-23s typedef %s\n", r13, r14)
                .endif
            .endw
            .break .if !strchr(rbx, ';')

            mov byte ptr [rax],0
            mov r13,rbx
            lea rbx,[rax+1]
            mov r13,ltokstart(r13)
            .if strrchr(r13, '*')
                mov r13,rax
            .endif
            .if byte ptr [r13] == '*'
                oprintf("%-23s typedef ptr %s\n", ltokstart(&[r13+1]), r14)
            .else
                push_struct(r13)
                oprintf("%-23s typedef %s\n", r13, r14)
            .endif
            .break
        .default
            parseline()
        .endsw
    .endw
    mov r14,filebuf
    mov filebuf,oldfilebuf
    .if ( !( oldflags & FL_STBUF) )
        and cflags,not FL_STBUF
    .endif
    lea r13,name
    .if ( clevel == 0 )
        oprintf("%-23s %s\n%s", r13, type, r14)
        push_struct(r13)
    .else
        .if !memcmp(r13, "DUMMY", 5)
            mov name,0
        .endif
        oprintf("%*s%s %s\n%s", ebx, "", type, r13, r14)
    .endif
    free(r14)
    ret

parse_struct endp


; typedef type name;
; typedef type (name)(args);

parse_typedef proc uses rbx r12 r13

   .new name[256]:char_t

    mov r12,tokpos
    mov rbx,nexttok(r12)
    .if ( cl == 0 )
        concat(r12)
        mov rbx,ltokstart(rbx)
    .endif

    .ifd ( toksize(rbx) == 4 )
        .if !memcmp(rbx, "enum", 4)
            mov tokpos,rbx
            .return parse_enum()
        .endif
    .elseif ( eax == 5 || eax == 6 )
        xor r13d,r13d
        .if !memcmp(rbx, "struct", 6)
            mov r13d,T_STRUCT
            mov eax,6
        .elseif !memcmp(rbx, "union", 5)
            mov r13d,T_UNION
            mov eax,5
        .endif
        .if r13d
            mov tokpos,rbx
            mov ctoken,r13b
            mov csize,eax
            .return parse_struct()
        .endif
    .endif

    strip_unsigned(concat_line(r12))
    strrchr(r12, ';')
    .if ( [rax-1] == ')' )
        .return parse_callback(r12)
    .endif

    mov r13,prevtokz(rax, r12)
    strcpy(&name, r13)
    mov [r13],0
    xor ebx,ebx

    .if strchr(r12, '*')
        mov [rax],0
        inc ebx
    .endif
    .if strtrim(r12)
        mov r12,prevtokz(&[r12+rax-1], r12)
    .endif

    lea r13,name
    .if strcmp(r13, r12)
        oprintf("%-23s typedef ", r13)
        .if ebx
            oprintf("ptr ")
        .endif
        oprintf("%s\n", r12)
    .endif
    ret

parse_typedef endp


parse_midl_interface proc uses rbx r12 r13

    .new iid[64]:char_t

    ; MIDL_INTERFACE("...");

    mov r12,tokpos
    .if strrchr(r12, ';')
        mov [rax],0
    .endif
    .return .if !strchr(r12, '"')
    strcpy(&iid, rax)

    .if !strchr(strcpy(tempbuf, ltokstart(getline(r12))), ':')
        .return error(r12)
    .endif
    mov [rax-1],0
    oprintf("DEFINE_IIDX(%s, %s\n\n", tempbuf, &iid)
    oprintf(".comdef %s\n", ltokstart(r12))

    getline(r12) ; {
    getline(r12) ; public:

    .while 1

        mov rbx,ltokstart(getline(r12))
        .break .if ( cl ==  '}' )
        .continue .if ( cl ==  0 )

        .break .if !strchr(concat_line(r12), '(')

        lea rbx,[rax+1]
        mov r13,prevtokz(rax, r12)
        oprintf("    %-19s proc", r13)
        parse_protoargs(ltokstart(rbx), 0)
        oprintf("\n")
    .endw
    oprintf("   .ends\n")
    .while memcmp(r12, "#endif", 6)
        getline(r12)
    .endw
    oprintf("endif\n")
    ret

parse_midl_interface endp


parse_interface proc uses rbx r12 r13

    mov r12,tokpos
    .return .if !strrchr(r12, ';')

    mov [rax],0
    strcpy(tempbuf, &[prevtokz(rax, r12)+4])
    getline(r12)

    .if !memcmp(r12, "#endif", 6)
        ;
        ; Windows 10:
        ;
        ; EXTERN_C const IID IID...
        ; #endif /* !defined(...
        ;
        oprintf("endif\n")
       .return(0)
    .endif
    ;
    ; Windows 8:
    ;
    ; EXTERN_C const IID IID...
    ;
    ; #if defined(__cplusplus) && !defined(CINTERFACE)
    ;
    ;     MIDL_INTERFACE(...
    ;
    getline(r12)
    .if memcmp(r12, "#if defined(__cplusplus) && !defined(CINTERFACE)", 49)
        .return error(r12)
    .endif
    getline(r12)
    getline(r12)

    .if !strrchr(r12, '(')
        .return error(r12)
    .endif

    inc rax
    oprintf("DEFINE_IIDX(%s, %s\n\n", tempbuf, rax)
    getline(r12)
    oprintf(".comdef %s\n", ltokstart(r12))
    getline(r12) ; {
    getline(r12) ; public:

    .while 1

        mov rbx,ltokstart(getline(r12))
        .break .if ( cl ==  '}' )
        .continue .if ( cl ==  0 )

        .break .if !strchr(concat_line(r12), '(')

        lea rbx,[rax+1]
        mov r13,prevtokz(rax, r12)
        oprintf("    %-19s proc", r13)
        parse_protoargs(ltokstart(rbx), 0)
        oprintf("\n")
    .endw
    oprintf("   .ends\n")
    .while memcmp(r12, "#endif", 6)
        getline(r12)
    .endw
    getline(r12)
    getline(r12)
    getline(r12)
    ret

parse_interface endp


parse_extern proc uses rbx r12 r13

    mov r12,tokpos
    .if !memcmp(r12, "extern const __declspec(selectany) _Null_terminated_ WCHAR", 58)

        mov rbx,ltokstart(&[r12+58])
        .if !strchr(rbx, '[')
            .return error(r12)
        .endif
        mov [rax],0
        lea r13,[rax+1]
        .if !strchr(r13, '"')
            .return error(rbx)
        .endif
        mov r13,rax
        .if strchr(r13, ';')
            mov [rax],0
        .endif
        oprintf("define %s <%s>\n", rbx, r13)
       .return
    .endif

    mov eax,csize

    mov rbx,ltokstart(&[r12+rax])

    .if ( ecx == 0 )
        concat(r12)
        mov rbx,ltokstart(rbx)
    .endif
    .if ( ecx == '"' )
        .return
    .endif
    .if !memcmp(rbx, "RPC_IF_HANDLE", 13)
        .return
    .endif

    concat_line(r12)
    .if strchr(r12, ')')
        lea rbx,[rax+1]
        ltokstart(rbx)
        .if ( cl == '_' )
            mov word ptr [rbx],';'
        .endif
        add tokpos,7
        .return parse_id()
    .endif

    strip_unsigned(r12)
    mov r13,prevtokz(strrchr(r12, ';'), r12)
    oprintf("externdef %s:", r13)

    mov [r13],0
    .if strchr(r12, '*')
        mov [rax],0
        oprintf("ptr ")
    .endif
    .if strtrim(r12)
        mov r12,prevtokz(&[r12+rax-1], r12)
    .endif
    oprintf("%s\n", r12)
    ret

parse_extern endp


parse_inline proc uses rbx

    mov rbx,tokpos
    oprintf(";%s\n", rbx)

    .while 1

        .switch tokenize(getline(rbx))
        .case T_ENDS
            oprintf(";%s\n", rbx)
            .break
        .case T_IF
            parse_if()
            .endc
        .case T_ELSE
        .case T_UNDEF
        .case T_ENDIF
            parse_else()
            .endc
        .default
            oprintf(";%s\n", rbx)
            .endc
        .endsw
    .endw
    ret

parse_inline endp


parse_namespace proc uses rbx

    mov rbx,tokpos
    .if !strchr(rbx, '{')
        .return error(rbx)
    .endif
    mov [rax],0
    oprintf(".%s\n", ltokstart(rbx))
    ret

parse_namespace endp


parseline proc

    .switch ctoken
    .case T_BLANK
       .return parse_blank()
    .case T_STRUCT
    .case T_UNION
        mov clevel,0
       .return parse_struct()
    .case T_ENUM
       .return parse_enum()
    .case T_ENDS
        .return parse_ends()
    .case T_TYPEDEF
        .return parse_typedef()
    .case T_ID
        .return parse_id()
    .case T_IF
        .return parse_if()
    .case T_ELSE
    .case T_UNDEF
    .case T_ENDIF
        .return parse_else()
    .case T_ERROR
        .return parse_error()
    .case T_PRAGMA
        .return parse_pragma()
    .case T_INCLUDE
        .return parse_include()
    .case T_DEFINE
        .return parse_define()
    .case T_INTERFACE
        .return parse_interface()
    .case T_MIDL_INTERFACE
        .return parse_midl_interface()
    .case T_EXTERN
        .return parse_extern()
    .case T_DEFINE_GUID
        .return parse_define_guide()
    .case T_INLINE
        .return parse_inline()
    .case T_NAMESPACE
        .return parse_namespace()
    .endsw
    ret

parseline endp


; Command line options

setarg_option proc uses rbx r12 r13 p:ptr string_t, arg:string_t, arg2:string_t

    ldr rbx,p
    ldr r13,arg
    ldr r12,arg2
    inc stoptions

    .for ( eax = 0, ecx = 0 : rax != [rbx] && ecx < MAXARGS : ecx++, rbx+=8 )
        .if r12
            add rbx,8
        .endif
    .endf
    .if ( ecx == MAXARGS )
        .return errexit(r13)
    .endif
    mov [rbx],_strdup(r13)
    .if r12
        mov [rbx+8],_strdup(r12)
    .endif
    ret

setarg_option endp


getnextcmdstring proc uses rsi rdi cmdline:array_t

    ldr rcx,cmdline
    .for ( rdi = rcx,
           rsi = &[rdi+string_t] : string_t ptr [rsi] : )
        movsq
    .endf
    movsq
   .return([rcx])

getnextcmdstring endp


get_nametoken proc uses rsi rdi rbx dst:string_t, string:string_t, size:int_t, file:int_t

    ldr rdi,dst
    ldr rsi,string
    ldr r9d,file
    ldr ecx,size
    mov al,[rsi]
    .if al == '"'

        inc rsi
        .for ( : ecx && [rsi] : ecx-- )

            mov eax,[rsi]
            .if al == '"'

                inc rsi
                .break
            .endif

            ; handle the \"" case

            .if al == '\' && ah == '"'

                inc rsi
            .endif
            movsb
        .endf

    .else

        .for ( : ecx : ecx -- )

            mov al,[rsi]
            .switch al
            .case ' '
            .case '-'
                .endc .if r9d
            .case 0
            .case 13
            .case 10
            .case 9
                .break
ifndef __UNIX__
            .case '/'
                .break .if !r9d
endif
            .endsw
            movsb
        .endf
    .endif
    mov [rdi],0
   .return(rsi)

get_nametoken endp


parse_param proc uses rbx r12 r13 cmdline:ptr string_t, buffer:string_t

    ldr r13,cmdline
    ldr r12,buffer
    mov rbx,[r13]
    mov eax,[rbx]

    .switch pascal al
ifdef __UNIX__
    .case '-'   ; --help
    .case 'h'
else
    .case '?'
endif
        exit_options()
    .case 'q'
        mov option_q,1
        mov banner,1
        inc rbx
        mov [r13],rbx
    .case 'n'
        mov banner,1
        inc rbx
        mov [r13],rbx
    .case 'b'
        mov option_b,1
        inc rbx
        mov [r13],rbx
    .case 'm'
        mov option_m,1
        inc rbx
        mov [r13],rbx
    .case 'c'
        inc rbx
        mov [r13],get_nametoken(r12, rbx, 256, 0)
        mov option_c,_strdup(r12)
    .case 'v'
        inc rbx
        mov [r13],get_nametoken(r12, rbx, 256, 0)
        mov option_v,_strdup(r12)
    .case 'f'
        inc rbx
        mov [r13],get_nametoken(r12, rbx, 256, 0)
        setarg_option(&option_f, r12, NULL)
    .case 'F'
        add rbx,2
        .if ( byte ptr [rbx] == 0 )
            mov rbx,getnextcmdstring(r13)
        .endif
        mov [r13],get_nametoken(r12, rbx, 256, 1)
        setarg_option(&option_Fo, r12, NULL)
    .case 'w'
        inc rbx
        mov [r13],get_nametoken(r12, rbx, 256, 0)
        setarg_option(&option_w, r12, NULL)
    .case 's'
        inc rbx
        mov [r13],get_nametoken(r12, rbx, 256, 0)
        setarg_option(&option_s, r12, NULL)
    .case 'r'
       .new param2[256]:char_t
        inc rbx
        mov [r13],get_nametoken(r12, rbx, 256, 0)
        mov rbx,ltokstart(rax)
        .if ( cl == 0 )
            mov rbx,getnextcmdstring(r13)
        .endif
        mov [r13],get_nametoken(&param2, rbx, 256-1, 0)
        setarg_option(&option_r, r12, &param2)
    .case 'o'
       .new param2[256]:char_t
        inc rbx
        mov [r13],get_nametoken(r12, rbx, 256, 0)
        mov rbx,ltokstart(rax)
        .if ( cl == 0 )
            mov rbx,getnextcmdstring(r13)
        .endif
        mov [r13],get_nametoken(&param2, rbx, 256-1, 0)
        setarg_option(&option_o, r12, &param2)
    .endsw
    ret

parse_param endp


get_filename proc path:string_t

    ldr rcx,path
    .for ( rax = rcx : [rcx] : rcx++ )
ifdef __UNIX__
        .if ( [rcx] == '/' )
else
        .if ( [rcx] == '\' || [rcx] == '/' )
endif
            lea rax,[rcx+1]
        .endif
    .endf
    ret

get_filename endp


read_paramfile proc uses rbx name:string_t

    ldr rbx,name
    .new fp:ptr FILE = fopen(rbx, "rb")

ifndef __UNIX__
    .if ( rax == NULL )

       .new path[_MAX_PATH]:char_t
        lea rbx,path
        GetModuleFileNameA(0, rbx, _MAX_PATH)
        .if ( get_filename(rbx) > rbx )
            mov [rax],0
        .else
            strcpy(rbx, ".\\")
        .endif
        mov fp,fopen(strcat(rbx, name), "rb")
    .endif
endif
    .if ( rax == NULL )
        errexit(rbx)
    .endif
    .new retval:ptr = NULL
    .if ( fseek( fp, 0, SEEK_END ) == 0 )

        .if ( ftell( fp ) )

            mov ebx,eax
            mov retval,malloc( &[rax+1] )
            mov byte ptr [rax+rbx],0
            rewind( fp )
            fread( retval, 1, ebx, fp )
        .endif
    .endif

    fclose(fp)
   .return( retval )

read_paramfile endp


parse_params proc uses rbx r12 r13 cmdline:ptr string_t, numargs:ptr int_t

   .new paramfile[_MAX_PATH]:char_t

    ldr r13,cmdline
    ldr r12,numargs

    .for ( rbx = [r13] : rbx : )

        mov eax,[rbx]
        .switch al
        .case 13
        .case 10
        .case 9
        .case ' '
            inc rbx
           .endc
        .case 0
            mov rbx,getnextcmdstring(r13)
           .endc
        .case '-'
ifndef __UNIX__
        .case '/'
endif
            inc rbx
            mov [r13],rbx
            parse_param(r13, &paramfile)
            inc dword ptr [r12]
            mov rbx,[r13]
           .endc
        .case '@'
            inc rbx
            mov [r13],get_nametoken(&paramfile, rbx, sizeof(paramfile)-1, 1)
            xor ebx,ebx
            .if paramfile[0]
                mov rbx,getenv(&paramfile)
            .endif
            .if !rbx
                mov rbx,read_paramfile(&paramfile)
            .endif
            .endc
        .default ; collect file name
            mov rbx,get_nametoken(&paramfile, rbx, sizeof(paramfile) - 1, 1)
            mov curfile,_strdup(&paramfile)
            inc dword ptr [r12]
            mov [r13],rbx
           .return
        .endsw
    .endf
    mov [r13],rbx
   .return(NULL)

parse_params endp


translate_module proc uses rbx source:string_t

    ldr rbx,source
    mov curfile,rbx

    .if ( !fopen(rbx, "r") )

        perror(rbx)
       .return( 1 )
    .endif
    mov srcfile,rax

    mov linebuf,malloc(MAXBUF)
    mov filebuf,malloc(MAXBUF)
    mov tempbuf,malloc(MAXBUF)

    .if ( option_Fo )
        mov rbx,option_Fo
    .else
        xchg rbx,rax
        .if ( strrchr(strcpy(rbx, rax), '\') )
            inc rax
            strcpy(rbx, rax)
        .endif
        .if strrchr(rbx, '.')
            strcpy(rax, ".inc")
        .else
            strcat(rbx, ".inc")
        .endif
    .endif
    .if !fopen(rbx, "wt")

        fclose(srcfile)
        perror(rbx)
       .return( 1 )
    .endif
    mov outfile,rax

    mov curline,1
    mov cflags,0
    mov clevel,0
    mov cstart,0
    mov cblank,0
    mov ercount,0
    ;mov lstructs,0 keep structs...

    .if ( !option_q )
        printf( " Translating: %s\n", source)
    .endif

    .if !_setjmp(&jmpenv)

        .while 1
            tokenize(getline(linebuf))
            parseline()
        .endw
    .endif

    fclose(srcfile)
    fclose(outfile)
    free(linebuf)
    free(filebuf)
    free(tempbuf)
   .return(ercount)

translate_module endp


strfcat proc buffer:string_t, path:string_t, file:string_t

    ldr rcx,buffer
    ldr r8,file
    ldr rdx,path

    mov rax,rcx
    .if rdx
        .for ( : byte ptr [rdx] : r9b=[rdx], [rcx]=r9b, rdx++, rcx++ )
        .endf
    .else
        .for ( : byte ptr [rcx] : rcx++ )
        .endf
    .endif
    lea rdx,[rcx-1]
    .if rdx > rax

        mov dl,[rdx]
        .if !( dl == '\' || dl == '/' )

            mov dl,'\'
            mov [rcx],dl
            inc rcx
        .endif
    .endif
    .for ( dl=[r8] : dl : [rcx]=dl, r8++, rcx++, dl=[r8] )
    .endf
    mov [rcx],dl
    ret

strfcat endp


ifdef __UNIX__

GeneralFailure proc private signo:int_t

    .if ( signo != SIGTERM )

        assume rbx:ptr mcontext_t

        lea rdi,@CStr(
            "\n"
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "\tRAX: %p R8:  %p\n"
            "\tRBX: %p R9:  %p\n"
            "\tRCX: %p R10: %p\n"
            "\tRDX: %p R11: %p\n"
            "\tRSI: %p R12: %p\n"
            "\tRDI: %p R13: %p\n"
            "\tRBP: %p R14: %p\n"
            "\tRSP: %p R15: %p\n"
            "\tRIP: %p %p\n"
            "\t     %p %p\n\n"
            "\tEFL: 0000000000000000\n"
            "\t     r n oditsz a p c\n\n" )


        mov rbx,rdx
        add rbx,ucontext_t.uc_mcontext
        mov rax,[rbx].gregs[REG_EFL*8]
        mov ecx,16
        .repeat
            shr eax,1
            adc byte ptr [rdi+rcx+sizeof(@CStr(0))-43],0
        .untilcxz

        mov rcx,[rbx].gregs[REG_RIP*8]
        mov rdx,[rcx]
        mov r10,[rcx-8]
        mov r11,[rcx+8]
        printf( rdi,
                [rbx].gregs[REG_RAX*8], [rbx].gregs[REG_R8*8],
                [rbx].gregs[REG_RBX*8], [rbx].gregs[REG_R9*8],
                [rbx].gregs[REG_RCX*8], [rbx].gregs[REG_R10*8],
                [rbx].gregs[REG_RDX*8], [rbx].gregs[REG_R11*8],
                [rbx].gregs[REG_RSI*8], [rbx].gregs[REG_R12*8],
                [rbx].gregs[REG_RDI*8], [rbx].gregs[REG_R13*8],
                [rbx].gregs[REG_RBP*8], [rbx].gregs[REG_R14*8],
                [rbx].gregs[REG_RSP*8], [rbx].gregs[REG_R15*8],
                rcx, rdx, r10, r11 )
        assume rbx:nothing
        exit(1)
    .endif
    errexit("Software termination signal")

GeneralFailure endp

main proc argc:int_t, argv:array_t

else

translate_subdir proc uses rbx r12 r13 r14 directory:string_t, wild:string_t

  local rc, path[_MAX_PATH]:byte, ff:_finddatai64_t

    lea r13,path
    lea r12,ff
    lea rbx,ff.name
    mov rc,0

    .ifd ( _findfirsti64(strfcat(r13, directory, wild), r12) != -1 )
        mov r14,rax
        .repeat
            .if !( ff.attrib & _F_SUBDIR )
                mov rc,translate_module(strfcat(r13, directory, rbx))
            .endif
        .until _findnexti64(r14, r12)
        _findclose(r14)
    .endif
    .return( rc )

translate_subdir endp


_exception_handler proc \
    ExceptionRecord   : PEXCEPTION_RECORD,
    EstablisherFrame  : PEXCEPTION_REGISTRATION_RECORD,
    ContextRecord     : PCONTEXT,
    DispatcherContext : LPDWORD

    .new signo:int_t = SIGTERM
    .new string:string_t = "Software termination signal from kill"

     mov eax,[rcx].EXCEPTION_RECORD.ExceptionFlags
    .switch
    .case eax & EXCEPTION_UNWINDING
    .case eax & EXCEPTION_EXIT_UNWIND
       .endc
    .case eax & EXCEPTION_STACK_INVALID
    .case eax & EXCEPTION_NONCONTINUABLE
        mov signo,SIGSEGV
        mov string,&@CStr("Segment violation")
       .endc
    .case eax & EXCEPTION_NESTED_CALL
        exit(1)

    .default
        mov eax,[rcx].EXCEPTION_RECORD.ExceptionCode
        .switch eax
        .case EXCEPTION_ACCESS_VIOLATION
        .case EXCEPTION_ARRAY_BOUNDS_EXCEEDED
        .case EXCEPTION_DATATYPE_MISALIGNMENT
        .case EXCEPTION_STACK_OVERFLOW
        .case EXCEPTION_IN_PAGE_ERROR
        .case EXCEPTION_INVALID_DISPOSITION
        .case EXCEPTION_NONCONTINUABLE_EXCEPTION
            mov signo,SIGSEGV
            mov string,&@CStr("Segment violation")
           .endc
        .case EXCEPTION_SINGLE_STEP
        .case EXCEPTION_BREAKPOINT
            mov signo,SIGINT
            mov string,&@CStr("Interrupt")
           .endc
        .case EXCEPTION_FLT_DENORMAL_OPERAND
        .case EXCEPTION_FLT_DIVIDE_BY_ZERO
        .case EXCEPTION_FLT_INEXACT_RESULT
        .case EXCEPTION_FLT_INVALID_OPERATION
        .case EXCEPTION_FLT_OVERFLOW
        .case EXCEPTION_FLT_STACK_CHECK
        .case EXCEPTION_FLT_UNDERFLOW
            mov signo,SIGFPE
            mov string,&@CStr("Floating point exception")
           .endc
        .case EXCEPTION_ILLEGAL_INSTRUCTION
        .case EXCEPTION_INT_DIVIDE_BY_ZERO
        .case EXCEPTION_INT_OVERFLOW
        .case EXCEPTION_PRIV_INSTRUCTION
            mov signo,SIGILL
            mov string,&@CStr("Illegal instruction")
           .endc
        .endsw
    .endsw

    .if ( signo != SIGTERM )

        .new flags[17]:sbyte

        .for ( r11      = r8,
               r10      = rcx,
               r8d      = 0,
               rdx      = &flags,
               rax      = '00000000',
               [rdx]    = rax,
               [rdx+8]  = rax,
               [rdx+16] = r8b,
               eax      = [r11].CONTEXT.EFlags,
               ecx      = 16 : ecx : ecx-- )

            shr eax,1
            adc [rdx+rcx-1],r8b
        .endf

        mov rdx,[r11].CONTEXT._Rip
        mov rcx,[rdx]
        bswap rcx
        xor r8,r8
        .if ( r9 )
            mov r8,[r9]
            mov r9,[r8]
            bswap r9
        .endif

        printf(
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "\tException:   %s\n"
            "\tCode: \t     %08X\n"
            "\tFlags:\t     %08X\n"
            "\tProcessor:\n"
            "\t\tRAX: %p R8:  %p\n"
            "\t\tRBX: %p R9:  %p\n"
            "\t\tRCX: %p R10: %p\n"
            "\t\tRDX: %p R11: %p\n"
            "\t\tRSI: %p R12: %p\n"
            "\t\tRDI: %p R13: %p\n"
            "\t\tRBP: %p R14: %p\n"
            "\t\tRSP: %p R15: %p\n"
            "\t\tRIP: %p *--: %p\n"
            "\t   Dispatch: %p *--: %p\n"
            "\t     EFlags: %s\n"
            "\t\t     r n oditsz a p c\n",
            string,
            [r10].EXCEPTION_RECORD.ExceptionCode,
            [r10].EXCEPTION_RECORD.ExceptionFlags,
            [r11].CONTEXT._Rax, [r11].CONTEXT._R8,
            [r11].CONTEXT._Rbx, [r11].CONTEXT._R9,
            [r11].CONTEXT._Rcx, [r11].CONTEXT._R10,
            [r11].CONTEXT._Rdx, [r11].CONTEXT._R11,
            [r11].CONTEXT._Rsi, [r11].CONTEXT._R12,
            [r11].CONTEXT._Rdi, [r11].CONTEXT._R13,
            [r11].CONTEXT._Rbp, [r11].CONTEXT._R14,
            [r11].CONTEXT._Rsp, [r11].CONTEXT._R15,
            rdx, rcx, r8, r9, &flags)

        exit(1)
    .endif
    errexit(string)

_exception_handler endp


main proc frame:_exception_handler argc:int_t, argv:array_t

endif

   .new num_args:int_t = 0
   .new num_files:int_t = 0
ifdef __UNIX__
   .new action:sigaction_t

    mov action.sa_sigaction,&GeneralFailure
    mov action.sa_flags,SA_SIGINFO
    sigaction(SIGSEGV, &action, NULL)
else
   .new ff:_finddatai64_t
endif

    lea r15,_ltype
    add argv,8

    .while parse_params(argv, &num_args)

        write_logo()

        inc num_files
ifdef __UNIX__
        translate_module(curfile)
else
        mov r13,curfile
        lea r12,ff.name
        .ifd _findfirsti64(r13, &ff) == -1
            errexit(r13)
        .endif
        _findclose(rax)

        .if !strchr(strcpy(r12, r13), '*')
            strchr(r12, '?')
        .endif
        .if rax
            .if ( get_filename(r12) > r12 )
                dec rax
            .endif
            mov [rax],0
            translate_subdir(r12, get_filename(r13))
        .else
            translate_module(r12)
        .endif
endif
    .endw

    .if !num_args
        write_usage()
    .elseif !num_files
        printf("error: missing source filename\n")
    .endif
    .return(0)

main endp

    end _tstart
