ifndef _WRL_COREWRAPPERS_H_
define _WRL_COREWRAPPERS_H_

include windows.inc
include intsafe.inc
include winstring.inc
include roapi.inc
ifdef BUILD_WINDOWS
include winrt.inc
endif

include wrl\def.inc
include wrl\internal.inc

.template RoInitializeWrapper fastcall

    _hr HRESULT ?

    .static RoInitializeWrapper flags:RO_INIT_TYPE {
        mov this._hr,RoInitialize(flags)
        }
    .static Release {
        .if (SUCCEEDED(this._hr))
            RoUninitialize()
        .endif
        }
    .static HRESULT {
        mov eax,this._hr
        }
    .ends

.template HString fastcall

    hstr_ HSTRING ?

    .static HString string:abs {
        if @InStr(1, string, <addr >)
            WindowsCreateString(string, lengthof(@SubStr(string, 5))-1, addr this.hstr_)
        else
            WindowsCreateString(string, wcslen(string), addr this.hstr_)
        endif
        }
    .static Release {
        WindowsDeleteString(this.hstr_)
        mov this.hstr_,NULL
        }
    .static GetRawBuffer length:abs=<NULL> {
        WindowsGetStringRawBuffer(this.hstr_, length)
        }


    .static Set s:ptr wchar_t, len:dword {
        this.Release()
        WindowsCreateString(s, len, &this.hstr_)
        }

    .static Attach hstr:HSTRING {
        mov rax,this.hstr_
        mov this.hstr_,hstr
        WindowsDeleteString(rax)
        }

    .static Detach {
        mov rax,this.hstr_
        mov this.hstr_,NULL
        }

    .static GetAddressOf {
        this.Release()
        mov rax,&this.hstr_
        }

    .static Get {
        mov rax,this.hstr_
        }

    .static IsValid {
        xor eax,eax
        cmp rax,this.hstr_
        setnz al
        }

    .static CopyTo s:ptr HSTRING {
        WindowsDuplicateString(this.hstr_, s)
        }

    .ends

.template HStringReference fastcall : public HString

    header_ HSTRING_HEADER <>

    .static HStringReference string:ptr wchar_t {

      local s,l
       .new s:ptr wchar_t = string
       .new l:int_t
        inc wcslen(string)
        mov l,eax
        WindowsCreateStringReference(wcscpy(alloca(addr [rax*2]), s), l, addr this.header_, addr this.hstr_)
        lea rax,this
        }

    .static CreateReference s:ptr wchar_t, bufferLen:abs, len:abs {

        mov eax,bufferLen
        mov ecx,len
        .if (ecx >= eax)
            mov ecx,eax
            dec ecx
        .endif
        WindowsCreateStringReference(s, ecx, addr this.header_, addr this.hstr_)
        .if (FAILED(eax))
        ;    RaiseException(eax)
        .endif
        }

    .static HStringReference_ s:ptr wchar_t, len:dword {
        mov eax,len
        inc eax
        this.CreateReference(s, eax, len)
        }

    .ends

endif
