; INFLATE.ASM--
;
; from inflate.c -- by Mark Adler
;
; Change history:
; 2012-09-08 - Modified for DZ32
; 03/31/2010 - Removed 386 instructions
; ../../1997 - Modified for Doszip

include deflate.inc

define OSIZE 0x8000
define lbits 9
define dbits 6

.data

; Tables for deflate from PKZIP's appnote.txt

border dd \
    16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15

cplens dw \
     3, 4, 5, 6, 7, 8, 9,10, 11, 13, 15, 17, 19, 23, 27, 31,
     35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0

cplext dw \ ; Extra bits for literal codes 257..285
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 99, 99 ; 99==invalid

cpdist dw \ ; Copy offsets for distance codes 0..29
    1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
    257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145,
    8193, 12289, 16385, 24577

cpdext dw \ ; Extra bits for distance codes
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
    7, 7, 8, 8, 9, 9, 10, 10, 11, 11,
    12, 12, 13, 13

align size_t

fixedtd PHUFT 0
fixedtl PHUFT 0
STDO    LPFILE 0
STDI    LPFILE 0
fsize   uint_t 0

    .code

    option proc:private, dotname

ifdef _LIN64
needbits proc __ccall uses rsi rdi count:int_t
else
needbits proc __ccall count:int_t
endif
    ldr edx,count

    .if ( _fneedb(STDI, edx) == -1 )
        xor eax,eax
    .endif
    ret

needbits endp

dumpbits proto fastcall :dword {
    mov rdx,STDI
    sub [rdx].FILE._bitcnt,ecx   ; dec bit count
    shr [rdx].FILE._charbuf,cl   ; dump used bits
    }

ifdef _LIN64
getbits proc __ccall uses rsi rdi count:int_t
else
getbits proc __ccall count:int_t
endif
    ldr edx,count

    .ifd ( _fgetb(STDI, ecx) == -1 )
        xor eax,eax
    .endif
    ret

getbits endp

ifdef _LIN64
oputc proc __ccall uses rsi rdi c:int_t
else
oputc proc __ccall c:int_t
endif
    ldr ecx,c

    inc fsize
    .ifd ( fputc(ecx, STDO) == -1 )

        .return( ER_DISK )
    .endif
    xor eax,eax
    ret

oputc endp

;************** Decompress the codes in a compressed block

inflate_codes proc __ccall uses rsi rdi rbx tl:PHUFT, td:PHUFT, l:SINT, d:SINT

    .while 1 ; do until end of block

        mov rbx,tl
        needbits(l)

        imul  eax,eax,HUFT
        add   rbx,rax
        movzx esi,[rbx].HUFT.e

        .if ( esi > 16 )

            .repeat

                .if ( esi == 99 )

                   .return( 1 )
                .endif

                dumpbits([rbx].HUFT.b)
                sub esi,16
                needbits(esi)

                mov   rbx,[rbx].HUFT.t
                imul  eax,eax,HUFT
                add   rbx,rax
                movzx esi,[rbx].HUFT.e
            .until esi <= 16
        .endif

        dumpbits([rbx].HUFT.b)

        .if ( esi == 16 ) ; then it's a literal

            movzx ecx,[rbx].HUFT.n
            .ifd oputc(ecx)
                .return
            .endif

        .else ; it's an EOB or a length

            .if ( esi == 15 ) ; exit if end of block

                .return( 0 )
            .endif

            ; get length of block to copy

            movzx edi,[rbx].HUFT.n
            add edi,getbits(esi)

            ; decode distance of block to copy

            needbits(d)

            mov   rbx,td
            imul  eax,eax,HUFT
            add   rbx,rax
            movzx esi,[rbx].HUFT.e

            .if ( esi > 16 )

                .repeat

                    .if ( esi == 99 )

                       .return( 1 )
                    .endif

                    dumpbits([rbx].HUFT.b)
                    sub esi,16
                    needbits(esi)

                    mov   rbx,[rbx].HUFT.t
                    imul  eax,eax,HUFT
                    add   rbx,rax
                    movzx esi,[rbx].HUFT.e
                .until esi <= 16
            .endif
            dumpbits([rbx].HUFT.b)

            movzx ebx,[rbx].HUFT.n
            mov edx,getbits(esi)

            mov rcx,STDO
            mov rax,[rcx].FILE._ptr
            sub rax,[rcx].FILE._base
            sub eax,ebx
            sub eax,edx
            mov ebx,eax

            .repeat

                mov rsi,STDO
                mov rdx,[rsi].FILE._ptr
                sub rdx,[rsi].FILE._base
                and ebx,OSIZE-1
                mov ecx,OSIZE
                mov eax,ebx
                .if ( eax <= edx )
                    mov eax,edx
                .endif
                sub ecx,eax
                .if ( ecx > edi )
                    mov ecx,edi
                .endif

                sub edi,ecx
                mov eax,edx
                add [rsi].FILE._ptr,rcx
                mov edx,[rsi].FILE._bufsiz
                sub edx,eax
                sub edx,ecx
                mov [rsi].FILE._cnt,edx
                mov edx,edi
                mov rsi,[rsi].FILE._base
                lea rdi,[rsi+rax]
                add rsi,rbx
                add ebx,ecx
                add eax,ecx
                add fsize,ecx
                rep movsb
                mov edi,edx

                .if ( eax >= OSIZE )
