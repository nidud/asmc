ifndef __ATLCORE_H__
__ATLCORE_H__ equ <>

include atldef.inc
include windows.inc
include ole2.inc
ifdef _ATL_USE_WINAPI_FAMILY_PHONE_APP
include oleauto.inc
endif

include limits.inc
include tchar.inc
include mbstring.inc

include atlchecked.inc
include atlsimpcoll.inc
include atlwinverapi.inc

.pragma pack(push,_ATL_PACKING)

AtlStrLenW proto :ptr wchar_t {
    mov rax,rcx
    .if rax
        wcslen(rcx)
    .endif
    }
AtlStrLenA proto :ptr sbyte {
    mov rax,rcx
    .if rax
        strlen(rcx)
    .endif
    }
ifdef _UNICODE
AtlStrLen equ <AtlStrLenW>
else
AtlStrLen equ <AtlStrLenA>
endif

AtlIsValidStringW proto :LPCWSTR, :abs {
    xor     eax,eax
    cmp     rax,rcx
    setnz   al
    }
AtlIsValidStringA proto :LPCSTR, :abs {
    xor     eax,eax
    cmp     rax,rcx
    setnz   al
    }
ifdef _UNICODE
AtlIsValidString equ <AtlIsValidStringW>
else
AtlIsValidString equ <AtlIsValidStringA>
endif

AtlIsValidAddress proto :ptr, :abs, :abs {
    xor     eax,eax
    cmp     rax,rcx
    setnz   al
    }

AtlAssertValidObject proto :ptr T {
    .if rcx
        [rcx].AssertValid()
    .endif
    }

ifdef _DEBUG
ATLASSERT_VALID macro x
    exitm<AtlAssertValidObject(x)>
    endm
else
ATLASSERT_VALID macro x
    exitm<>
    endm
endif

.class CComCriticalSection

    m_sec CRITICAL_SECTION <>

    .inline CComCriticalSection {
        memset(this, 0, sizeof(CRITICAL_SECTION))
        }

    .inline _Acquires_lock_ {
        EnterCriticalSection(this)
        mov eax,S_OK
        }
    .inline _Releases_lock_ {
        LeaveCriticalSection(&m_sec)
        mov eax,S_OK
        }
    .inline Init {
       .new This:HRESULT
       .new hr:HRESULT
        mov hr,S_OK
        mov This,this
        .if (!_AtlInitializeCriticalSectionEx(this, 0, 0))
            GetLastError()
            mov hr,HRESULT_FROM_WIN32(eax)
        .endif
        mov eax,hr
        mov this,This
        }
    .inline Term {
        DeleteCriticalSection(this)
        mov eax,S_OK
        }

    .ENDS

.template CComAutoCriticalSection : public CComCriticalSection

    .inline CComAutoCriticalSection {
        CComCriticalSection::Init(this)
        .if (FAILED(eax))
            AtlThrow(eax)
        .endif
        }
    .inline Release {
        CComCriticalSection::Term(this)
        }
    .ENDS

.template CComSafeDeleteCriticalSection : public CComCriticalSection

    m_bInitialized BOOL ?

    .inline CComSafeDeleteCriticalSection {
        mov [rcx].CComSafeDeleteCriticalSection.m_bInitialized,FALSE
        }

    .inline Release {
        .if ([rcx].CComSafeDeleteCriticalSection.m_bInitialized)
            mov [rcx].CComSafeDeleteCriticalSection.m_bInitialized,FALSE
            CComCriticalSection::Term(rcx)
        .endif
        }

    .inline Init {
        CComCriticalSection::Init(this)
        .if (SUCCEEDED(eax))
            mov [this].CComSafeDeleteCriticalSection.m_bInitialized,TRUE
        .endif
        }

    .inline Term {
        .if [this].CComSafeDeleteCriticalSection.m_bInitialized
            mov [this].CComSafeDeleteCriticalSection.m_bInitialized,FALSE
            CComCriticalSection::Term(this)
        .endif
        }

    .inline _Acquires_lock_ {
        CComCriticalSection::_Lock(this)
        }
    .ENDS



.class CComAutoDeleteCriticalSection : public CComSafeDeleteCriticalSection
    .ENDS

.class CComFakeCriticalSection
    .inline _Lock {
        mov eax,S_OK
        }
    .inline Unlock {
        mov eax,S_OK
        }
    .inline Init {
        mov eax,S_OK
        }
    .inline Term {
        mov eax,S_OK
        }
    .ENDS

_ATL_BASE_MODULE70      struct
cbSize                  UINT ?
m_hInst                 HINSTANCE ?
m_hInstResource         HINSTANCE ?
dwAtlBuildVer           DWORD ?
pguidVer                LPGUID ?
m_csResource            PVOID ? ; CComCriticalSection
m_rgResourceInstance    HINSTANCE ?
_ATL_BASE_MODULE70      ends
_ATL_BASE_MODULE        typedef _ATL_BASE_MODULE70

.class CAtlBaseModule : public _ATL_BASE_MODULE

    m_bInitFailed BOOL ?

    CAtlBaseModule proc
    Release proc

    .inline GetModuleInstance {
        mov rax,m_hInst
        }
    .inline GetResourceInstance {
        mov rax,m_hInstResource
        }
    .inline SetResourceInstance :HINSTANCE {
        InterlockedExchangePointer(&m_hInstResource, _1)
        }

    AddResourceInstance proc :HINSTANCE
    RemoveResourceInstance proc :HINSTANCE
    GetHInstanceAt proc :int_t
    .ENDS

externdef _AtlBaseModule:CAtlBaseModule

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP

ATLSTRINGRESOURCEIMAGE struct
nLength             WORD ?
achString           WCHAR ?
ATLSTRINGRESOURCEIMAGE ends

_AtlGetStringResourceImage proto :HINSTANCE, :HRSRC, :UINT {
    int 3
}

AtlLoadString proto :UINT, :LPTSTR, :int_t {
    int 3
}

AtlFindResourceInstance proto :LPCTSTR, :LPCTSTR, :WORD {
    int 3
}

AtlFindStringResourceInstance proto :UINT, :WORD {
    int 3
}

endif

AtlSafeArrayGetActualVartype proto :ptr SAFEARRAY, :ptr VARTYPE {
    int 3
}

AtlCharNext proto :ptr {
    int 3
}

AtlstrchrT proto :ptr, :wchar_t {
    int 3
}

AtlprintfT proto :ptr, :vararg {
    int 3
}

AtlConvertSystemTimeToVariantTime proto :ptr SYSTEMTIME, :ptr {
    int 3
}

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP

AtlLoadSystemLibraryUsingFullPath proto :ptr WCHAR {
    int 3
if (_ATL_NTDDI_MIN > NTDDI_WIN7)
else
ifndef _USING_V110_SDK71_
endif
endif
}

endif

.pragma pack(pop)

endif
