
; Implementation of utility functions

PrintErrorIfFailed proto functionName:PCWSTR, errorCode:HRESULT {

    .if (FAILED(errorCode))

        wprintf("Function %s failed with error code 0x%x\n", functionName, errorCode)
    .endif
    }

PrintEnumString proto :ptr IEnumString, :PCWSTR {

    .new enumString:ptr IEnumString = _1
    .new prefixText:PCWSTR = _2
    .new hr:HRESULT = S_OK
    .while ( hr == S_OK )

       .new string:LPOLESTR = nullptr
        mov hr,enumString.Next(1, &string, nullptr)

        .if ( hr == S_OK )

            .if ( prefixText == nullptr )

                wprintf("%s\n", string)

            .else

                wprintf("%s %s\n", prefixText, string)
            .endif
            CoTaskMemFree(string)
        .endif
    .endw

    PrintErrorIfFailed("ListAvailableLanguages", hr)
    mov eax,hr
    .if (SUCCEEDED(eax))
        mov eax,S_OK
    .endif
    }

HasSingleString proto enumString:ptr IEnumString, value:ptr bool {

    .new penumString:ptr IEnumString = enumString
    .new pvalue:ptr bool = value
    .new strings[2]:LPOLESTR = {0}
    .new count:ULONG = 0
    .new hr:HRESULT = penumString.Next(2, &strings, &count)
    .if (SUCCEEDED(hr))

        .new i:ULONG = 0
        .for ( : i < count: ++i )

            mov eax,i
            CoTaskMemFree(strings[rax*size_t])
        .endf
        mov rcx,pvalue
        xor eax,eax
        .if ( count == 1 )
            inc eax
        .endif
        mov [rcx],eax
        mov hr,penumString.Reset()
    .endif

    PrintErrorIfFailed("HasSingleString", hr)
    mov eax,hr
    .if (SUCCEEDED(eax))
        mov eax,S_OK
    .endif
    }
