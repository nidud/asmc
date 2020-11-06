
include csmcmd.inc

;; Forward declarations

EnumRoots   proto
EnumRules   proto
AddRoots    proto :PCWSTR
RemoveRoots proto :PCWSTR
AddRule     proto :BOOL, :BOOL, :BOOL, :PCWSTR
RemoveRule  proto :BOOL, :PCWSTR
Revert      proto
Reset       proto
Reindex     proto


    .data

     v1 CFlagParamVtbl      { { CFlagParam_Init } }
     v2 CExclFlagParamVtbl  { { CExclFlagParam_Init } }
     v3 CSetValueParamVtbl  { { CSetValueParam_Init } }

;; Global objects used for command line parsing.

g_IncludeParam      CExclFlagParam  { { v2, FALSE }, FALSE, @CStr(L"include"), @CStr(L"exclude") }
g_DefaultParam      CExclFlagParam  { { v2, FALSE }, FALSE, @CStr(L"default"), @CStr(L"user") }
g_OverrideParam     CFlagParam      { { v1, FALSE }, @CStr(L"override_children") }
g_EnumRootsParam    CFlagParam      { { v1, FALSE }, @CStr(L"enumerate_roots") }
g_EnumRulesParam    CFlagParam      { { v1, FALSE }, @CStr(L"enumerate_rules") }

g_AddRootParam      CSetValueParam  { { v3, FALSE }, @CStr(L"add_root"), NULL }
g_RemoveRootParam   CSetValueParam  { { v3, FALSE }, @CStr(L"remove_root"), NULL }
g_AddRuleParam      CSetValueParam  { { v3, FALSE }, @CStr(L"add_rule"), NULL }
g_RemoveRuleParam   CSetValueParam  { { v3, FALSE }, @CStr(L"remove_rule"), NULL }

g_RevertParam       CFlagParam      { { v1, FALSE }, @CStr(L"revert") }
g_Reset             CFlagParam      { { v1, FALSE }, @CStr(L"reset") }
g_Reindex           CFlagParam      { { v1, FALSE }, @CStr(L"reindex") }
g_HelpParam         CFlagParam      { { v1, FALSE }, @CStr(L"help") }
g_AltHelpParam      CFlagParam      { { v1, FALSE }, @CStr(L"?") }

;; List of all supported command line options.

Params LPCPARAMBASE \
    g_IncludeParam,
    g_DefaultParam,
    g_EnumRootsParam,
    g_EnumRulesParam,
    g_AddRootParam,
    g_RemoveRootParam,
    g_AddRuleParam,
    g_RemoveRuleParam,
    g_RevertParam,
    g_Reset,
    g_Reindex,
    g_HelpParam,
    g_AltHelpParam

;; List of alternative options corresponding to CSM operations.

ExclusiveParams LPCPARAMBASE \
    g_EnumRootsParam,
    g_EnumRulesParam,
    g_AddRootParam,
    g_RemoveRootParam,
    g_AddRuleParam,
    g_RemoveRuleParam,
    g_RevertParam,
    g_Reset,
    g_Reindex,
    g_HelpParam,
    g_AltHelpParam

;; Command line options help text

rgParamsHelp PCWSTR \
    @CStr(L"/enumerate_roots"),
    @CStr(L"/enumerate_rules"),
    @CStr(L"/add_root <new root path>"),
    @CStr(L"/remove_root <root path to remove>"),
    @CStr(L"/add_rule <rule URL> /[DEFAULT|USER] /[INCLUDE|EXCLUDE]"),
    @CStr(L"/remove_rule <rule URL> /[DEFAULT|USER]"),
    @CStr(L"/revert"),
    @CStr(L"/reset"),
    @CStr(L"/reindex"),
    @CStr(L"/help or /? ")


    .code

PrintHelp proc uses rsi rdi

  local p:PCWSTR

    wcout << "NOTE: you must run this tool as an admin to perform functions" << endl
    wcout << "      that change the state of the index" << endl
    wcout << "List of availible options:" << endl

    .for (rsi = &rgParamsHelp, edi = 0: edi < ARRAYSIZE(rgParamsHelp): edi++)

        lodsq
        mov p,rax

        wcout << "\t" << p << endl
    .endf
    .return ERROR_SUCCESS