ifdef _LIN64
                    .new count:uint_t = edi
endif
                    fflush( STDO )
ifdef _LIN64
                    mov edi,count
endif
                    .if ( eax )
                        .return( ER_DISK )
                    .endif
                .endif
            .until !edi
        .endif
    .endw
    ret

inflate_codes endp

;************** Decompress an inflated type 1 (fixed Huffman codes) block

inflate_fixed proc uses rdi rbx

   .new fixed_bd:DWORD = 0
   .new fixed_bl:DWORD = 0
   .new ll[288]:DWORD   ; length list for huft_build

    lea rdi,ll
    xor eax,eax
    .if ( rax == fixedtl )

        mov rbx,rdi
        mov ecx,144         ; literal table
        mov eax,8
        rep stosd
        mov ecx,112
        mov eax,9
        rep stosd
        mov ecx,24
        mov eax,7
        rep stosd           ; make a complete, but wrong code set
        mov ecx,8
        mov eax,8
        rep stosd

        mov rdi,rbx
        mov fixed_bl,7
        .ifd huft_build( rdi, 288, 257, &cplens, &cplext, &fixedtl, &fixed_bl )

            mov fixedtl,NULL
           .return
        .endif

        mov rdx,rdi         ; make an incomplete code set
        mov ecx,30
        mov eax,5
        rep stosd
        mov fixed_bd,5
        mov rdi,rdx
        .ifd huft_build( rdi, 30, 0, &cpdist, &cpdext, &fixedtd, &fixed_bd )

            .if ( eax != 1 )

                mov ebx,eax
                huft_free( fixedtl )
                mov fixedtl,NULL
                mov eax,ebx
               .return
            .endif
        .endif
    .endif
    ;
    ; decompress until an end-of-block code
    ;
    .ifd inflate_codes( fixedtl, fixedtd, fixed_bl, fixed_bd )

        mov eax,1
    .endif
    ret

inflate_fixed endp

;************** Decompress an inflated type 2 (dynamic Huffman codes) block

inflate_dynamic proc uses rsi rdi rbx

  local nd:dword,       ; number of distance codes
        nl:dword,       ; number of literal/length codes
        nb:dword,       ; number of bit length codes
        tl:PHUFT,       ; literal/length code table
        td:PHUFT,       ; distance code table
        l:dword,        ; lookup bits for tl (bl)
        d:dword,        ; lookup bits for td (bd)
        n:dword,        ; number of lengths to get
        ll[320]:DWORD   ; literal/length and distance code lengths

    getbits(5)
    add eax,257
    mov nl,eax          ; number of literal/length codes
    getbits(5)
    inc eax
    mov nd,eax          ; number of distance codes
    getbits(4)
    add eax,4
    mov nb,eax          ; number of bit length codes

    .if ( nl > 288 || nd > 32 )    ; PKZIP_BUG_WORKAROUND
        .return( 1 )
    .endif

    lea rbx,border
    .for ( esi = 0 : esi < nb : esi++ )

        getbits(3)
        mov edx,[rbx+rsi*4]
        mov ll[rdx*4],eax
    .endf

    .for ( : esi < 19 : esi++ )

        mov eax,[rbx+rsi*4]
        mov ll[rax*4],0
    .endf

    ; build decoding table for trees--single level, 7 bit lookup

    mov l,7
    .ifd huft_build( &ll, 19, 19, NULL, NULL, &tl, &l )

        mov esi,eax
        .if ( eax == 1 )
            huft_free(tl)
        .endif
        .return( esi ) ; incomplete code set
    .endif

    mov eax,nl
    add eax,nd
    mov n,eax

    .for ( edi = 0, esi = 0 : esi < n : )

        needbits(l)

        mov     rbx,tl
        imul    eax,eax,HUFT
        add     rbx,rax
        mov     td,rbx

        dumpbits([rbx].HUFT.b)
        movzx eax,[rbx].HUFT.n
        .if ( eax < 16 )

            mov edi,eax
            mov ll[rsi*4],eax
            inc esi
            xor edx,edx

        .elseif ( eax == 16 )

            getbits(2)
            add eax,3
            mov edx,eax
            add eax,esi
            .if ( eax > n )
                .return( 1 )
            .endif

        .else

            .if ( eax == 17 )

                getbits(3)
                add eax,3
            .else
                getbits(7)
                add eax,11
            .endif
            mov edx,eax
            add eax,esi
            .if ( eax > n )
                .return( 1 )
            .endif
            xor edi,edi
        .endif

        .if edx
            .repeat
                mov ll[rsi*4],edi
                inc esi
                dec edx
            .untilz
        .endif
    .endf

    ; free decoding table for trees

    huft_free( tl )


    mov l,lbits
    huft_build( &ll, nl, 257, &cplens, &cplext, &tl, &l )

    .if ( l == 0 || eax == 1 )

        huft_free( tl )
       .return( 1 )
    .endif
    .if ( eax )
        .return
    .endif

    mov d,dbits
    mov eax,nl
    lea rcx,ll[rax*4]
    huft_build( rcx, nd, 0, &cpdist, &cpdext, &td, &d )

    .if ( l == 0 && nl <= 257 )

        huft_free( tl )
       .return( 1 )
    .endif
    .if ( eax == 1 )
        xor eax,eax
    .endif
    .if ( eax )

        mov ebx,eax
        huft_free( tl )
       .return( ebx )
    .endif

    mov ebx,inflate_codes( tl, td, l, d )
    huft_free( td )
    huft_free( tl )

    mov eax,ebx
    .if ( eax )
        mov eax,1
    .endif
    ret

