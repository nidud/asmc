;
; delayed expansion of macro .elseif
;
    .386
    .model flat

M1 macro reg
add reg,1
exitm<reg>
endm

    .code

    .if ( ( byte ptr [ecx] & 1 ) && ( eax == 2 || ( edx & 3 ) ) )
	nop
    .elseif ( ( byte ptr [ecx] & 2 ) && ( eax == 1 || M1(ebx) == 2 ) )
	nop
    .endif

    end

