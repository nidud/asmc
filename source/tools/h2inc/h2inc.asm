; H2INC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc
include signal.inc
include ctype.inc
include tchar.inc

    option dllimport:none

define __H2INC__    100

define MAXLINE      512
define MAXBUF       0x100000
define FL_STBUF     0x01
define FL_STRUCT    0x02
define FL_ENUM      0x04
define FL_TYPEDEF   0x08
define _LABEL       0x40 ; _UPPER + _LOWER + '_'

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
    T_INTERFACE,
    T_EXTERN
    }

parseline proto

.data

 banner     db 0
 option_q   db 0            ; -q
 option_n   db 0            ; -nologo

 align 8
 option_c   string_t NULL   ; -c<calling_convention>
 option_v   string_t NULL   ; -v<calling_convention>

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
_ltype      db \
  0,
  9 dup(_CONTROL),
  5 dup(_SPACE+_CONTROL),
 18 dup(_CONTROL),
  _SPACE,
 15 dup(_PUNCT),
 10 dup(_DIGIT+_HEX),
  7 dup(_PUNCT),
  6 dup(_UPPER+_LABEL+_HEX),
 20 dup(_UPPER+_LABEL),
  4 dup(_PUNCT),
  _PUNCT+_LABEL,
  _PUNCT,
  6 dup(_LOWER+_LABEL+_HEX),
 20 dup(_LOWER+_LABEL),
  4 dup(_PUNCT),
  _CONTROL,
128 dup(0) ; and the rest are 0...

    .code

write_logo proc

    .if ( !banner )

        mov banner,1
        printf(
            "Asmc Macro Assembler C Include File Translator %d.%d\n"
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
        "/q           - Operate quietly\n"
        "/nologo      - Suppress copyright message\n"
        "/c<string>   - Specify string (calling convention) for PROTO\n"
        "/v<string>   - Specify string for PROTO using VARARG\n")

    exit(0)

exit_options endp


    .pragma warning(disable: 8019) ; assume byte..

;
; String macros
;
islalpha proto watcall c:byte {
    retm<([r15+rax+1] & (_UPPER or _LOWER))>
    }
isldigit proto watcall c:byte {
    retm<([r15+rax+1] & _DIGIT)>
    }
islalnum proto watcall c:byte {
    retm<([r15+rax+1] & (_DIGIT or _UPPER or _LOWER))>
    }
islpunct proto watcall c:byte {
    retm<([r15+rax+1] & _PUNCT)>
    }
islspace proto watcall c:byte {
    retm<([r15+rax+1] & _SPACE)>
    }
islxdigit proto watcall c:byte {
    retm<([r15+rax+1] & _HEX)>
    }
isid proto watcall c:byte {
    retm<([r15+rax+1] & (_LABEL or _DIGIT))>
    }
isidfirst proto watcall :byte {
    retm<([r15+rax+1] & _LABEL)>
    }
tokstart proto watcall string:string_t {
    movzx ecx,byte ptr [rax]
    .while ( [r15+rcx+1] & _SPACE )
        inc rax
        mov cl,[rax]
    .endw
    }


strtrim proc string:string_t

    .if strlen(rcx)

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


strstart proc string:string_t

    .while islspace([rcx])
        inc rcx
    .endw
    xchg rcx,rax
    ret

strstart endp


prevtok proc string:string_t, start:string_t

    .while ( rcx >= rdx && !isid([rcx]) )
        dec rcx
    .endw
    .while ( rcx >= rdx && isid([rcx]) )
        dec rcx
    .endw
    inc  rcx
    xchg rcx,rax
    ret

prevtok endp


prevtokz proc string:string_t, start:string_t

    .while ( rcx >= rdx && !isid([rcx]) )
        mov [rcx],ah
        dec rcx
    .endw
    .while ( rcx >= rdx && isid([rcx]) )
        dec rcx
    .endw
    inc  rcx
    xchg rcx,rax
    ret

prevtokz endp


nexttok proc string:string_t

    .repeat
        .if ( isid([rcx]) )
            inc rcx
            .while isid([rcx])
                inc rcx
            .endw
            .break
        .endif
        .if ( islpunct([rcx]) )
            inc rcx
        .endif
    .until 1

    tokstart(rcx)
    ret

nexttok endp


toksize proc string:string_t

    mov rdx,rcx
    .if ( isidfirst([rcx]) )
        inc rcx
        .while isid([rcx])
            inc rcx
        .endw
    .endif
    xchg rax,rcx
    sub rax,rdx
    ret

toksize endp


