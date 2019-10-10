include string.inc
include errno.inc
include quadmath.inc
include asmc.inc
include expreval.inc

    .code

_atoow proc uses esi edi ebx dst:string_t, src:string_t, radix:int_t, bsize:int_t

    mov esi,src
    mov edx,dst
    mov ebx,radix
    mov edi,bsize

ifdef CHEXPREFIX
    movzx eax,word ptr [esi]
    or eax,0x2000
    .if eax == 'x0'
        add esi,2
        sub edi,2
    .endif
endif

    xor eax,eax
    mov [edx],eax
    mov [edx+4],eax
    mov [edx+8],eax
    mov [edx+12],eax

    .repeat

        .if ebx == 16 && edi <= 16

            ; hex value <= qword

            xor ecx,ecx

            .if edi <= 8

                ; 32-bit value

                .repeat
                    mov al,[esi]
                    add esi,1
                    and eax,not 0x30    ; 'a' (0x61) --> 'A' (0x41)
                    bt  eax,6           ; digit ?
                    sbb ebx,ebx         ; -1 : 0
                    and ebx,0x37        ; 10 = 0x41 - 0x37
                    sub eax,ebx
                    shl ecx,4
                    add ecx,eax
                    dec edi
                .untilz

                mov [edx],ecx
                mov eax,edx
                .break
            .endif

            ; 64-bit value

            xor edx,edx

            .repeat
                mov  al,[esi]
                add  esi,1
                and  eax,not 0x30
                bt   eax,6
                sbb  ebx,ebx
                and  ebx,0x37
                sub  eax,ebx
                shld edx,ecx,4
                shl  ecx,4
                add  ecx,eax
                adc  edx,0
                dec  edi
            .untilz

            mov eax,dst
            mov [eax],ecx
            mov [eax+4],edx
            .break

        .elseif ebx == 10 && edi <= 20

            xor ecx,ecx

            mov cl,[esi]
            add esi,1
            sub cl,'0'

            .if edi < 10

                .while 1

                    ; FFFFFFFF - 4294967295 = 10

                    dec edi
                    .break .ifz

                    mov al,[esi]
                    add esi,1
                    sub al,'0'
                    lea ebx,[ecx*8+eax]
                    lea ecx,[ecx*2+ebx]
                .endw

                mov [edx],ecx
                mov eax,edx
                .break

            .endif

            xor edx,edx

            .while 1

                ; FFFFFFFFFFFFFFFF - 18446744073709551615 = 20

                dec edi
                .break .ifz

                mov  al,[esi]
                add  esi,1
                sub  al,'0'
                mov  ebx,edx
                mov  bsize,ecx
                shld edx,ecx,3
                shl  ecx,3
                add  ecx,bsize
                adc  edx,ebx
                add  ecx,bsize
                adc  edx,ebx
                add  ecx,eax
                adc  edx,0
            .endw

            mov eax,dst
            mov [eax],ecx
            mov [eax+4],edx

        .else

            mov bsize,edi
            mov edi,edx
            .repeat
                mov al,[esi]
                and eax,not 0x30
                bt  eax,6
                sbb ecx,ecx
                and ecx,0x37
                sub eax,ecx
                mov ecx,8
                .repeat
                    movzx edx,word ptr [edi]
                    imul  edx,ebx
                    add   eax,edx
                    mov   [edi],ax
                    add   edi,2
                    shr   eax,16
                .untilcxz
                sub edi,16
                add esi,1
                dec bsize
            .untilz
            mov eax,dst
        .endif
    .until 1
    ret

_atoow endp

atofloat proc _out:ptr, inp:string_t, size:uint_t, negative:int_t, ftype:uchar_t

    ;; v2.04: accept and handle 'real number designator'

    .if ( ftype )

        ;; convert hex string with float "designator" to float.
        ;; this is supposed to work with real4, real8 and real10.
        ;; v2.11: use _atoow() for conversion ( this function
        ;;    always initializes and reads a 16-byte number ).
        ;;    then check that the number fits in the variable.
        ;;
        _atoow( _out, inp, 16, &[strlen(inp)-1] )

        .for ( ecx = _out,
               edx = ecx,
               ecx += size,
               edx += 16: ecx < edx: ecx++ )

            .if ( byte ptr [ecx] != 0 )

                asmerr( 2104, inp )
                .break
            .endif
        .endf
    .else

        mov errno,0
        __cvta_q(_out, inp, NULL)
        .if ( errno )
            asmerr( 2104, inp )
        .endif
        .if( negative )
            mov ecx,_out
            or  byte ptr [ecx+15],0x80
        .endif

        .switch ( size )
        .case 2
            __cvtq_h(_out, _out)
            .if ( errno )
                asmerr( 2071 )
            .endif
            .endc
        .case 4
            __cvtq_ss(_out, _out)
            .if ( errno )
                asmerr( 2071 )
            .endif
            .endc
        .case 8
            __cvtq_sd(_out, _out)
            .if ( errno )
                asmerr( 2071 )
            .endif
            .endc
        .case 10
            __cvtq_ld(_out, _out)
        .case 16
            .endc
        .default
            ;; sizes != 4,8,10 or 16 aren't accepted.
            ;; Masm ignores silently, JWasm also unless -W4 is set.
            ;;
            .if ( Parse_Pass == PASS_1 )
                asmerr( 7004 )
            .endif
            memset( _out, 0, size )
        .endsw
    .endif
    ret

atofloat endp

    assume ebx:expr_t

quad_resize proc uses ebx opnd:expr_t, size:uint_t

    mov errno,0
    mov ebx,opnd
    mov eax,size

    .switch eax
    .case 10
        __cvtq_ld(ebx, ebx)
        .endc
    .case 8
        .if ( [ebx].chararray[15] & 0x80 )
            or  [ebx].flags,E_NEGATIVE
            and [ebx].chararray[15],0x7F
        .endif
        __cvtq_sd(ebx, ebx)
        .if ( [ebx].flags & E_NEGATIVE )
            or [ebx].chararray[7],0x80
        .endif
        mov [ebx].mem_type,MT_REAL8
        .endc
    .case 4
        .if ( [ebx].chararray[15] & 0x80 )
            or  [ebx].flags,E_NEGATIVE
            and [ebx].chararray[15],0x7F
        .endif
        __cvtq_ss(ebx, ebx)
        .if ( [ebx].flags & E_NEGATIVE )
            or [ebx].chararray[3],0x80
        .endif
        mov [ebx].mem_type,MT_REAL4
        .endc
    .case 2
        .if ( [ebx].chararray[15] & 0x80 )
            or  [ebx].flags,E_NEGATIVE
            and [ebx].chararray[15],0x7F
        .endif
        __cvtq_h(ebx, ebx)
        .if ( [ebx].flags & E_NEGATIVE )
            or [ebx].chararray[1],0x80
        .endif
        mov [ebx].mem_type,MT_REAL2
        .endc
    .endsw

    .if ( errno )
        asmerr( 2071 )
    .endif
    ret

quad_resize endp

    end
