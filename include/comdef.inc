ifndef _INC_COMDEF
define _INC_COMDEF

ifdef WINAPI_FAMILY
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif
if not WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
define _COMDEF_NOT_WINAPI_FAMILY_DESKTOP_APP
endif
if defined(WINAPI_FAMILY_PHONE_APP) and WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_PHONE_APP)
define _COMDEF_WINAPI_FAMILY_PHONE_APP
endif
endif

ifndef _COMDEF_WINAPI_FAMILY_PHONE_APP
include Ole2.inc

include comutil.inc
endif

ifdef _COMDEF_NOT_WINAPI_FAMILY_DESKTOP_APP

include roerrorapi.inc
include new.inc
include wchar.inc

else

include OleCtl.inc

.pragma comment(lib, user32)
.pragma comment(lib, ole32)
.pragma comment(lib, oleaut32)

ifdef _NATIVE_WCHAR_T_DEFINED
if defined(_GUARDED_CRT)
 ifdef _DEBUG
  .pragma comment(lib, comsuppwgd)
 else
  .pragma comment(lib, comsuppwg)
 endif
else
 ifdef _DEBUG
  .pragma comment(lib, comsuppwd)
 else
  .pragma comment(lib, comsuppw)
 endif
endif
else
if defined(_GUARDED_CRT)
 ifdef _DEBUG
  .pragma comment(lib, comsuppgd)
 else
  .pragma comment(lib, comsuppg)
 endif
else
 ifdef _DEBUG
  .pragma comment(lib, comsuppd)
 else
  .pragma comment(lib, comsupp)
 endif
endif
endif

_com_raise_error proto :HRESULT, :ptr IErrorInfo
_set_com_error_handler proto :ptr
_com_issue_error proto :HRESULT
_com_issue_errorex proto :HRESULT, :ptr IUnknown, :REFIID

_com_dispatch_propget proto :ptr IDispatch, :DISPID, :VARTYPE, :ptr
_com_dispatch_propput proto :ptr IDispatch, :DISPID, :VARTYPE, :vararg
_com_dispatch_method proto :ptr IDispatch, :DISPID, :WORD, :VARTYPE, :ptr, :ptr wchar_t, :vararg

_com_dispatch_raw_propget proto :ptr IDispatch, :DISPID, :VARTYPE, :ptr
_com_dispatch_raw_propput proto :ptr IDispatch, :DISPID, :VARTYPE, :vararg
_com_dispatch_raw_method proto :ptr IDispatch, :DISPID, :WORD, :VARTYPE, :ptr, :ptr wchar_t, :vararg

.enum {
    WCODE_HRESULT_FIRST = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200),
    WCODE_HRESULT_LAST = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF+1, 0) - 1
    }

