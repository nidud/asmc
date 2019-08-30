include string.inc
include errno.inc
include quadmath.inc
include asmc.inc

    .code

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

    end