stripval proc uses rsi string:string_t

    ; strip (0U-199U) | 0x40000000000UI64

    mov rsi,rcx
    .while [rsi]

        .while !isldigit([rsi])
            mov rsi,nexttok(rsi)
            .break(1) .if !cl
        .endw
        inc rsi
        .if ( [rsi] == 'x' )
            inc rsi
        .endif

        .for ( : islxdigit([rsi]) : rsi++ )
        .endf
        .break .if !al
        .continue .if !islalpha([rsi])

        mov rcx,rsi
        .for ( : islalnum([rsi]) : rsi++ )
        .endf
        mov rdx,rsi
        mov rsi,rcx
        strcpy(rcx, rdx)
    .endw
    .return(string)

stripval endp


; #define CN_EVENT ((UINT)(-2))

striptype proc string:string_t

    .return .if !strchr(rcx, '(')
     mov r8,tokstart(&[rax+1])
    .return .if cl != '('
     mov rdx,tokstart(&[rax+1])
    .if cl == '('
        mov r8,rdx
        mov rdx,tokstart(&[rax+1])
    .endif
    .while isid([rdx])
        inc rdx
    .endw
    tokstart(rdx)
    .return .if cl != ')'
    strcpy(r8, &[rax+1])
    ret

striptype endp


wordxchg proc uses rdi rsi rbx r12 r13 string:string_t, token:string_t, new:string_t

   .new retval:int_t = 0

    mov r12,rcx
    mov r13,r8
    mov rdi,tempbuf
    mov rbx,strlen(rdx)

    .while strstr(r12, token)
        mov rsi,rax
        .if !isid([rsi-1])
            .if !isid([rsi+rbx])
                inc retval
                mov [rsi],0
                strcpy(rdi, r12)
                strcat(rdi, r13)
                strcat(rdi, &[rsi+rbx])
                strcpy(r12, rdi)
            .endif
        .endif
        lea r12,[rsi+rbx]
    .endw
    .return(retval)

wordxchg endp


strxchg proc uses rdi rsi rbx r12 string:string_t, token:string_t, new:string_t

    mov r12,rcx
    mov rdi,tempbuf
    mov rbx,strlen(rdx)

    .while strstr(r12, token)

        mov [rax],0
        lea rsi,[rax+rbx]
        mov rsi,strstart(rsi)
        strtrim(r12)
        strcpy(rdi, r12)
        strcat(rdi, new)
        strcat(rdi, rsi)
        strcpy(r12, rdi)
    .endw
    ret

strxchg endp


convert proc uses rsi string:string_t

    mov rsi,rcx

    striptype(rsi)
    stripval(rsi)

    strxchg(rsi, "<<", " shl ")
    strxchg(rsi, ">>", " shr ")
    strxchg(rsi, "==", " eq ")
    strxchg(rsi, ">=", " ge ")
    strxchg(rsi, "<=", " le ")
    strxchg(rsi, "||", " or ")
    strxchg(rsi, "&&", " and ")
    strxchg(rsi, ">",  " gt ")
    strxchg(rsi, "<",  " lt ")
    strxchg(rsi, "|",  " or ")
    strxchg(rsi, "&",  " and ")
    strxchg(rsi, "!",  " not ")
    strxchg(rsi, "~",  " not ")
    strxchg(rsi, "->",  ".")
    ret

convert endp


oprintf proc format:string_t, args:vararg

    .if ( cflags & FL_STBUF )

        mov rcx,strlen(filebuf)
        add rcx,filebuf
        .return vsprintf(rcx, format, &args)
    .endif

     mov cstart,1
    .return vfprintf(outfile, format, &args)

oprintf endp


errexit proc string:string_t

    fclose(srcfile)
    fclose(outfile)
    printf("%s(%d) : fatal error : %s\n", curfile, curline, string)
    exit(1)
    ret

errexit endp


eofexit proc

    .if ( cflags & FL_STBUF )

        fprintf(outfile, filebuf)
    .endif

    fclose(srcfile)
    fclose(outfile)
    exit(0)
    ret

eofexit endp


getline proc uses rsi rdi buffer:string_t

   .new comment_section:byte = 0

    mov rsi,buffer

    .while 1

        .if !fgets(rsi, MAXLINE, srcfile)
            eofexit()
        .endif

        inc curline

        .if comment_section
            .if strstr(rsi, "*/")
                strcpy(rsi, &[rax+2])
                dec comment_section
            .else
                .continue
            .endif
        .elseif strstr(rsi, "/*")
            mov byte ptr [rax],0
            mov rdi,rax
            inc rax
            .if strstr(rax, "*/")
                add rax,2
                strcpy(rdi, rax)
            .else
                inc comment_section
            .endif
        .endif
        .if comment_section
            .continue
        .endif
        .if strstr(rsi, "//")
            mov byte ptr [rax],0
        .endif

        strtrim(rsi)
        .return rsi
    .endw
    ret

