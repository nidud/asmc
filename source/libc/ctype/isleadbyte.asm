; ISLEADBYTE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc
ifndef __UNIX__
include winnls.inc
include consoleapi.inc
endif

    .code

isleadbyte proc wc:int_t

    ldr     ecx,wc
    movzx   ecx,cl
    mov     rax,_pctype
    test    word ptr [rax+rcx*2],_LEADBYTE
    setnz   al
    movzx   eax,al
    ret

isleadbyte endp

ifndef __UNIX__

_initlead proc private

    .new cpInfo:CPINFOEX

     mov ecx,GetACP() ; GetConsoleCP()
    .if GetCPInfoEx(ecx, 0, &cpInfo)

        .if ( cpInfo.MaxCharSize > 1 )

            mov rdx,_pctype
            .for ( rcx = &cpInfo.LeadByte : byte ptr [rcx] && byte ptr [rcx+1] : rcx += 2 )

                .for ( eax = 0, al = [rcx] : al <= [rcx+1] : eax++ )
                    or word ptr [rdx+rax*2],_LEADBYTE
                .endf
            .endf
        .endif
    .endif
    ret

_initlead endp

.pragma(init(_initlead, 70))

endif

    end

