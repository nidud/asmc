; STRIP.ASM--
;
; remove dubicated lines from a test case
;

include stdio.inc
include stdlib.inc
include string.inc

define BUFSIZE 4096 ; Size of line buffer

.data?
 buf db BUFSIZE dup(?)
 src string_t 16000 dup(?)
.code

print_usage proc
    printf( "Usage: strip <file>.d\n" )
    .return( 0 )
    endp

convertfile proc uses rsi rdi rbx name:string_t

    .new fp:LPFILE = fopen(name, "r")
    .new fo:LPFILE
    .new lines:dword = 0

    .if ( fp == NULL )
        perror(name)
       .return( 0 )
    .endif

    .if ( strrchr( strcpy(&buf, strfn(name)), '.' ) == NULL ||
          word ptr [rax+1] != 'd' )
        printf( "<file>.d was expected: %s\n",  &buf)
        fclose(fp)
       .return( 0 )
    .endif
    strcpy(rax, ".asm")
    .if !fopen(&buf, "w")
        perror(&buf)
        fclose(fp)
       .return( 0 )
    .endif
    mov fo,rax
    lea rbx,buf
    lea rdi,src
    .while fgets(rbx, BUFSIZE, fp)
        _strdup(rbx)
        stosq
    .endw
    stosq
    fclose(fp)
    lea rsi,src
    lodsq
    .while rax
        .for ( rbx = rax, eax = 0, rdi = rsi : rax != [rdi] : rdi+=string_t )
            .ifd !strcmp(rbx, [rdi])
                inc eax
                inc lines
               .break
            .endif
            xor eax,eax
        .endf
        .if ( eax == 0 )
            fprintf(fo, rbx )
        .endif
        lodsq
    .endw
    fclose(fo)
    .return( lines )
    endp

main proc argc:int_t, argv:array_t

    .new path[_MAX_PATH]:char_t = 0
    .new i:int_t
    .if ( argc == 1 )
        .return print_usage()
    .endif

    .for ( i = 1 : i < argc : i++ )

        mov ecx,i
        mov rdx,argv
        mov rbx,[rdx+rcx*size_t]
        mov eax,[rbx]
        .switch al
ifndef __UNIX__
        .case '?'
        .case '/'
endif
        .case '-'
        .case 'h'
            .return( print_usage() )
        .default
            .if !_fullpath(&path, rbx, _MAX_PATH)
                perror(rbx)
               .endc
            .endif
            printf( "%d lines stripped from: %s\n", convertfile(&path), rbx )
        .endsw
    .endf
    .return( 0 )
    endp
    end
