
; This strips the objconv output for comments
; and removes '@' and '$' from labels.

include io.inc
include ctype.inc
include stdio.inc
include string.inc

.code

main proc argc:int_t, argv:array_t

    .new fp:ptr FILE
    .new ft:ptr FILE
    .new file:string_t
    .new p:string_t
    .new lsize:int_t
    .new tmp[256]:char_t
    .new buf[512]:char_t

    .if ( argc != 2 )

        printf("Usage: strip_s <file>\n")
       .return( 0 )
    .endif
    ldr rsi,argv
    mov rbx,[rsi+size_t]
    mov file,rbx
    .if ( strrchr(strcpy(&tmp, rbx), '.') )
        mov byte ptr [rax],0
    .endif
    strcat(&tmp, ".tmp")
    .if ( fopen(rbx, "rt") == NULL )
        perror(rbx)
       .return 1
    .endif
    mov fp,rax
    ; binary not needed for Unix...
    .if ( fopen(&tmp, "wb") == NULL )
        perror(&tmp)
        fclose(fp)
       .return 1
    .endif
    mov ft,rax

    lea rbx,buf
    .while fgets(rbx, 512, fp)

        .continue .if byte ptr [rbx] == '#'
        .if strchr(rbx, '#')
            mov byte ptr [rax],0
        .endif
        mov lsize,strtrim(rbx)
        .if ( eax == 0 )
            fprintf(ft, "\n")
           .continue
        .endif
        .ifd ( memcmp(rbx, ".type", 5) == 0 )
           .continue
        .endif
        .if ( lsize > 4 )
            .while 1
                mov p,rbx
                movzx eax,byte ptr [rbx]
                inc rbx
                .switch al
                .case 0
                    .break
                .case 39
                .case '"'
                    mov cl,al
                    .repeat
                        mov al,[rbx]
                        inc rbx
                        .break(1) .if !al
                    .until al == cl
                    .continue
                .endsw
                .continue .ifd !isspace(eax)
                .repeat
                    movzx ecx,byte ptr [rbx]
                    inc rbx
                .untild !isspace(ecx)
                dec rbx
                .while 1
                    lea rax,buf
                    mov rdx,p
                    mov rdi,rdx
                    sub rdi,rax
                    mov rcx,rdi
                    add rdi,8
                    and rdi,-8
                    sub rdi,rcx
                    lea rcx,[rbx+1]
                    sub rcx,rdx
                    .break .if ecx < 3
                    .break .if ecx <= edi
                    mov byte ptr [rdx],9
                    inc rdx
                    mov ecx,edi
                    dec ecx
                    .ifnz
                        mov rdi,rdx
                        add rdx,rcx
                        mov al,1
                        rep stosb
                    .endif
                    mov p,rdx
                .endw
                .if ecx
                    dec ecx
                    .ifnz
                        mov al,' '
                        mov rdi,p
                        rep stosb
                    .endif
                .endif
            .endw
            .for ( rbx = &buf, rsi = rbx, rdi = rbx : byte ptr [rsi] : )
                lodsb
                .if ( al != 1 )
                    stosb
                .endif
            .endf
            mov byte ptr [rdi],0
        .endif
        .ifd ( memcmp(rbx, "\t.type", 5) == 0 )
           .continue
        .endif
        .ifd ( memcmp(rbx, "\t.size", 5) == 0 )
           .continue
        .endif
        .if strstr(rbx, "I$@C")
            mov rcx,rax
            strcpy(rcx, &[rax+1])
            mov byte ptr [rax],'I'
        .endif
        .if strstr(rbx, "@C")
            mov byte ptr [rax],'L'
        .endif
        .if strstr(rbx, "D$")
            mov byte ptr [rax+1],'S'
        .endif
        fprintf(ft, "%s\n", rbx)
    .endw
    fclose(ft)
    fclose(fp)
    remove(file)
    rename(&tmp, file)
    .return( 0 )
    endp
    end