inflate_dynamic endp


;****** Decompress an inflated type 0 (stored) block.

inflate_stored proc uses rbx

    mov rcx,STDI        ; go to byte boundary
    and [rcx].FILE._bitcnt,7
    getbits([rcx].FILE._bitcnt)

    mov ebx,getbits(16) ; number of bytes in block
    getbits(16)
    not ax
    .if ( eax != ebx )

        .return( 1 )
    .endif
    .if ( eax == 0 )

        .return
    .endif
    .for ( : ebx : ebx-- ) ; read and output the compressed data

        .ifd oputc(getbits(8))
            .return
        .endif
    .endf
    .return( 0 )

inflate_stored endp


inflate proc public uses rbx file:string_t, fp:ptr FILE, zp:PZIPLOCAL

   .new rc:int_t = 0
   .new state:int_t

    ldr rax,fp
    ldr rbx,zp

    mov [rax].FILE._bitcnt,0
    mov [rax].FILE._charbuf,0
    mov STDI,rax

    .if ( fopen(ldr(file), "wz") == NULL )

        dec rax
       .return
    .endif
    mov STDO,rax
    mov fsize,0

    .if ( rbx && [rbx].ZIPLOCAL.method == 0 )

        .for ( : fsize < [rbx].ZIPLOCAL.fsize : fsize++ )

            .ifd ( fgetc(STDI) == -1 )

                mov rc,ER_ZIP
               .break
            .endif
            .ifd ( fputc(eax, STDO) == -1 )

                mov rc,ER_DISK
               .break
            .endif
        .endf
        .if ( rc == 0 )
            .ifd fflush(STDO)
                mov eax,ER_DISK
            .endif
        .endif
    .else

        .repeat

            mov state,getbits(1)
            .switch getbits(2)
            .case 0
                inflate_stored()
               .endc
            .case 1
                inflate_fixed()
               .endc
            .case 2
                inflate_dynamic()
               .endc
            .default
                mov eax,ER_ZIP
            .endsw
            .if ( eax == 0 )

                .continue( 0 ) .if ( state == 0 )
                .ifd fflush(STDO)
                    mov eax,ER_DISK
                .endif
            .endif
            mov rc,eax

            xor eax,eax
            .if ( rax != fixedtl )

                huft_free( fixedtd )
                huft_free( fixedtl )
                xor eax,eax
                mov fixedtd,rax
                mov fixedtl,rax
            .endif
        .until 1
    .endif

    .if ( rbx && rc == 0 )

        mov rax,STDO
        mov eax,[rax].FILE._crc32
        not eax
        .if ( eax != [rbx].ZIPLOCAL.crc )
            mov rc,ER_CRCERR
        .elseif ( fsize != [rbx].ZIPLOCAL.fsize )
            mov rc,ER_ZIP
        .endif
    .endif
    fclose(STDO)
    mov eax,rc
    ret

inflate endp

    end