PrintHelp endp


;; CheckExcusiveParameters function validates that only one option
;; from ExclusiveParams list is present in argument list

CheckExcusiveParameters proc uses rsi

  local i:int_t
  local iRes:int_t
  local dwCount:DWORD
  local Param:LPCPARAMBASE

    mov iRes,ERROR_SUCCESS
    mov dwCount,0
    lea rsi,ExclusiveParams

    .for (i = 0: i < ARRAYSIZE(ExclusiveParams): i++)

        lodsq
        mov Param,rax

        .if (Param.Exists())

            inc dwCount
        .endif
    .endf

    .if (dwCount == 0)

        wcout << "Error: CSM operation parameter is expected!" << endl
        mov iRes,ERROR_INVALID_PARAMETER

    .elseif (dwCount > 1)

        wcout << "Error: Duplicated CSM operation parameters!" << endl
        mov iRes,ERROR_INVALID_PARAMETER
    .endif
    .return iRes

CheckExcusiveParameters endp


wmain proc uses rsi argc:int_t, argv:ptr ptr wchar_t

  local hr:HRESULT
  local iRes:int_t

    mov hr,CoInitializeEx(NULL, COINIT_APARTMENTTHREADED or COINIT_DISABLE_OLE1DDE)
    .if (SUCCEEDED(hr))

        ;; Parsing command line

        dec argc
        mov r9,argv
        add r9,8
        mov iRes,ParseParams(&Params, ARRAYSIZE(Params), argc, r9)

        .if (iRes == ERROR_SUCCESS)

            ;; Check that only one CSM operation parameter was referred

            mov iRes,CheckExcusiveParameters()
            .if (iRes == ERROR_SUCCESS)

                ;; Default catalog name will be used if /CATALOG option doesn't specify otherwise

                mov edx,g_HelpParam.Exists()
                g_AltHelpParam.Exists()

                .if (eax || edx)

                    mov iRes,PrintHelp()

                .elseif (g_EnumRootsParam.Exists())

                    mov iRes,EnumRoots()

                .elseif (g_EnumRulesParam.Exists())

                    mov iRes,EnumRules()

                .elseif (g_AddRootParam.Exists())

                    mov iRes,AddRoots(g_AddRootParam.Get())

                .elseif (g_RemoveRootParam.Exists())

                    mov iRes,RemoveRoots(g_RemoveRootParam.Get())

                .elseif (g_AddRuleParam.Exists())

                    mov esi,g_DefaultParam.Exists()
                    and esi,g_DefaultParam.Get()
                    mov edx,g_IncludeParam.Exists()
                    and edx,g_IncludeParam.Get()
                    mov r8d,g_OverrideParam.Exists()
                    mov iRes,AddRule(esi, edx, r8d, g_AddRuleParam.Get())

                .elseif (g_RemoveRuleParam.Exists())

                    mov esi,g_DefaultParam.Exists()
                    and esi,g_DefaultParam.Get()
                    mov iRes,RemoveRule(ecx, g_RemoveRuleParam.Get())

                .elseif (g_RevertParam.Exists())

                    mov iRes,Revert()

                .elseif (g_Reset.Exists())

                    mov iRes,Reset()

                .elseif (g_Reindex.Exists())

                    mov iRes,Reindex()
                .else
                    .assert(!"Required parameter is missing!")
                .endif
            .else

                mov iRes,PrintHelp()
            .endif
        .endif

        CoUninitialize()
    .endif
    .return 0

wmain endp


