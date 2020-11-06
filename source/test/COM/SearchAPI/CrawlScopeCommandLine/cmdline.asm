include csmcmd.inc

    .code

CFlagParam::Init proc argc:int_t, argv:ptr ptr wchar_t, rParamsProcessed:ptr int_t

    xor eax,eax
    mov [r9],eax
    mov rcx,[r8]
    mov al,[rcx]

    .if (edx && (al == '/' || al == '-' ))

        add rcx,2
        mov rdx,this
        .if !_wcsicmp(rcx, [rdx].CFlagParam.m_szParamName)

            mov rdx,this
            mov [rdx].CFlagParam.m_fExists,TRUE

            mov rcx,rParamsProcessed
            mov dword ptr [rcx],1
        .endif
    .endif

    .return ERROR_SUCCESS

CFlagParam::Init endp


    assume rbx:ptr CExclFlagParam

CExclFlagParam::Init proc uses rsi rdi rbx argc:int_t, argv:ptr ptr wchar_t, rParamsProcessed:ptr int_t

  local iRes:int_t

    mov rbx,rcx
    mov rdi,r9
    mov iRes,ERROR_SUCCESS
    xor eax,eax
    mov [rdi],eax
    mov rsi,[r8]
    mov al,[rsi]

    .if (edx && (al == '/' || al == '-'))

        add rsi,2
        .if (!_wcsicmp(rsi, [rbx].m_szTrueParamName))

            .if (![rbx].m_fExists)

                mov [rbx].m_fExists,TRUE
                mov [rbx].m_fFlag,TRUE
                mov dword ptr [rdi],1

            .else

                mov iRes,ERROR_INVALID_PARAMETER
            .endif

        .elseif (!_wcsicmp(rsi, [rbx].m_szFalseParamName))

            .if (![rbx].m_fExists)

                mov [rbx].m_fExists,TRUE
                mov [rbx].m_fFlag,FALSE
                mov dword ptr [rdi],1

            .else

                mov iRes,ERROR_INVALID_PARAMETER
            .endif
        .endif
    .endif

    .if (iRes == ERROR_INVALID_PARAMETER)

        wcout << "/" << ([rbx].m_szTrueParamName) << " and /"
        wcout << ([rbx].m_szFalseParamName) << " parameters can't be used together!" << endl
    .endif

    .return iRes

CExclFlagParam::Init endp


    assume rbx:ptr CSetValueParam


CSetValueParam::Init proc uses rsi rdi rbx argc:int_t, argv:ptr ptr wchar_t, rParamsProcessed:ptr int_t

  local iRes:int_t

    mov rbx,rcx
    mov rdi,r9
    mov iRes,ERROR_SUCCESS
    xor eax,eax
    mov [rdi],eax
    mov rsi,[r8]
    mov al,[rsi]

    .if (al == '/' || al == '-')

        add rsi,2
        .if (!_wcsicmp(rsi, [rbx].m_szParamName))

            .if (![rbx].m_fExists)

                mov [rbx].m_fExists,TRUE
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

                    mov [rbx].m_szValue,rsi
                    mov dword ptr [rdi],2

                .else

                    mov iRes,ERROR_INVALID_PARAMETER
                    wcout << "No valid value following parameter /" << ([rbx].m_szParamName) << "!" << endl
                .endif

            .else

                mov iRes,ERROR_INVALID_PARAMETER
                wcout << "More than one instane of /" << ([rbx].m_szParamName) << " were found in command line!" << endl
            .endif
        .endif
    .endif

    .return iRes

CSetValueParam::Init endp

    assume rbx:nothing


ParseParams proc uses rsi rdi rbx pParams:ptr ptr CParamBase, dwParamCnt:DWORD, argc:int_t, argv:ptr ptr WCHAR

  local i:int_t
  local iRes:int_t
  local cp:ptr CParamBase

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
            mov rbx,[rsi+rax*8]

            wcout << "Unknown parameter: " << rbx << endl
        .endif
    .endw

    .return iRes

ParseParams endp

    end
