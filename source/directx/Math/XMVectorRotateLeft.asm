
include DirectXMath.inc

    .code

    option win64:nosave

XMVectorRotateLeft proc XM_CALLCONV V:FXMVECTOR, Elements:uint32_t

    .assert( edx < 4 )

    lea r8d,[rdx+1]
    lea r9d,[rdx+2]
    lea eax,[rdx+3]
;    and edx,3
    and r8d,3
    and r9d,3
    and eax,3

    XMVectorSwizzle(xmm0, edx, r8d, r9d, eax)
    ret

XMVectorRotateLeft endp

    end