ReportHRESULTError proc pszOpName:PCWSTR, hr:HRESULT

  local iErr:int_t

    mov iErr,0

    .if (FAILED(hr))

        .if HRESULT_FACILITY(hr) == FACILITY_WIN32

            mov iErr,HRESULT_CODE(hr)
           .new pMsgBuf:PCWSTR

            FormatMessageW(
                FORMAT_MESSAGE_ALLOCATE_BUFFER or FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                iErr,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                &pMsgBuf,
                0,
                NULL )

            wcout << endl << "Error: " << pszOpName << " failed with error " \
                  << iErr << ": " << pMsgBuf << endl

            LocalFree(pMsgBuf)
        .else

            wcout << endl << "Error: " << pszOpName << " failed with error " << hr << endl
            mov iErr,-1
        .endif
    .endif

    .return iErr

ReportHRESULTError endp


CreateCatalogManager proc ppSearchCatalogManager:ptr ptr ISearchCatalogManager

  local hr:HRESULT
  local pSearchManager:ptr ISearchManager

    xor eax,eax
    mov [rcx],rax
    mov hr,CoCreateInstance(&CLSID_CSearchManager, NULL, CLSCTX_SERVER,
            &IID_ISearchManager, &pSearchManager)

    .if (SUCCEEDED(hr))

        mov hr,pSearchManager.GetCatalog(L"SystemIndex", ppSearchCatalogManager)
        pSearchManager.Release()
    .endif
    .return hr

CreateCatalogManager endp


CreateCrawlScopManager proc ppSearchCrawlScopeManager:ptr ptr ISearchCrawlScopeManager

  local hr:HRESULT
  local pCatalogManager:ptr ISearchCatalogManager

    xor eax,eax
    mov [rcx],rax

    mov hr,CreateCatalogManager(&pCatalogManager)
    .if (SUCCEEDED(hr))

        ;; Crawl scope manager for that catalog
        mov hr,pCatalogManager.GetCrawlScopeManager(ppSearchCrawlScopeManager)
        pCatalogManager.Release()
    .endif
    .return hr

CreateCrawlScopManager endp


DisplayRootInfo proc pSearchRoot:ptr ISearchRoot

  local hr:HRESULT
  local pszUrl:PWSTR
  local fProvidesNotifications:BOOL

    mov pszUrl,NULL

    mov hr,pSearchRoot.get_RootURL(&pszUrl)
    .if (SUCCEEDED(hr))

        wcout << "\t" << pszUrl

        mov fProvidesNotifications,FALSE
        mov hr,pSearchRoot.get_ProvidesNotifications(&fProvidesNotifications)

        .if (SUCCEEDED(hr) && fProvidesNotifications)

            wcout << " - Provides Notifications"
        .endif
        CoTaskMemFree(pszUrl)
    .endif
    wcout << endl

    .return hr

DisplayRootInfo endp


EnumRoots proc

  local hr:HRESULT
  local pSearchCrawlScopeManager:ptr ISearchCrawlScopeManager
  local pSearchRoots:ptr IEnumSearchRoots
  local pSearchRoot:ptr ISearchRoot

    ;; Crawl scope manager for that catalog

    mov hr,CreateCrawlScopManager(&pSearchCrawlScopeManager)
    .if (SUCCEEDED(hr))

        ;; Search roots on that crawl scope

        mov hr,pSearchCrawlScopeManager.EnumerateRoots(&pSearchRoots)
        .if (SUCCEEDED(hr))

            .while SUCCEEDED(hr)

                mov hr,pSearchRoots.Next(1, &pSearchRoot, NULL)
                .break .if hr != S_OK

                mov hr,DisplayRootInfo(pSearchRoot)
                pSearchRoot.Release()
            .endw
            pSearchRoots.Release()
        .endif
        pSearchCrawlScopeManager.Release()
    .endif

    .return ReportHRESULTError(L"EnumRoots()", hr)

EnumRoots endp


