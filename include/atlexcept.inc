ifndef __ATLEXCEPT_H__
define __ATLEXCEPT_H__

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
    .inline CAtlException :abs=<E_FAIL> {
        mov [this].CAtlException.m_hr,_1
        }
    .ENDS

ifndef _ATL_NO_EXCEPTIONS

if defined( _ATL_CUSTOM_THROW )
ifdef _AFX
.err<MFC projects must use default implementation of AtlThrow()>
endif
else
AtlThrowImpl proto watcall :HRESULT {
ifdef _AFX
    .if( eax == E_OUTOFMEMORY )
        AfxThrowMemoryException()
    .else
        AfxThrowOleException(eax)
    .endif
else
    CAtlException(eax)
endif
    }
endif

AtlThrowLastWin32 proto fastcall {
    AtlThrow( HRESULT_FROM_WIN32R( GetLastError() ) )
    }

else

ifndef _ATL_CUSTOM_THROW
AtlThrowImpl proto watcall :HRESULT {
    .switch(eax)
    .case E_OUTOFMEMORY
        mov eax,STATUS_NO_MEMORY
        .endc
    .default
        mov eax,EXCEPTION_ILLEGAL_INSTRUCTION
    .endsw
    _AtlRaiseException(eax)
    }
endif
if 0
AtlThrowLastWin32 proto {
    AtlThrow( HRESULT_FROM_WIN32R( GetLastError() ) )
    }
endif

endif

.pragma pack(pop)

endif