getline endp


concat proc uses rdi string:string_t

    mov rdi,rcx
    lea rcx,[rdi+strtrim(rdi)+1]
    mov [rcx-1],' '
    getline(rcx)
   .return(rdi)

concat endp


concatf proc uses rdi string:string_t

    mov rdi,string
    lea rcx,[rdi+strlen(rdi)-1]

    .if ( [rcx] == '\' )

        .while 1

            mov [rcx],0
            lea rcx,[rdi+strlen(concat(rdi))-1]
            .break .if ( [rcx] != '\' )
        .endw
    .endif
    .return(rdi)

concatf endp


tokenize proc uses rsi rdi string:string_t

    mov rsi,rcx

    .while 1

        mov rdi,tokstart(rsi)
        mov tokpos,rdi

        .if ( [rdi] == 0 )
            mov csize,0
            mov ctoken,T_BLANK
           .return(T_BLANK)
        .endif

        .if ( [rdi] == '#' )

            inc rdi
            mov rdx,tokstart(rdi)
            .if ( rdx != rdi )
                strcpy(rdi, rdx)
            .endif
            dec rdi

            mov eax,[rdi+1]
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
                strcat(rax, &[rdi+5])
                strcpy(rdi, rax)
                mov csize,7
                mov ctoken,T_IF
                .return(T_IF)
            .case 'else'
                movzx eax,byte ptr [rdi+5]
                .if !islalpha(eax)
                    mov csize,5
                    mov ctoken,T_ELSE
                    .return(T_ELSE)
                .endif
            .default
                .for ( rdi++, ecx = 1 : islalpha([rdi]) : rdi++, ecx++ )
                .endf
                mov csize,ecx
                mov ctoken,T_IF
                .return(T_IF)
            .endsw
        .endif

        .if ( byte ptr [rdi] == '}' )
            mov csize,1
            mov ctoken,T_ENDS
            .return(T_ENDS)
        .endif

        .switch toksize(rdi)
        .case 4
            mov eax,[rdi]
            .if eax == 'mune'
                mov csize,4
                mov ctoken,T_ENUM
               .return(T_ENUM)
            .endif
            .endc
        .case 5
            .if !memcmp(rdi, "union", 5)
                mov csize,5
                mov ctoken,T_UNION
               .return(T_STRUCT)
            .endif
            .endc
        .case 6
            .if !memcmp(rdi, "struct", 6)
                mov csize,6
                mov ctoken,T_STRUCT
               .return(T_STRUCT)
            .endif
            .if !memcmp(rdi, "extern", 6)
                mov csize,6
                mov ctoken,T_EXTERN
               .return(T_EXTERN)
            .endif
            .endc
        .case 7
            .endc .if memcmp(rdi, "typedef", 7)
            mov csize,7
            mov ctoken,T_TYPEDEF
           .return(T_TYPEDEF)
        .case 8
            .if !memcmp(rdi, "EXTERN_C", 8)
                mov csize,8
                mov ctoken,T_EXTERN
               .return(T_EXTERN)
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
        oprintf("\n")
    .endif
    ret

parse_blank endp


; #[else]if[n]def

parse_if proc uses rdi

    mov rdi,tokpos
    convert(concatf(rdi))
    oprintf("%s\n", &[rdi+1])
    ret

parse_if endp


; #else/#endif/#undef

parse_else proc

    mov rdx,tokpos
    oprintf("%s\n", &[rdx+1])
    ret

parse_else endp


; #error

parse_error proc uses rdi

    mov rdi,tokpos
    .if strchr(rdi, '<')

        lea rdx,[rax+1]
        strcpy(rax, rdx)
        .if strchr(rdi, '>')
            lea rdx,[rax+1]
            strcpy(rax, rdx)
        .endif
    .endif
    oprintf(".err <%s>\n", &[rdi+7])
    ret

parse_error endp


; #pragma

parse_pragma proc uses rdi

    mov rdi,tokpos
    convert(concatf(rdi))
    oprintf(";.%s\n", &[rdi+1])
    ret

parse_pragma endp


; #include <name.h>

stripchr proc string:string_t, chr:int_t
    .if strchr(rcx, edx)
        lea rdx,[rax+1]
        strcpy(rax, rdx)
    .endif
    ret
stripchr endp


parse_include proc uses rdi

    mov rdi,tokpos
    .if stripchr(rdi, '<')
        stripchr(rdi, '>')
    .elseif stripchr(rdi, '"')
        stripchr(rdi, '"')
    .endif
    .if strrchr(rdi, '.')
        mov [rax],0
    .endif

    strcat(rdi, ".inc")
    oprintf("%s\n", &[rdi+1])
    ret

parse_include endp


exit_macro proc string:string_t

    .return oprintf("  exitm<%s>\n  endm\n", rcx)

exit_macro endp


; gues:
; #define n (x) - value
; #define n(x)  - macro

parse_define proc uses rsi rdi rbx r12

    mov rdi,tokpos
    mov r12,tokstart(&[rdi+7])
    mov rsi,nexttok(rax)
    mov al,[rsi-1]

    .if ( cl != '(' || ( cl == '(' && ( al == ' ' || al == 9 ) ) )

        convert(concatf(rdi))
        .if ( [rsi] == '"' || ( [rsi] == 'L' && [rsi+1] == '"' ) )
            strcpy(rsi, strcat(strcat(strcpy(tempbuf, "<"), rsi), ">"))
        .endif
        oprintf("%s\n", &[rdi+1])
       .return
    .endif

    mov [rsi],0
    inc rsi
    xor ebx,ebx
    .if strchr(rsi, ')')
        mov [rax],0
        mov rbx,tokstart(&[rax+1])
    .endif

    oprintf("%s macro %s\n", r12, rsi)

    .if ( !rbx )
        errexit(rsi)
    .endif
    strcpy(rdi, rbx)

    .while ( [rdi] == '\' )
        .return .if !getline(rdi)
        mov rdi,tokstart(rdi)
    .endw
    .if ( [rdi] == 0 )
        .return exit_macro(rdi)
    .endif
    .if ( [rdi+strlen(rdi)-1] != '\' )
        .return exit_macro(rdi)
    .endif

    .repeat

        mov [rdi+rax-1],0
        strtrim(rdi)
        convert(rdi)
        oprintf("    %s\n", tokstart(rdi))
       .return .if !getline(rdi)
    .until ( [rdi+strlen(rdi)-1] != '\' )

    convert(rdi)
    oprintf("    %s\n", tokstart(rdi))
   .return exit_macro("")

parse_define endp


; [typedef] enum [name] {

parse_enum proc uses rdi rbx

    mov rdi,tokpos
    mov rbx,nexttok(rdi)

    .if ( cl == 0 )
        .return .if !concat(rdi)
        mov rbx,strstart(rbx)
    .endif

    or cflags,FL_ENUM
    .if ( cl == '{' ) ; enum { --> } name;
        mov rax,filebuf
        mov [rax],0
        or cflags,FL_STBUF
       .return
    .endif

    .if ( cl == '_' ) ; enum _name { ... } name;
        inc rbx
    .endif
    oprintf(".%s\n", rbx)
    ret

parse_enum endp


; }[name][, type];

parse_ends proc uses rdi rbx

    mov rdi,tokpos

    .if ( cflags & FL_STBUF )

        and cflags,not FL_STBUF
        .if ( cflags & FL_ENUM )

            and cflags,not FL_ENUM
            mov rbx,nexttok(rdi)
            .if toksize(rbx)
                mov [rbx+rax],0
            .endif
            mov byte ptr [rdi],0
            oprintf(".enum %s {\n%s%s}\n", rbx, filebuf, linebuf)
        .endif
    .endif
    ret

parse_ends endp


strip_unsigned proc uses rsi rdi rbx string:string_t

    mov rdi,rcx
    .while strstr(rdi, "unsigned")

        mov rbx,rax
        mov rsi,tokstart(&[rax+8])
        mov ecx,toksize(rax)
        mov eax,[rsi]
        add rsi,rcx
        lea rdx,@CStr("dword")

        .switch ecx
        .case 7
            .if eax == 'ni__'
                lea rdx,@CStr("qword")
               .endc
            .endif
            lea rsi,[rbx+8]
            .endc
        .case 4
            .if eax == 'rahc'
                lea rdx,@CStr("byte")
               .endc
            .endif
            mov eax,[rsi+1]
            .if eax == 'gnol'
                add rsi,5
                lea rdx,@CStr("qword")
               .endc
            .endif
            lea rsi,[rbx+8]
            .endc
        .case 3
            .endc .if ax == 'ni'
            lea rsi,[rax+8]
            .endc
        .case 5
            .if eax == 'rohs'
                lea rdx,@CStr("word")
               .endc
            .endif
        .default
            lea rsi,[rbx+8]
        .endsw
        strcpy(tempbuf, rdx)
        strcat(rax, rsi)
        strcpy(rbx, rax)
    .endw

    wordxchg(rdi, "long long",   "sqword")
    wordxchg(rdi, "__int64",     "sqword")
    wordxchg(rdi, "long",        "sdword")
    wordxchg(rdi, "int",         "sdword")
    wordxchg(rdi, "char",        "sbyte")
    wordxchg(rdi, "short",       "sword")
    wordxchg(rdi, "float",       "real4")
    wordxchg(rdi, "double",      "real8")
    wordxchg(rdi, "...",         "vararg")
    ret

strip_unsigned endp


; type [*] name

parse_protoarg proc uses rsi rdi rbx arg:string_t

    mov rdi,tokstart(rcx)

    .if ( strchr(rdi, '*') )
        oprintf(" :ptr")
       .return( 1 )
    .endif

    lea rbx,[rdi+strtrim(rdi)]
    .if !strcmp(rdi, "void")
        .return( 0 )
    .endif

    mov rbx,prevtok(rbx, rdi)
    .if ( rbx > rdi )
        dec rbx
        mov rbx,prevtokz(rbx, rdi)
    .endif
    oprintf(" :%s", rbx)
   .return( 1 )

parse_protoarg endp


; args );

parse_protoargs proc uses rsi rdi rbx args:string_t, comma:int_t

     mov rdi,rcx
     mov ebx,edx
     .if !strrchr(rdi, ')')
        .return errexit(rdi)
     .endif
     mov [rax],0

    .while strchr(rdi, '(')
        mov rsi,rax
        .if !strchr(rdi, ')')
            .return errexit(rsi)
        .endif
        strcpy(rsi, &[rax+1])
    .endw
    .while strstr(rdi, "const ")
        mov rsi,rax
        strcpy(rsi, &[rax+6])
    .endw

    .while rdi
        xor esi,esi
        .if strchr(rdi, ',')
            mov [rax],0
            lea rsi,[rax+1]
        .endif
        .if ( ebx )
            oprintf(",")
        .endif
        parse_protoarg(rdi)
        inc ebx
        mov rdi,rsi
    .endw
    ret

parse_protoargs endp


; name( args );

parse_proto proc uses rsi rdi rbx p:string_t

    mov rdi,rcx
    strrchr(rdi, '(')
    mov [rax],0
    mov rbx,rax
    mov rsi,tokstart(&[rax+1])

    oprintf("%s proto", prevtokz(rbx, rdi))

    .ifd ( strip_unsigned(rsi) && option_v )
        oprintf(" %s", option_v)
    .elseif ( option_c )
        oprintf(" %s", option_c)
    .endif

    parse_protoargs(rsi, 0)
    oprintf("\n")
    ret

parse_proto endp


; (name)( args );

parse_callback proc uses rsi rdi p:string_t

    mov rdi,rcx
    oprintf("CALLBACK(")

    .if !strrchr(rdi, '(')
        .return errexit(rdi)
    .endif
    mov [rax],0
    mov rsi,tokstart(&[rax+1])
    strip_unsigned(rsi)

    .if !strrchr(rdi, ')')
        .return errexit(rdi)
    .endif
    oprintf("%s", prevtokz(rax, rdi))
    parse_protoargs(rsi, 1)
    oprintf(")\n")
    ret

parse_callback endp


concat_line proc uses rdi rbx buffer:string_t

    .while !strrchr(rdi, ';')
        concat(rdi)
    .endw
    .if strstr(rdi, "__attribute__")
        mov rcx,rax
        .if ( [rax-1] == ' ' )
            dec rcx
        .endif
        lea rdx,[rax+13]
        mov al,[rdx]
        .if ( al == '(' )
            .for ( ebx = 0 : al : rdx++, al = [rdx] )
                .if ( al == '(' )
                    inc ebx
                .elseif ( al == ')' )
                    dec ebx
                    .ifz
                        inc rdx
                        .break
                    .endif
                .endif
            .endf
        .endif
        strcpy(rcx, rdx)
    .endif
    .return(rdi)
    ret

concat_line endp


parse_id proc uses rsi rdi rbx

    mov rdi,tokpos

    .if ( cflags & FL_ENUM )

        convert(rdi)
        oprintf("%s\n", linebuf)
       .return
    .endif

    mov rsi,strchr(rdi, ';')
    mov rbx,strchr(rdi, '(')
    .if ( rsi && rbx )
        .return parse_proto(rdi)
    .endif

    .if ( !rsi && !rbx ) ; macro ?

        fgets(tempbuf, MAXLINE, srcfile)
        .if ( !rax || [rax] == 10 )

            inc curline
            oprintf("%s\n\n", linebuf)
           .return
        .endif
        tokenize(strcpy(linebuf, tempbuf))
       .return parseline()
    .endif

    .if ( !rsi && rbx )

        .return .if strchr(rdi, ')')
         nexttok(rdi)
        .return .if ( cl == '(' )
    .endif
    .if strchr(concat_line(rdi), '(')
        .return parse_proto(rdi)
    .endif
    ret

parse_id endp


; type name[, name2, ...];
; type (*name)(args);

parse_struct_member proc uses rsi rdi rbx r12 r13 r14

    mov rdi,tokpos
    mov r12d,strip_unsigned(rdi)

    .if strchr(rdi, '(')
        .if ( [tokstart(&[rax+1])] == '*' )
            .if strchr(rax, ')')
                lea rbx,[rax+1]
                mov rsi,prevtokz(rax, rdi)
                movzx eax,clevel
                dec eax
                lea ecx,[rax-23]
                oprintf("%*s%*s proc", eax, "", ecx, rsi)

                .ifd ( r12d && option_v )
                    oprintf(" %s", option_v)
                .elseif ( option_c )
                    oprintf(" %s", option_c)
                .endif
                mov rbx,tokstart(rbx)
                .if ( cl == '(' )
                    inc rbx
                .elseif strchr(rbx, '(')
                    lea rbx,[rax+1]
                .endif
                parse_protoargs(tokstart(rbx), 0)
                oprintf("\n")
               .return
            .endif
        .endif
    .endif

    lea r12,@CStr("ptr ")
    xor ebx,ebx
    xor r13,r13
    .if strchr(rdi, ',')
        mov [rax],0
    .endif
    mov r14,rax
    .if strrchr(rdi, '[')
        mov [rax],0
        lea rbx,[rax+1]
        .if strchr(rbx, ']')
            mov [rax],0
        .endif
        lea rsi,[rdi+strtrim(rdi)-1]
    .elseif strrchr(rdi, ':')
        mov [rax],0
        lea rsi,[rax-1]
        mov r13,tokstart(&[rax+1])
        .if strchr(r13, ';')
            mov [rax],0
        .endif
    .elseif r14
        mov rsi,r14
    .else
        mov rsi,strrchr(rdi, ';')
    .endif
    mov rsi,prevtokz(rsi, rdi)

    movzx eax,clevel
    dec eax
    lea ecx,[rax-24]
    oprintf("%*s%*s", eax, "", ecx, rsi)
    mov [rsi],0

    ; reduce type to 2: [unsigned] type [*]

    lea rax,[rdi+strtrim(rdi)]
    mov rsi,prevtok(rax, rdi)
    .if ( rsi > rdi )
        dec rax
        .if prevtok(rax, rdi) > rdi
            mov rdi,rax
        .endif
    .endif

    .if strchr(rsi, '*')
        mov [rax],0
        strtrim(rsi)
    .else
        add r12,4
    .endif

    .if ( rsi > rdi )
        mov rdi,rsi
    .endif

    .if rbx
        oprintf("%s%s %s dup(?)\n", r12, rdi, rbx)
    .elseif r13
        oprintf("%s%s : %2s ?\n", r12, rdi, r13)
    .else
        oprintf("%s%s ?\n", r12, rdi)
    .endif

    .while r14

        mov rsi,tokstart(&[r14+1])
        mov r14,strchr(rsi, ',')
        .if rax
            mov [rax],0
        .elseif strrchr(rsi, ';')
            mov [rax],0
        .endif

        xor ebx,ebx
        .if strrchr(rsi, '[')
            mov [rax],0
            lea rbx,[rax+1]
            .if strchr(rbx, ']')
                mov [rax],0
            .endif
        .endif
        strtrim(rsi)
        movzx eax,clevel
        dec eax
        lea ecx,[rax-24]
        oprintf("%*s%*s", eax, "", ecx, rsi)
        .if rbx
            oprintf("%s%s %s dup(?)\n", r12, rdi, rbx)
        .else
            oprintf("%s%s ?\n", r12, rdi)
        .endif
    .endw

    xor  eax,eax
    test r13,r13
    setnz al
    ret

parse_struct_member endp


; [typedef] <struct|union> [name] {

parse_struct proc uses rsi rdi rbx

    .new name[256]:char_t
    .new type:string_t = "struct"
    .new oldfilebuf:string_t = filebuf
    .new oldflags:dword = cflags

    .if ( ctoken == T_UNION )
        mov type,&@CStr("union")
    .endif

    mov rdi,tokpos
    mov rbx,nexttok(rdi)
    .if ( cl == 0 )
        concat(rdi)
        mov rbx,strstart(rbx)
    .endif
    .if !strchr(rdi, '{')
        .if !strchr(rdi, ';')
            concat(rdi)
        .endif
    .endif
    .if strchr(rdi, '{')
        mov byte ptr[rax], 0
    .endif

    xor esi,esi
    .if strchr(rbx, ';')
        mov rsi,prevtokz(rax, rbx)
        oprintf("%-23s typedef ", rsi)
        mov byte ptr [rsi],0
        .if strchr(rbx, '*')
            mov byte ptr [rax],0
            oprintf("ptr ")
        .endif
    .endif
    .if strtrim(rbx)
        mov rbx,prevtokz(&[rbx+rax-1], rbx)
    .endif
    .if ( rsi )
        oprintf("%s\n", rbx)
       .return
    .endif

    strcpy(&name, rbx)

    inc clevel
    or  cflags,FL_STRUCT

    .if ( clevel > 1 )
        mov filebuf,malloc(MAXBUF)
        or  cflags,FL_STBUF
    .else
        oprintf("%-23s %s\n", rbx, type)
    .endif

    mov rdi,linebuf
    .while 1

        .switch tokenize(getline(rdi))
        .case T_ID
            concat_line(rdi)
            parse_struct_member()
            .endc
        .case T_STRUCT
            parse_struct()
            .endc
        .case T_ENDS

            xor ebx,ebx
            .if strchr(rdi, ',')
                mov byte ptr [rax],0
                lea rbx,[rax+1]
            .elseif strrchr(rdi, ';')
                mov byte ptr [rax],0
                lea rbx,[rax+1]
            .endif
            mov rdi,nexttok(tokpos)

            dec clevel
            .if ( clevel )
                movzx ebx,clevel
                sub ebx,2
                oprintf("%*s ends\n", ebx, "")
                mov rsi,filebuf
                mov filebuf,oldfilebuf
                .if ( !( oldflags & FL_STBUF) )
                    and cflags,not FL_STBUF
                .endif
                oprintf("%*s%s %s\n%s",  ebx, "", type, rdi, rsi)
                free(rsi)
                .break
            .endif

            strtrim(rdi)
            lea rsi,name
            .if ( name )
                oprintf("%-23s ends\n", rsi)
                .if ( byte ptr [rdi] )
                    .if strcmp(rsi, rdi)
                        oprintf("%-23s typedef %s\n", rdi, rsi)
                    .endif
                .endif
            .else
                oprintf("%-23s ends\n", rdi)
            .endif

            .break .if !rbx
            mov rbx,strstart(rbx)
            .break .if !byte ptr [rbx]

            .while strchr(rbx, ',')

                mov byte ptr [rax],0
                mov rdi,rbx
                lea rbx,[rax+1]
                mov rdi,strstart(rdi)
                .if strrchr(rdi, '*')
                    mov rdi,rax
                .endif
                .if ( byte ptr [rdi] == '*' )
                    oprintf("%-23s typedef ptr %s\n", &[rdi+1],rsi)
                .else
                    oprintf("%-23s typedef %s\n", rdi, rsi)
                .endif
            .endw
            .break .if !strchr(rbx, ';')

            mov byte ptr [rax],0
            mov rdi,rbx
            lea rbx,[rax+1]
            mov rdi,strstart(rdi)
            .if strrchr(rdi, '*')
                mov rdi,rax
            .endif
            .if byte ptr [rdi] == '*'
                oprintf("%-23s typedef ptr %s\n", addr [rdi+1], rsi)
            .else
                oprintf("%-23s typedef %s\n", rdi, rsi)
            .endif
            .break
        .default
            parseline()
        .endsw
    .endw
    ret

parse_struct endp


; typedef type name;
; typedef type (name)(args);

parse_typedef proc uses rsi rdi rbx

    mov rdi,tokpos
    mov rbx,nexttok(rdi)
    .if ( cl == 0 )
        getline(rbx)
        mov rbx,strstart(rdi)
    .endif
    .ifd ( toksize(rbx) == 4 )
        .if !memcmp(rbx, "enum", 4)
            mov tokpos,rbx
            .return parse_enum()
        .endif
    .elseif ( eax == 5 || eax == 6 )
        xor esi,esi
        .if !memcmp(rbx, "struct", 6)
            mov esi,T_STRUCT
            mov eax,6
        .elseif !memcmp(rbx, "union", 5)
            mov esi,T_UNION
            mov eax,5
        .endif
        .if esi
            mov tokpos,rbx
            mov ctoken,sil
            mov csize,eax
            .return parse_struct()
        .endif
    .endif

    strip_unsigned(concat_line(rdi))
    strrchr(rdi, ';')
    .if ( [rax-1] == ')' )
        .return parse_callback(rdi)
    .endif

    mov rsi,prevtokz(rax, rdi)
    oprintf("%-23s typedef ", rsi)
    mov [rsi],0
    .if strchr(rdi, '*')
        mov [rax],0
        oprintf("ptr ")
    .endif
    .if strtrim(rdi)
        mov rdi,prevtokz(&[rdi+rax-1], rdi)
    .endif
    oprintf("%s\n", rdi)
    ret

parse_typedef endp


parse_interface proc
    ret
parse_interface endp


parse_extern proc uses rsi rdi rbx

    mov rdi,tokpos
    concat_line(rdi)
    .if strchr(rdi, ')')
        lea rbx,[rax+1]
        tokstart(rbx)
        .if ( cl == '_' )
            mov word ptr [rbx],';'
        .endif
        add tokpos,7
        .return parse_id()
    .endif

    strip_unsigned(rdi)
    mov rsi,prevtokz(strrchr(rdi, ';'), rdi)
    oprintf("externdef %s:", rsi)

    mov [rsi],0
    .if strchr(rdi, '*')
        mov [rax],0
        oprintf("ptr ")
    .endif
    .if strtrim(rdi)
        mov rdi,prevtokz(&[rdi+rax-1], rdi)
    .endif
    oprintf("%s\n", rdi)
    ret

parse_extern endp


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
    .case T_EXTERN
        .return parse_extern()
    .endsw
    ret
parseline endp


define EH_STACK_INVALID    0x08
define EH_NONCONTINUABLE   0x01
define EH_UNWINDING        0x02
define EH_EXIT_UNWIND      0x04
define EH_NESTED_CALL      0x10

GeneralFailure proc \
    ExceptionRecord   : PEXCEPTION_RECORD,
    EstablisherFrame  : ptr dword,
    ContextRecord     : PCONTEXT,
    DispatcherContext : LPDWORD

    .new signo:int_t = SIGTERM
    .new string:string_t = "Software termination signal from kill"

     mov eax,[rcx].EXCEPTION_RECORD.ExceptionFlags
    .switch
    .case eax & EH_UNWINDING
    .case eax & EH_EXIT_UNWIND
       .endc
    .case eax & EH_STACK_INVALID
    .case eax & EH_NONCONTINUABLE
        mov signo,SIGSEGV
        mov string,&@CStr("Segment violation")
       .endc
    .case eax & EH_NESTED_CALL
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

        printf(
            "This message is created due to unrecoverable error\n"
            "and may contain data necessary to locate it.\n"
            "\n"
            "\tException Code: %08X\n"
            "\tException Flags %08X\n"
            "\n"
            "\t  regs: RAX: %016lX R8:  %016lX\n"
            "\t\tRBX: %016lX R9:  %016lX\n"
            "\t\tRCX: %016lX R10: %016lX\n"
            "\t\tRDX: %016lX R11: %016lX\n"
            "\t\tRSI: %016lX R12: %016lX\n"
            "\t\tRDI: %016lX R13: %016lX\n"
            "\t\tRBP: %016lX R14: %016lX\n"
            "\t\tRSP: %016lX R15: %016lX\n"
            "\t\tRIP: %016lX\n\n"
            "\t     EFlags: %s\n"
            "\t\t     r n oditsz a p c\n\n",
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
            [r11].CONTEXT._Rip, &flags)

    .endif
    errexit(string)

GeneralFailure endp


main proc frame:GeneralFailure argc:int_t, argv:array_t

    .for ( rsi = &[rdx+8], ebx = 1 : ebx < argc : ebx++ )

        lodsq
        .if ( [rax] == '-' || [rax] == '/' )

            mov dl,[rax+1]

            .switch pascal dl
            .case '?'
                exit_options()
            .case 'q'
                mov option_q,1
                mov banner,1
            .case 'n'
                mov banner,1
            .case 'c'
                add rax,2
                mov option_c,rax
            .case 'v'
                add rax,2
                mov option_v,rax
            .endsw
        .else
            mov curfile,rax
        .endif
    .endf

    write_logo()

    mov rsi,curfile
    .if ( rsi == NULL )
        exit_usage()
    .endif

    .if ( !fopen(rsi, "rt") )

        perror(rsi)
       .return( 1 )
    .endif

    mov srcfile,rax
    mov linebuf,malloc(MAXBUF)
    mov filebuf,malloc(MAXBUF)
    mov tempbuf,malloc(MAXBUF)

    mov rdi,rax
    .if ( strrchr(strcpy(rdi, rsi), '\') )
        inc rax
        strcpy(rdi, rax)
    .endif

    .if strrchr(rdi, '.')
        strcpy(rax, ".inc")
    .else
        strcat(rdi, ".inc")
    .endif
    .if !fopen(rdi, "wt")

        fclose(srcfile)
        perror(rdi)
       .return( 1 )
    .endif
    mov outfile,rax

    lea r15,_ltype
    .if ( !option_q )
        printf( " Translating: %s\n", curfile)
    .endif

    .while 1

        tokenize(getline(linebuf))
        parseline()
    .endw

    fclose(srcfile)
    fclose(outfile)
   .return(0)

main endp

    end _tstart