.class _com_error

    LPIErrorInfo typedef ptr IErrorInfo

    m_hresult HRESULT ?
    m_perrinfo LPIErrorInfo ?
    m_pszMsg LPTSTR ?

    .static _com_error hr:HRESULT, perrinfo:ptr IErrorInfo, fAddRef:BOOL {
        mov this.m_hresult,hr
        mov this.m_perrinfo,perrinfo
        mov this.m_pszMsg,NULL
        .if (this.m_perrinfo != NULL && fAddRef)
            this.m_perrinfo.AddRef()
        .endif
        }

    .static copy that:ptr _com_error {
        mov this.m_hresult,[rcx]._com_error.m_hresult
        mov this.m_perrinfo,[rcx]._com_error.m_perrinfo
        mov this.m_pszMsg,NULL
        .if (this.m_perrinfo != NULL)
            this.m_perrinfo.AddRef()
        .endif
        }

    ;; Destructor

    .static Release {
        .if this.m_perrinfo != NULL
            this.m_perrinfo.Release()
        .endif
        .if this.m_pszMsg != NULL
            LocalFree(this.m_pszMsg)
        .endif
        }

    ;; Accessors

    .static Error {
        mov eax,this.m_hresult
        }

    .static WCode {
        this.HRESULTToWCode(this.m_hresult)
        }
    .static ErrorInfo {
        .if this.m_perrinfo != NULL
            this.m_perrinfo.AddRef()
        .endif
        mov rax,this.m_perrinfo
        }

    ;; IErrorInfo method accessors

    .static Description {
        .new bstr:BSTR = NULL
        .if m_perrinfo != NULL
            this.m_perrinfo.GetDescription(&bstr)
            .if (FAILED(eax))
                mov bstr,NULL
            .endif
        .endif
        _bstr_t(bstr, FALSE)
        }
    .static HelpContext {
        .new dwHelpContext:DWORD = 0
        .if (this.m_perrinfo != NULL)
            this.m_perrinfo.GetHelpContext(&dwHelpContext)
            .if (FAILED(eax))
                mov dwHelpContext,0
            .endif
        .endif
        mov eax,dwHelpContext
        }
    .static HelpFile {
        .new bstr:BSTR = NULL
        .if this.m_perrinfo != NULL
            this.m_perrinfo.GetHelpFile(&bstr)
            .if FAILED(eax)
                mov bstr,NULL
            .endif
        .endif
        _bstr_t(bstr, FALSE)
        }
    .static Source {
        .new bstr:BSTR = NULL
        .if this.m_perrinfo != NULL
            this.m_perrinfo.GetSource(&bstr)
            .if FAILED(eax)
                mov bstr,NULL
            .endif
        .endif
        _bstr_t(bstr, FALSE)
        }
    .static Guid {
        .new guid:GUID
        .if this.m_perrinfo != NULL
            this.m_perrinfo.GetGUID(&guid)
        .endif
        lea rax,guid
        }

    ;; FormatMessage accessors

    .static ErrorMessage {
        .if this.m_pszMsg == NULL
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER or FORMAT_MESSAGE_FROM_SYSTEM or FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                this.m_hresult,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                &this.m_pszMsg,
                0,
                NULL)
        .endif
        mov rcx,this.m_pszMsg
        .if rcx
          ifdef _UNICODE
            add rax,wcslen(rcx)
          else
            strlen(rcx)
          endif
            mov rcx,this.m_pszMsg
            .if rax > 1 && tchar_t ptr [rcx+rax - 1*tchar_t] == '\n'
                mov tchar_t ptr [rcx+rax - 1*tchar_t],0
                .if tchar_t ptr [rcx+rax - 2*tchar_t] == '\r'
                    mov tchar_t ptr [rcx+rax - 2*tchar_t],0
                .endif
            .endif
        .else
            mov this.m_pszMsg,LocalAlloc(0, 32 * sizeof(tchar_t))
            .if rax
                .new wCode:WORD = this.WCode()
                .if wCode != 0
                    _COM_PRINTF_S_1(this.m_pszMsg, 32, "IDispatch error #%d", wCode)
                .else
                    _COM_PRINTF_S_1(this.m_pszMsg, 32, "Unknown error 0x%0lX", this.m_hresult)
                .endif
            .endif
        .endif
        mov rax,this.m_pszMsg
        }

    ;; EXCEPINFO.wCode <-> HRESULT mappers

    .static WCodeToHRESULT wCode:WORD {
        .if wCode >= 0xFE00
            mov eax,WCODE_HRESULT_LAST
        .else
            mov eax,WCODE_HRESULT_FIRST
            add eax,wCode
        .endif
        }
    .static HRESULTToWCode hr:HRESULT {
        mov eax,0
        .if hr >= WCODE_HRESULT_FIRST && hr <= WCODE_HRESULT_LAST
            sub hr,WCODE_HRESULT_FIRST
            mov eax,hr
        .endif
        }
    .ends

__missing_type__ typedef int_t

ifndef _COM_SMARTPTR
 ifndef _INC_COMIP
  include comip.inc
 endif
 _COM_SMARTPTR        equ <_com_ptr_t>
 _COM_SMARTPTR_LEVEL2 equ <_com_IIID>
endif

ifndef _COM_NO_STANDARD_GUIDS_
ifdef __IFontDisp_INTERFACE_DEFINED__
; Font, IDispatch
endif
ifdef __IFontEventsDisp_INTERFACE_DEFINED__
; FontEvents : IFontEventsDisp, IDispatch
endif
ifdef __IPictureDisp_INTERFACE_DEFINED__
; Picture : IPictureDisp, IDispatch
endif
include comdefsp.inc
endif ;; _COM_NO_STANDARD_GUIDS_

endif ;; _COMDEF_NOT_WINAPI_FAMILY_DESKTOP_APP
endif ;; _INC_COMDEF
