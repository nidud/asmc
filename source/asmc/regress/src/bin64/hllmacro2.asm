
; v2.31 delayed expansion of macro error

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

_HRESULT_TYPEDEF_ macro val
    exitm<val>
    endm

E_OUTOFMEMORY EQU _HRESULT_TYPEDEF_ ( 8007000Eh )

    .code

    .if edx
	nop
    .elseif eax == E_OUTOFMEMORY
	nop
    .endif

    .while eax == E_OUTOFMEMORY
	nop
    .endw

    end

