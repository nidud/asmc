ifdef _M_CEE_PURE
.err <comip.inc header cannot be included under /clr:safe or /clr:pure>
endif

ifndef _INC_COMIP
_INC_COMIP equ <>

include Ole2.inc
include comutil.inc
include malloc.inc
;include type_traits

_com_issue_error proto WINAPI :HRESULT

.template _com_IIID

    _IID LPIID ?

    .static GetInterfacePtr {
        xor eax,eax
        }
    .static GetInterface {
        .this.GetInterfacePtr()
        }
    .static GetIID {
        mov rax,this._IID
        }
    .ends

endif
