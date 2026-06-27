; BTEST.ASM--
;
; creat test from a binary (or a GAS test case (*-intel.d) file):
;  objdump -w -M intel -b binary -D -m i386:x86-64 test.bin > test.d
;  btest test.d
;
; Build: asmc64 btest.asm
;

include stdio.inc
include stdlib.inc
include string.inc

define BUFSIZE 4096 ; Size of line buffer

.data?
 buf db BUFSIZE dup(?)
 src db BUFSIZE dup(?)
 bin db BUFSIZE dup(?)
.code

print_usage proc
    printf( "Usage: btest <file>.d\n" )
    .return( 0 )
    endp

    assume rbx:string_t, rsi:string_t, rdi:string_t

convertfile proc uses rsi rdi rbx name:string_t

    .new fp:LPFILE = fopen(name, "r")
    .new fo:LPFILE
    .new line:long_t = 0
    .new first_char:byte

    .if ( fp == NULL )
        perror(name)
       .return( 0 )
    .endif

    .for ( rbx = &buf : fgets(rbx, BUFSIZE, fp) : )
        .if ( [rbx] == '0' )
            inc line
           .break
        .endif
    .endf
    .if ( line == 0 )
        fclose(fp)
       .return( 0 )
    .endif
    .if ( strrchr( strcpy(&bin, strfn(name)), '.' ) == NULL ||
          word ptr [rax+1] != 'd' )
        printf( "<file>.d was expected: %s\n",  &bin)
        fclose(fp)
       .return( 0 )
    .endif
    strcpy(rax, ".asm")
    .if !fopen(&bin, "w")
        perror(&bin)
        fclose(fp)
       .return( 0 )
    .endif
    mov fo,rax

    fprintf(fo,
        "; %s\n"
        "testcase macro B, S\n"
        " ifdef BIN\n"
        "  db B\n"
        " else\n"
        "  S\n"
        " endif\n"
        " endm\n"
        ".code\n", strfn(name))

    .while fgets(rbx, BUFSIZE, fp)

        mov rsi,strchr(rbx, ':')

        .break .if ( rsi == NULL )

        ; [   ]*[a-f0-9]+:    62 f1 d5 48 58 f4       vaddpd zmm6,zmm5,zmm4
        ; [   ]*[a-f0-9]+:[   ]*62 f3 d5 48 ce f4 ab[     ]*vgf2p8affineqb zmm6,zmm5,zmm4,0xab
        ; \s*...\s+

        lodsb
        lodsb
        mov first_char,al
        .if ( al == '[' )
            .break .if ( strchr(rsi, ']') == NULL )
            lea rsi,[rax+1]
            .break .if ( [rsi] != '*' )
            lodsb
        .elseif ( al == 9 )
            .while ( [rsi] == ' ' || [rsi] == 9 )
                inc rsi
            .endw
        .elseif ( al == '\' )
            lodsb
            .break .if ( al != 's' )
            lodsb
            .break .if ( al != '*' )
        .else
            .break
        .endif
        lodsb
        lea rdi,bin
        mov rdx,rdi
        .while ( al && al != first_char )
            stosb
            lodsb
        .endw
        .if ( al == '\' && al == first_char )
            lodsb
            .break .if ( al != 's' )
            lodsb
            .break .if ( al != '+' )
            mov al,'\'
        .endif
        .while ( rdi > rdx && [rdi-1] == ' ' )
            dec rdi
            mov [rdi],0
        .endw
        .break .if ( rdi == rdx || al != first_char )
        mov [rdi],0

        .if ( al == '[' )
            .break .if ( strchr(rsi, ']') == NULL )
            lea rsi,[rax+1]
            .break .if ( [rsi] != '*' )
            lodsb
        .endif
        strtrunc(rsi)
        mov rsi,rcx
        lodsb
        lea rdi,src
        mov rdx,rdi
        .while ( al > 13 )
            .if ( al != '\' )
                stosb
            .endif
            lodsb
        .endw
        .while ( rdi > rdx && [rdi-1] == ' ' )
            dec rdi
            mov [rdi],0
        .endw
        .break .if ( rdi == rdx || al )
        mov [rdi],0
        fprintf(fo, "testcase <" )
        .for ( rbx = &bin : [rbx] : )
            movzx ecx,[rbx]
            movzx edx,[rbx+1]
            fprintf(fo, "0x%c%c", ecx, edx)
            add rbx,2
            .if ( [rbx] == ' ' )
                inc rbx
                fprintf(fo, ", ")
            .endif
        .endf
        lea rbx,buf
        fprintf(fo, ">, <%s>\n", &src )
    .endw
    fprintf(fo, "end\n" )
    fclose(fo)
    fclose(fp)
    .return( line )
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
        mov eax,dword ptr [rbx]
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
            printf( "convert file: %s\n", strfn(&path) )
            convertfile(&path)
        .endsw
    .endf
    .return( 0 )
    endp
    end
