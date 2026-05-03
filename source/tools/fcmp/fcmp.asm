; FCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2024-08-15 - updated for Linux
; 2013-10-23 - created for the regression test of ASMC
;
include io.inc
include stdio.inc
include stdlib.inc
include fcntl.inc
include tchar.inc

.code

print_usage proc

    printf( "Usage:     fcmp [-option] <file1> <file2>\n"
            "\n"
            "-d         Desimal (default is hex)\n"
            "-v         Verbose\n"
            "-p         Compare PE\n"
            "-c         Compare COFF\n"
            "-o<offs>   Offset start of compare\n"
            "-n<lines>  Number of lines (default is 10)\n"
            "\n" )

    xor eax,eax
    ret

print_usage endp


main proc argc:int_t, argv:array_t

   .new file1:string_t = NULL
   .new file2:string_t = NULL
   .new buffer1:string_t
   .new buffer2:string_t
   .new compare_coff:char_t = 0
   .new compare_pe:char_t = 0
   .new desimal:char_t = 0      ; default is hex
   .new verbose:char_t = 0
   .new off_start:int_t = 0     ; Offset start of compare
   .new lines:int_t = 10        ; Number of lines (default is 10)
   .new size1:size_t
   .new size2:size_t
   .new rsize1:size_t
   .new rsize2:size_t
   .new unequal:uint_t = 0
   .new h1:int_t
   .new h2:int_t
   .new a:int_t
   .new b:int_t
   .new i:int_t
   .new p:string_t
   .new q:string_t

    .if ( argc == 1 )

        .return( print_usage() )
    .endif

    .for ( i = 1 : i < argc : i++ )

        mov ecx,i
        mov rdx,argv
        mov rcx,[rdx+rcx*size_t]
        mov eax,[rcx]

        .switch al
ifndef __UNIX__
        .case '/'
endif
        .case '-'

            shr eax,8
            .switch al
            .case 'd'
                inc desimal
               .endc
            .case 'c'
                inc compare_coff
               .endc
            .case 'p'
                inc compare_pe
               .endc
            .case 'v'
                inc verbose
               .endc
            .case 'n'
                add rcx,2
                .if atol(rcx)
                    mov lines,eax
                .endif
                .endc
            .case 'o'
                add rcx,2
                .if atol(rcx)
                    mov off_start,eax
                .endif
                .endc
            .default
                perror(rcx)
               .return(1)
            .endsw
            .endc
        .default
            .if file1
                mov file2,rcx
            .else
                mov file1,rcx
            .endif
        .endsw
    .endf

    .if ( !file1 || !file2 )

        print_usage()
       .return( 1 )
    .endif

    .ifd ( _open(file1, O_RDONLY or O_BINARY, 0) == -1 )

        perror(file1)
       .return( 1 )
    .endif
    mov h1,eax

    .ifd ( _open(file2, O_RDONLY or O_BINARY, 0) == -1 )

        perror(file2)
       .return( 1 )
    .endif
    mov h2,eax

    mov size2,_filelength(eax)
    mov size1,_filelength(h1)

    .if !malloc(0x10000*2)

        perror("No memory")
       .return( 1 )
    .endif
    mov buffer1,rax
    add rax,0x10000
    mov buffer2,rax

    .if !_read(h1, buffer1, 0x10000)

        perror("Read error")
       .return( 1 )
    .endif
    mov rsize1,rax

    .if !_read(h2, buffer2, 0x10000)

        perror("Read error")
       .return( 1 )
    .endif
    mov rsize2,rax

    mov rsi,buffer1
    mov rdi,buffer2
    mov rbx,size1
    mov eax,off_start

    .if ( rax >= rbx )

        printf("%s: Offset >= File Size\n", file1)
       .return( 1 )
    .endif

    sub rbx,rax
    add rsi,rax
    add rdi,rax

    .if ( compare_pe )

        .repeat

            .repeat

                mov     eax,[rsi+0x3C]
                add     rsi,rax
                .break .if ( size1 < rax )
                .break .if ( dword ptr [rsi] != 'EP' )

                mov     eax,[rdi+0x3C]
                add     rdi,rax
                .break .if ( size2 < rax )
                .break .if ( dword ptr [rdi] != 'EP' )

                mov     a,[rsi+4+20+0x3C]
                mov     b,[rdi+4+20+0x3C]
                movzx   eax,word ptr [rsi+4+2]
                imul    ecx,eax,40
                add     ecx,0xE0+20+4
                mov     eax,[rsi+8]
                mov     [rdi+8],eax

                .repeat

                    repe cmpsb
                    .break .ifz

                    mov     p,rsi
                    mov     q,rdi
                    inc     unequal
                    mov     rbx,rcx
                    mov     rax,rsi
                    sub     rax,buffer1
                    dec     eax
                    movzx   ecx,byte ptr [rdi-1]
                    movzx   edx,byte ptr [rsi-1]

                    .if ( desimal )
                        printf("%d: %d %d\n", eax, edx, ecx)
                    .else
                        printf("%08X: %02X %02X\n", eax, edx, ecx)
                    .endif
                    mov rsi,p
                    mov rdi,q
                    mov rcx,rbx
                    dec lines
                   .break .ifz
                .until !rcx

                mov     rsi,buffer1
                mov     eax,a
                add     rsi,rax
                sub     rsize1,rax
                .break .ifb
                mov     rdi,buffer2
                mov     eax,b
                add     rdi,rax
                sub     rsize2,rax
                .break .ifb
                .break( 1 )
            .until 1
            perror("invalid PE binary")
           .return( 1 )
        .until 1

    .elseif ( compare_coff )

        mov eax,[rdi+4]
        mov [rsi+4],eax
    .endif

    .if ( size1 != size2 )

        printf("%s(%d), %s(%d): file sizes differ\n", file1, size1, file2, size2)
        inc unequal
    .endif

    .while 1

        mov rsi,buffer1
        mov rdi,buffer2
        mov rcx,rsize1
        .if rcx > rsize2
            mov rcx,rsize2
        .endif
        .break .if !rcx
        .repeat
            repe cmpsb
            mov p,rsi
            mov q,rdi
            .break .ifz
            inc unequal
            mov ebx,ecx
            mov rax,rsi
            sub rax,buffer1
            dec eax
            movzx ecx,byte ptr [rdi-1]
            movzx edx,byte ptr [rsi-1]
            .if ( desimal )
                printf("%d: %d %d\n", eax, edx, ecx)
            .else
                printf("%08X: %02X %02X\n", eax, edx, ecx)
            .endif
            mov rsi,p
            mov rdi,q
            mov ecx,ebx
            dec lines
           .break .ifz
        .until !ecx
        mov rsize1,_read(h1, buffer1, 0x10000)
        mov rsize2,_read(h2, buffer2, 0x10000)
    .endw

    .if !unequal
        .if ( verbose )
            printf("%s == %s (Ok)\n", file1, file2)
        .endif
        xor eax,eax
    .else
        printf("%d unequal bytes found cmp(%s, %s)\n", unequal, file1, file2)
        mov eax,1
    .endif
    ret

main endp

    end _tstart
