ifndef __ATLEXCEPT_H__
__ATLEXCEPT_H__ equ <>

include atldef.inc
include atltrace.inc

.pragma pack(push,_ATL_PACKING)
if 0
_AtlRaiseException proto :abs, :abs=<EXCEPTION_NONCONTINUABLE> {
    RaiseException( this, _1, 0, NULL )
    }
endif
.template CAtlException

    m_hr HRESULT ?

    .operator CAtlException :abs=<E_FAIL> {
        mov [this].CAtlException.m_hr,_1
        }
    .ENDS

ifndef _ATL_NO_EXCEPTIONS

if defined( _ATL_CUSTOM_THROW )
ifdef _AFX
.err<MFC projects must use default implementation of AtlThrow()>
endif
else
AtlThrowImpl proto :HRESULT {

ifdef _AFX
    .if( ecx == E_OUTOFMEMORY )

        AfxThrowMemoryException()
    .else
        AfxThrowOleException( ecx )
    .endif
else
    CAtlException( ecx )
endif
}
endif

AtlThrowLastWin32 proto {
    GetLastError()
    AtlThrow( HRESULT_FROM_WIN32( eax ) )
}

else

ifndef _ATL_CUSTOM_THROW
AtlThrowImpl proto :HRESULT {
    .switch(ecx)

    .case E_OUTOFMEMORY:
        mov ecx,STATUS_NO_MEMORY
        .endc
    .default
        mov ecx,EXCEPTION_ILLEGAL_INSTRUCTION
    .endsw
    _AtlRaiseException(ecx)
}
endif
if 0
AtlThrowLastWin32 proto {
    GetLastError()
    AtlThrow( HRESULT_FROM_WIN32( eax ) )
}
endif

endif


.pragma pack(pop)

endif
