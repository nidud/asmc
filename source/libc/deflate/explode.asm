; EXPLODE.ASM--
;
; from explode.c -- by Mark Adler
;
; Change history:
; 2012-09-08 - Modified for DZ32
; 03/31/2010 - Removed 386 instructions
; ../../1997 - Modified for Doszip

include deflate.inc

define OSIZE 0x8000

.data

; Tables for length and distance for explode

cplen2 dw \
    2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
    18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
    35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,
    52,53,54,55,56,57,58,59,60,61,62,63,64,65

cplen3 dw \
    3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,
    19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
    36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,
    53,54,55,56,57,58,59,60,61,62,63,64,65,66

extra dw \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8

cpdist4 dw \
    1,65,129,193,257,321,385,449,513,577,641,705,
    769,833,897,961,1025,1089,1153,1217,1281,1345,1409,1473,
    1537,1601,1665,1729,1793,1857,1921,1985,2049,2113,2177,
    2241,2305,2369,2433,2497,2561,2625,2689,2753,2817,2881,
    2945,3009,3073,3137,3201,3265,3329,3393,3457,3521,3585,
    3649,3713,3777,3841,3905,3969,4033

cpdist8 dw \
    1,129,257,385,513,641,769,897,1025,1153,1281,
    1409,1537,1665,1793,1921,2049,2177,2305,2433,2561,2689,
    2817,2945,3073,3201,3329,3457,3585,3713,3841,3969,4097,
    4225,4353,4481,4609,4737,4865,4993,5121,5249,5377,5505,
    5633,5761,5889,6017,6145,6273,6401,6529,6657,6785,6913,
    7041,7169,7297,7425,7553,7681,7809,7937,8065

align size_t

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

;************** Explode an imploded compressed stream

; Get the bit lengths for a code representation from the compressed
; stream. If get_tree() returns 4, then there is an error in the data.
; Otherwise zero or -1 is returned.

get_tree proc __ccall uses rsi rbx l:ptr uint_t, n:uint_t

    ; get bit lengths

    .ifd ( fgetc(STDI) == -1 )

        .return( 4 )
    .endif
    lea ebx,[rax+1] ; length/count pairs to read
    xor esi,esi     ; next code

    .repeat

        .ifd ( fgetc(STDI) == -1 )

            .return( 4 )
        .endif

        mov ecx,eax
        and eax,0x0F
        mov edx,eax
        inc edx         ; bits in code (1..16)
        and ecx,0xF0
        shr ecx,4
        inc ecx         ; codes with those bits (1..16)

        lea eax,[rcx+rsi]
        .if ( eax > n ) ; don't overflow l[]

            .return( 4 )
        .endif
        mov rax,l
        .repeat
            mov [rax+rsi*4],edx
            inc esi
        .untilcxz
        dec ebx
    .untilz
    mov eax,ebx
    .if ( esi != n )
        mov eax,4
    .endif
    ret

get_tree endp


decode_huft proc __ccall uses rsi rdi htab:PHUFT, bits:int_t

    ldr rbx,htab
    ldr ecx,bits

    mov edi,1
    shl edi,cl
    dec edi

    needbits(ecx)

    .while 1

        not  eax
        and  eax,edi
        imul eax,eax,HUFT
        add  rbx,rax

        dumpbits([rbx].HUFT.b)
        movzx esi,[rbx].HUFT.e
        .if ( esi <= 16 )
            .return( 0 )
        .endif
        .if ( esi == 99 )
            .return( 1 )
        .endif
        sub esi,16
        mov edi,1
        mov ecx,esi
        shl edi,cl
        dec edi
        needbits(esi)
        mov rbx,[rbx].HUFT.t
    .endw
    ret

decode_huft endp


explode_docopy proc __ccall uses rsi rdi rbx tl:PHUFT, td:PHUFT, xbl:uint_t, xbd:uint_t, bdl:uint_t, s:ptr uint_t, u:ptr uint_t

   .new offs:int_t
   .new count:int_t

    mov edi,getbits(bdl)        ; get distance low bits

    .ifd decode_huft(td, xbd)   ; get coded distance high bits

        .return
    .endif

    movzx edx,[rbx].HUFT.n      ; construct offset
    mov rcx,STDO
    mov rax,[rcx].FILE._ptr
    sub rax,[rcx].FILE._base
    sub eax,edi
    sub eax,edx
    mov edi,eax

    .ifd decode_huft(tl, xbl)    ; get coded length

        .return
    .endif

    movzx esi,[rbx].HUFT.n      ; get length extra bits
    .if ( [rbx].HUFT.e )

        add esi,getbits(8)
    .endif

    mov rcx,s
    xor eax,eax
    mov edx,[rcx]
    mov [rcx],eax
    mov eax,esi
    .if ( edx > eax )

        sub edx,eax
        mov [rcx],edx
    .endif

    .while esi

        and edi,OSIZE-1
        mov rbx,STDO
        mov rdx,[rbx].FILE._ptr
        sub rdx,[rbx].FILE._base
        mov eax,edi
        .if ( eax <= edx )
            mov eax,edx
        .endif

        mov ecx,OSIZE
        sub ecx,eax
        .if ( ecx >= esi )
            mov ecx,esi
        .endif

        sub esi,ecx
        mov eax,edx
        add [rbx].FILE._ptr,rcx
        mov edx,[rbx].FILE._bufsiz
        sub edx,eax
        sub edx,ecx
        mov [rbx].FILE._cnt,edx
        mov count,esi
        mov esi,edi
        add edi,ecx
        add fsize,ecx
        mov offs,edi
        mov rbx,[rbx].FILE._base
        lea rdi,[rbx+rax]
        add rbx,rsi
        mov rdx,u

        .if ( uint_t ptr [rdx] && eax <= esi )

            xor eax,eax
            rep stosb
        .else
            mov rsi,rbx
            rep movsb
        .endif
        mov rbx,STDO
        mov rax,[rbx].FILE._ptr
        sub rax,[rbx].FILE._base
        .if ( eax >= OSIZE )

            mov uint_t ptr [rdx],0
            .ifd fflush(STDO)
                .return( ER_DISK )
            .endif
        .endif
        mov esi,count
        mov edi,offs
    .endw
    .return( 0 )

