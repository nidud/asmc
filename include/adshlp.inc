ifndef _ADSHLP_
_ADSHLP_ equ 1

;HRESULT
ADsGetObject proto WINAPI \
          lpszPathName: LPCWSTR,
                  riid: REFIID,
              ppObject: ptr ptr

;HRESULT
ADsBuildEnumerator proto WINAPI \
         pADsContainer: ptr IADsContainer,
         ppEnumVariant: ptr IEnumVARIANT

;HRESULT
ADsFreeEnumerator proto WINAPI \
          pEnumVariant: ptr IEnumVARIANT

;HRESULT
ADsEnumerateNext proto WINAPI \
          pEnumVariant: ptr IEnumVARIANT,
             cElements: ULONG,
                  pvar: ptr,
     pcElementsFetched: ptr

;HRESULT
ADsBuildVarArrayStr proto WINAPI \
          lppPathNames: ptr LPWSTR,
           dwPathNames: DWORD,
                  pVar: ptr

;HRESULT
ADsBuildVarArrayInt proto WINAPI \
       lpdwObjectTypes: LPDWORD,
         dwObjectTypes: DWORD,
                  pVar: ptr


;HRESULT
ADsOpenObject proto WINAPI \
          lpszPathName: LPCWSTR,
          lpszUserName: LPCWSTR,
          lpszPassword: LPCWSTR,
            dwReserved: DWORD,
                  riid: REFIID,


;HRESULT
ADsGetLastError proto WINAPI \
               lpError: LPDWORD,
            lpErrorBuf: LPWSTR,
         dwErrorBufLen: DWORD,
             lpNameBuf: LPWSTR,
          dwNameBufLen: DWORD


;VOID
ADsSetLastError proto WINAPI \
                 dwErr: DWORD,
              pszError: LPCWSTR,
           pszProvider: LPCWSTR


;VOID
ADsFreeAllErrorRecords proto WINAPI
;LPVOID WINAPI
AllocADsMem proto WINAPI :DWORD
;BOOL
FreeADsMem proto WINAPI pMem:LPVOID
;LPVOID WINAPI
ReallocADsMem proto WINAPI \
               pOldMem: LPVOID,
                 cbOld: DWORD,
                 cbNew: DWORD

;LPWSTR WINAPI
AllocADsStr proto WINAPI pStr:LPCWSTR
;BOOL
FreeADsStr proto WINAPI pStr:LPWSTR
;BOOL
ReallocADsStr proto WINAPI \
                 ppStr: ptr LPWSTR,
                  pStr: LPWSTR


;HRESULT
ADsEncodeBinaryData proto WINAPI \
             pbSrcData: PBYTE,
              dwSrcLen: DWORD,
          ppszDestData: ptr LPWSTR


;HRESULT
ADsDecodeBinaryData proto WINAPI \
             szSrcData: LPCWSTR,
           ppbDestData: ptr PBYTE,
            pdwDestLen: ptr ULONG


;HRESULT
PropVariantToAdsType proto WINAPI \
              pVariant: ptr,
          dwNumVariant: DWORD,
           ppAdsValues: ptr PADSVALUE,
          pdwNumValues: PDWORD


;HRESULT
AdsTypeToPropVariant proto WINAPI \
            pAdsValues: PADSVALUE,
           dwNumValues: DWORD,
              pVariant: ptr


;void
AdsFreeAdsValues proto WINAPI \
            pAdsValues: PADSVALUE,
           dwNumValues: DWORD

;HRESULT
BinarySDToSecurityDescriptor proto WINAPI \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
               pVarsec: ptr VARIANT,
         pszServerName: LPCWSTR,
              userName: LPCWSTR,
              passWord: LPCWSTR,
               dwFlags: DWORD


;HRESULT
SecurityDescriptorToBinarySD proto WINAPI \
            vVarSecDes: VARIANT,
  ppSecurityDescriptor: ptr,
           pdwSDLength: PDWORD,
         pszServerName: LPCWSTR,
              userName: LPCWSTR,
              passWord: LPCWSTR,
               dwFlags: DWORD

ifdef DBG
if DBG
externdef ADsMemList :LIST_ENTRY
externdef ADsMemCritSect :CRITICAL_SECTION
InitADsMem proto WINAPI
AssertADsMemLeaks proto WINAPI
DumpMemoryTracker proto WINAPI
else
InitADsMem macro
    endm
AssertADsMemLeaks macro
    endm
DumpMemoryTracker macro
    endm
endif
endif

endif ;; _ADSHLP_


