include csmcmd.inc

    .code

    assume class:rbx

CFlagParam::Init proc argc:int_t, argv:ptr ptr wchar_t, rParamsProcessed:ptr int_t

    xor eax,eax
    mov [r9],eax
    mov rcx,[r8]
    mov al,[rcx]
    .if (edx && (al == '/' || al == '-' ))
        add rcx,2
        .if !_wcsicmp(rcx, m_szParamName)
            mov m_fExists,TRUE
            mov rcx,rParamsProcessed
            mov dword ptr [rcx],1
        .endif
    .endif
    .return ERROR_SUCCESS
    endp


CExclFlagParam::Init proc uses rsi rdi argc:int_t, argv:ptr wstring_t, rParamsProcessed:ptr int_t

  local iRes:int_t

    mov rdi,r9
    mov iRes,ERROR_SUCCESS
    xor eax,eax
    mov [rdi],eax
    mov rsi,[r8]
    mov al,[rsi]

    .if ( edx && (al == '/' || al == '-') )

        add rsi,2
        .ifd !_wcsicmp(rsi, m_szTrueParamName)
            .if ( !m_fExists )
                mov m_fExists,TRUE
                mov m_fFlag,TRUE
                mov dword ptr [rdi],1
            .else
                mov iRes,ERROR_INVALID_PARAMETER
            .endif
        .elseifd !_wcsicmp(rsi, m_szFalseParamName)
            .if ( !m_fExists )
                mov m_fExists,TRUE
                mov m_fFlag,FALSE
                mov dword ptr [rdi],1
            .else
                mov iRes,ERROR_INVALID_PARAMETER
            .endif
        .endif
    .endif
    .if ( iRes == ERROR_INVALID_PARAMETER )
        wcout << "/" << (m_szTrueParamName) << " and /"
        wcout << (m_szFalseParamName) << " parameters can't be used together!" << endl
    .endif
    .return iRes
    endp


CSetValueParam::Init proc uses rsi rdi argc:int_t, argv:ptr ptr wchar_t, rParamsProcessed:ptr int_t

  local iRes:int_t

    mov rdi,r9
    mov iRes,ERROR_SUCCESS
    xor eax,eax
    mov [rdi],eax
    mov rsi,[r8]
    mov al,[rsi]

    .if ( al == '/' || al == '-' )

        add rsi,2
        .if (!_wcsicmp(rsi, m_szParamName))

            .if (!m_fExists)

                mov m_fExists,TRUE
                mov rcx,argv
                mov rsi,[rcx+8]
                mov dl,[rsi]
                xor eax,eax

                .if ( argc > 1 && dl != '/' && dl != '-' )
                    ;; if it's not last word in command line
                    ;; and not followed by other parameter
                    ;; Parameter values starting with '/' and '-' are not supported
                    inc eax
                .endif
                .if eax
                    mov m_szValue,rsi
                    mov dword ptr [rdi],2
                .else
                    mov iRes,ERROR_INVALID_PARAMETER
                    wcout << "No valid value following parameter /" << (m_szParamName) << "!" << endl
                .endif
            .else
                mov iRes,ERROR_INVALID_PARAMETER
                wcout << "More than one instane of /" << (m_szParamName) << " were found in command line!" << endl
            .endif
        .endif
    .endif
    .return iRes
    endp


ParseParams proc uses rsi rdi rbx pParams:ptr ptr CParamBase, dwParamCnt:DWORD, argc:int_t, argv:ptr ptr WCHAR

  local i:int_t
  local iRes:int_t
  local cp:ptr CParamBase
  local p:PCWSTR

    mov rsi,r9
    mov iRes,ERROR_SUCCESS
    mov i,0

    .while (iRes == ERROR_SUCCESS && argc > i)
       .new iIncrement:int_t
        mov iIncrement,0
        .for (edi = 0: iRes == ERROR_SUCCESS && edi < dwParamCnt: edi++)
            mov rcx,pParams
            mov cp,[rcx+rdi*8]
            mov edx,argc
            sub edx,i
            imul r8d,i,8
            add r8,rsi
            mov iRes,cp.Init(edx, r8, &iIncrement)
            .if (iRes == ERROR_SUCCESS && iIncrement != 0)
                add i,iIncrement
                .break
            .endif
        .endf
        .if (iRes == ERROR_SUCCESS && iIncrement == 0)
            mov iRes,ERROR_INVALID_PARAMETER
            mov eax,i
            mov p,[rsi+rax*8]
            wcout << "Unknown parameter: " << p << endl
        .endif
    .endw
    .return iRes
    endp

    end
