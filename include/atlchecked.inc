ifndef __ATLCHECKED_H__
__ATLCHECKED_H__ equ <>

include atldef.inc
include atlexcept.inc
include malloc.inc
include string.inc
include mbstring.inc
include wchar.inc
include tchar.inc
include stdlib.inc


.pragma pack(push,_ATL_PACKING)


AtlCrtErrorCheck proto :errno_t {
    .switch(ecx)
    .case ENOMEM
        AtlThrow(E_OUTOFMEMORY)
        .endc
    .case EINVAL
    .case ERANGE
        AtlThrow(E_INVALIDARG)
        .endc
    .case 0:
    .case STRUNCATE
        .endc
    .default
        AtlThrow(E_FAIL)
        .endc
    .endsw
    mov eax,ecx
}


ifdef _AFX
;ATLMFC_CRT_ERRORCHECK(expr) AFX_CRT_ERRORCHECK(expr)
else
;ATLMFC_CRT_ERRORCHECK(expr) ATL_CRT_ERRORCHECK(expr)
endif

.pragma pack(pop)

endif