AddRoots proc pszURL:PCWSTR

    wcout << "Adding new root " << pszURL << endl

    ;; Crawl scope manager for that catalog

    .new pCatalogManager:ptr ISearchCatalogManager
    .new hr:HRESULT
     mov hr,CreateCatalogManager(&pCatalogManager)

    .if (SUCCEEDED(hr))

        ;; Crawl scope manager for that catalog

       .new pSearchCrawlScopeManager:ptr ISearchCrawlScopeManager
        mov hr,pCatalogManager.GetCrawlScopeManager(&pSearchCrawlScopeManager)

        .if (SUCCEEDED(hr))

           .new pISearchRoot:ptr ISearchRoot
            mov hr,CoCreateInstance(&CLSID_CSearchRoot, NULL, CLSCTX_ALL, &IID_ISearchRoot, &pISearchRoot)

            .if (SUCCEEDED(hr))

                mov hr,pISearchRoot.put_RootURL(pszURL)
                .if (SUCCEEDED(hr))

                    mov hr,pSearchCrawlScopeManager.AddRoot(pISearchRoot)
                    .if (SUCCEEDED(hr))

                        mov hr,pSearchCrawlScopeManager.SaveAll()
                        .if (SUCCEEDED(hr))

                            mov hr,pCatalogManager.ReindexSearchRoot(pszURL)
                            .if (SUCCEEDED(hr))

                                wcout << "Reindexing was started for root " << pszURL << endl
                            .endif
                        .endif
                    .endif
                .endif
                pISearchRoot.Release()
            .endif
            pSearchCrawlScopeManager.Release()
        .endif
        pCatalogManager.Release()
    .endif
    .return ReportHRESULTError(L"AddRoots()", hr)

AddRoots endp


RemoveRoots proc pszURL:PCWSTR

  local hr:HRESULT

    wcout << "Removing root " << pszURL << endl

    ;; Crawl scope manager for that catalog

   .new pSearchCrawlScopeManager:ptr ISearchCrawlScopeManager
    mov hr,CreateCrawlScopManager(&pSearchCrawlScopeManager)

    .if (SUCCEEDED(hr))

        mov hr,pSearchCrawlScopeManager.RemoveRoot(pszURL)
        .if (SUCCEEDED(hr))

            mov hr,pSearchCrawlScopeManager.SaveAll()
        .endif
        pSearchCrawlScopeManager.Release();
    .endif
    .return ReportHRESULTError(L"AddRoots()", hr)

RemoveRoots endp


DisplayRule proc pSearchScopeRule:ptr ISearchScopeRule

  local hr:HRESULT
  local pszUrl:PWSTR
  local fDefault:BOOL
  local fIncluded:BOOL

    mov hr,pSearchScopeRule.get_PatternOrURL(&pszUrl)
    .if (SUCCEEDED(hr))

        wcout << "\t" << pszUrl
        mov fDefault,FALSE
        mov hr,pSearchScopeRule.get_IsDefault(&fDefault)
        .if (SUCCEEDED(hr))

            .if !fDefault
                wcout << " NOT"
            .endif
            wcout << " DEFAULT"

            mov fIncluded,FALSE
            mov hr,pSearchScopeRule.get_IsIncluded(&fIncluded)
            .if (SUCCEEDED(hr))

                .if fIncluded
                    wcout << " INCLUDED"
                .else
                    wcout << " EXCLUDED "
                .endif
            .endif
        .endif
        CoTaskMemFree(pszUrl)
    .endif
    wcout << endl
   .return hr

DisplayRule endp


EnumRules proc

  local hr:HRESULT
  local pSearchCrawlScopeManager:ptr ISearchCrawlScopeManager
  local pScopeRules:ptr IEnumSearchScopeRules
  local pSearchScopeRule:ptr ISearchScopeRule

    ;; Crawl scope manager for that catalog

    mov hr,CreateCrawlScopManager(&pSearchCrawlScopeManager)
    .if (SUCCEEDED(hr))

        ;; Search roots on that crawl scope

        mov hr,pSearchCrawlScopeManager.EnumerateScopeRules(&pScopeRules)
        .if (SUCCEEDED(hr))

            .while SUCCEEDED(hr)

                mov hr,pScopeRules.Next(1, &pSearchScopeRule, NULL)
                .break .if hr != S_OK

                mov hr,DisplayRule(pSearchScopeRule)
                pSearchScopeRule.Release()
            .endw
            pScopeRules.Release()
        .endif
        pSearchCrawlScopeManager.Release()
    .endif

    .return ReportHRESULTError(L"EnumRules()", hr)