explode_docopy endp

; Decompress the imploded data using coded literals and a sliding
; window (of size 2^(6+bdl) bytes).

explode_lit proc __ccall uses rbx tb:PHUFT, tl:PHUFT, td:PHUFT, xbb:uint_t, xbl:uint_t, xbd:uint_t, bdl:uint_t, s:uint_t

   .new u:uint_t = 1 ; true if unflushed

    .while ( s ) ; do until ucsize bytes uncompressed

        .ifd getbits(1) ; then literal--decode it

            dec s
            .ifd decode_huft(tb, xbb)
                .return
            .endif
            movzx ecx,[rbx].HUFT.n
            .ifd oputc(ecx)
                .return
            .endif

            ; flush test?

        .elseifd explode_docopy(tl, td, xbl, xbd, bdl, &s, &u)

            .return
        .endif
    .endw
    .ifd fflush(STDO)
        mov eax,ER_DISK
    .endif
    ret

explode_lit endp

; Decompress the imploded data using uncoded literals and a sliding
; window (of size 2^(6+bdl) bytes).

explode_nolit proc __ccall tl:PHUFT, td:PHUFT, xbl:uint_t, xbd:uint_t, bdl:uint_t, s:uint_t

   .new u:uint_t = 1 ; true if unflushed

    .while ( s )

        .ifd getbits(1)

            dec s
            .ifd oputc(getbits(8))
               .return
            .endif

            ; flush test?

        .elseifd explode_docopy(tl, td, xbl, xbd, bdl, &s, &u)

            .return
        .endif
    .endw
    .ifd fflush(STDO)
        mov eax,ER_DISK
    .endif
    ret

explode_nolit endp


explode proc public uses rsi rdi rbx file:string_t, fp:ptr FILE, zp:PZIPLOCAL

   .new r:uint_t
   .new rc:int_t = 0
   .new td:PHUFT
   .new tl:PHUFT
   .new tb:PHUFT
   .new xbl:uint_t
   .new xbb:uint_t
   .new xbd:uint_t
   .new bdl:uint_t
   .new l[256]:uint_t

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

    mov eax,7
    mov xbl,eax
    .if ( [rbx].ZIPLOCAL.csize > 200000 )
        inc eax
    .endif
    mov xbd,eax

    .if ( [rbx].ZIPLOCAL.flag & 4 )

        mov xbb,9
        .ifd get_tree(&l, 256)

            mov rc,eax
            jmp done
        .endif

        .ifd huft_build( &l, 256, 256, 0, 0, &tb, &xbb )

            mov rc,eax
            .if ( eax == 1 )
                jmp freetb
            .endif
            jmp done
        .endif

        .ifd get_tree(&l, 64)

            mov rc,eax
            jmp freetb
        .endif
        lea rdx,cplen3

    .else

        mov tb,NULL
        .ifd get_tree(&l, 64)

           mov rc,eax
           jmp done
        .endif
        lea rdx,cplen2
    .endif

    .ifd huft_build( &l, 64, 0, rdx, &extra, &tl, &xbl )

        mov rc,eax
        .if ( eax == 1 )
            jmp freetl
        .endif
        jmp freetb
    .endif

    .ifd get_tree(&l, 64)

        mov rc,eax
        jmp freetl
    .endif

    mov bdl,6
    lea rdx,cpdist4
    .if ( [rbx].ZIPLOCAL.flag & 2 )

        lea rdx,cpdist8
        inc bdl
    .endif

    .ifd huft_build( &l, 64, 0, rdx, &extra, &td, &xbd )

        mov rc,eax
        .if ( eax == 1 )

            jmp freetd
        .endif
        jmp freetl
    .endif

    .if ( tb == NULL )
        mov rc,explode_nolit(tl, td, xbl, xbd, bdl, [rbx].ZIPLOCAL.fsize)
    .else
        mov rc,explode_lit(tb, tl, td, xbb, xbl, xbd, bdl, [rbx].ZIPLOCAL.fsize)
    .endif
freetd:
    huft_free( td )
freetl:
    huft_free( tl )
freetb:
    huft_free( tb )
done:
    .if ( rc == 0 )

        mov rcx,STDI
        .if ( [rcx].FILE._bitcnt >= 8 )

            inc [rcx].FILE._cnt
            dec [rcx].FILE._ptr
        .endif
        mov rcx,STDO
        mov eax,[rcx].FILE._crc32
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

explode endp

    end