EnumRules endp


AddRule proc fDefault:BOOL, fInclude:BOOL, fOverride:BOOL, pszURL:PCWSTR

    wcout << "Adding new "
    .if fDefault
        wcout << "default "
    .else
        wcout << "user "
    .endif
    .if fInclude
        wcout << "inclusion "
    .else
        wcout << "exclusion "
    .endif
    wcout << "rule " << pszURL
    .if (!fDefault && fOverride)
        wcout << "overriding cildren rules"
    .endif
    wcout << endl

    ;; Crawl scope manager for that catalog

    .new hr:HRESULT
    .new pSearchCrawlScopeManager:ptr ISearchCrawlScopeManager

    mov hr,CreateCrawlScopManager(&pSearchCrawlScopeManager)
    .if (SUCCEEDED(hr))

        .if (fDefault)

            mov hr,pSearchCrawlScopeManager.AddDefaultScopeRule(pszURL, fInclude, FF_INDEXCOMPLEXURLS)

        .else

            mov hr,pSearchCrawlScopeManager.AddUserScopeRule(pszURL,
                                                             fInclude,
                                                             fOverride,
                                                             FF_INDEXCOMPLEXURLS)
        .endif
        .if (SUCCEEDED(hr))

            mov hr,pSearchCrawlScopeManager.SaveAll()
        .endif
        pSearchCrawlScopeManager.Release()
    .endif
    .return ReportHRESULTError(L"AddRules()", hr)
AddRule endp


RemoveRule proc fDefault:BOOL, pszURL:PCWSTR

    wcout << "Removing "
    .if fDefault
        wcout << "default"
    .else
        wcout << "user"
    .endif
    wcout << " rule " << pszURL << endl

    ;; Crawl scope manager for that catalog

    .new hr:HRESULT
    .new pSearchCrawlScopeManager:ptr ISearchCrawlScopeManager

    mov hr,CreateCrawlScopManager(&pSearchCrawlScopeManager)
    .if (SUCCEEDED(hr))

        .if (fDefault)
            mov hr,pSearchCrawlScopeManager.RemoveDefaultScopeRule(pszURL)
        .else
            mov hr,pSearchCrawlScopeManager.RemoveScopeRule(pszURL)
        .endif
        .if (SUCCEEDED(hr))
            mov hr,pSearchCrawlScopeManager.SaveAll()
        .endif
        pSearchCrawlScopeManager.Release()
    .endif
    .return ReportHRESULTError(L"AddRules()", hr)

RemoveRule endp


Revert proc

  local hr:HRESULT
  local pSearchCrawlScopeManager:ptr ISearchCrawlScopeManager

    wcout << "Reverting catalog to its default state." << endl

    ;; Crawl scope manager for that catalog

    mov hr,CreateCrawlScopManager(&pSearchCrawlScopeManager)
    .if (SUCCEEDED(hr))

        mov hr,pSearchCrawlScopeManager.RevertToDefaultScopes()
        .if (SUCCEEDED(hr))

            mov hr,pSearchCrawlScopeManager.SaveAll()
        .endif
        pSearchCrawlScopeManager.Release()
    .endif

    .return ReportHRESULTError(L"Revert()", hr)

Revert endp


Reset proc

  local hr:HRESULT
  local pCatalogManager:ptr ISearchCatalogManager

    wcout << "Resetting catalog." << endl

    mov hr,CreateCatalogManager(&pCatalogManager)
    .if (SUCCEEDED(hr))

        mov hr,pCatalogManager.Reset()
        pCatalogManager.Release()
    .endif
    .return ReportHRESULTError(L"Reset()", hr)

Reset endp


Reindex proc

  local hr:HRESULT
  local pCatalogManager:ptr ISearchCatalogManager

    wcout << "Reindexing catalog." << endl

    mov hr,CreateCatalogManager(&pCatalogManager)
    .if (SUCCEEDED(hr))

        mov hr,pCatalogManager.Reset()
        pCatalogManager.Release()
    .endif
    .return ReportHRESULTError(L"Reindex()", hr)

Reindex endp

    end
