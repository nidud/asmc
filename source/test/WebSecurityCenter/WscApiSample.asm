;;
;; https://github.com/microsoft/Windows-classic-samples
;;
;; This sample demonstrates how to query Security Center for the product name,
;; product state, and product signature status for each security product
;; registered.
;;

include stdio.inc
include atlbase.inc
include wscapi.inc
include iwscapi.inc
include tchar.inc

.data
 CLSID_WSCProductList GUID {0x17072F7B,0x9ABE,0x4A74,{0xA2,0x61,0x1E,0xB7,0x6B,0x55,0x10,0x7A}}
 IID_IWSCProductList  GUID {0x722A338C,0x6E8E,0x4E72,{0xAC,0x27,0x14,0x17,0xFB,0x0C,0x81,0xC2}}

.code

GetSecurityProducts proc uses rsi rdi rbx provider:WSC_SECURITY_PROVIDER

    .new hr:HRESULT                             = S_OK
    .new PtrProduct:ptr IWscProduct             = NULL
    .new PtrProductList:ptr IWSCProductList     = NULL
    .new PtrVal:BSTR                            = NULL
    .new ProductCount:LONG                      = 0
    .new ProductState:WSC_SECURITY_PRODUCT_STATE
    .new ProductStatus:WSC_SECURITY_SIGNATURE_STATUS

    .if (provider != WSC_SECURITY_PROVIDER_FIREWALL && \
         provider != WSC_SECURITY_PROVIDER_ANTIVIRUS && \
         provider != WSC_SECURITY_PROVIDER_ANTISPYWARE)

        mov hr,E_INVALIDARG
        jmp done
    .endif

    ;;
    ;; Initialize can only be called once per instance, so you need to
    ;; CoCreateInstance for each security product type you want to query.
    ;;
    mov hr,CoCreateInstance(
            &CLSID_WSCProductList,
            NULL,
            CLSCTX_INPROC_SERVER,
            &IID_IWSCProductList,
            &PtrProductList)
    .if (FAILED(hr))

        wprintf("CoCreateInstance returned error = 0x%d \n", hr)
        jmp done
    .endif

    ;;
    ;; Initialize the product list with the type of security product you're
    ;; interested in.
    ;;
    mov hr,PtrProductList.Initialize(provider)
    .if (FAILED(hr))

        wprintf("Initialize failed with error: 0x%d\n", hr)
        jmp done
    .endif

    ;;
    ;; Get the number of security products of that type.
    ;;
    mov hr,PtrProductList.get_Count(&ProductCount)
    .if (FAILED(hr))

        wprintf("get_Count failed with error: 0x%d\n", hr)
        jmp done
    .endif

    .if (provider == WSC_SECURITY_PROVIDER_FIREWALL)

        wprintf("\n\nFirewall Products:\n")

    .elseif (provider == WSC_SECURITY_PROVIDER_ANTIVIRUS)

        wprintf("\n\nAntivirus Products:\n")
    .else
        wprintf("\n\nAntispyware Products:\n")
    .endif

    ;;
    ;; Loop over each product, querying the specific attributes.
    ;;
    .for (ebx = 0: ebx < ProductCount: ebx++)

        ;;
        ;; Get the next security product
        ;;
        mov hr,PtrProductList.get_Item(ebx, &PtrProduct)
        .if (FAILED(hr))

            wprintf("get_Item failed with error: 0x%d\n", hr)
            jmp done
        .endif

        ;;
        ;; Get the product name
        ;;

        mov hr,PtrProduct.get_ProductName(&PtrVal)
        .if (FAILED(hr))

            wprintf("get_ProductName failed with error: 0x%d\n", hr)
            jmp done
        .endif
        wprintf("\nProduct name: %s\n", PtrVal)

        ;; Caller is responsible for freeing the string

        SysFreeString(PtrVal)
        mov PtrVal,NULL

        ;;
        ;; Get the product state
        ;;

        mov hr,PtrProduct.get_ProductState(&ProductState)
        .if (FAILED(hr))

            wprintf("get_ProductState failed with error: 0x%d\n", hr)
            jmp done
        .endif

        .new pszState:LPWSTR
        .if (ProductState == WSC_SECURITY_PRODUCT_STATE_ON)
            mov pszState,&@CStr("On")
        .elseif (ProductState == WSC_SECURITY_PRODUCT_STATE_OFF)
            mov pszState,&@CStr("Off")
        .elseif (ProductState == WSC_SECURITY_PRODUCT_STATE_SNOOZED)
            mov pszState,&@CStr("Snoozed")
        .else
            mov pszState,&@CStr("Expired")
        .endif
        wprintf("Product state: %s\n", pszState)

        ;;
        ;; Get the signature status (not applicable to firewall products)
        ;;

        .if (provider != WSC_SECURITY_PROVIDER_FIREWALL)

            mov hr,PtrProduct.get_SignatureStatus(&ProductStatus)
            .if (FAILED(hr))

                wprintf("get_SignatureStatus failed with error: 0x%d\n", hr)
                jmp done
            .endif
            .new pszStatus:LPWSTR = "Out-of-date"
            .if (ProductStatus == WSC_SECURITY_PRODUCT_UP_TO_DATE)
                mov pszStatus,&@CStr("Up-to-date")
            .endif
            wprintf("Product status: %s\n", pszStatus)
        .endif

        ;;
        ;; Get the remediation path for the security product
        ;;
        mov hr,PtrProduct.get_RemediationPath(&PtrVal)
        .if (FAILED(hr))

            wprintf("get_RemediationPath failed with error: 0x%d\n", hr)
            jmp done
        .endif
        wprintf("Product remediation path: %s\n", PtrVal)

        ;; Caller is responsible for freeing the string

        SysFreeString(PtrVal)
        mov PtrVal,NULL

        ;;
        ;; Get the product state timestamp (updated when product changes its
        ;; state), and only applicable for AV products (NULL is returned for
        ;; AS and FW products)
        ;;
        .if (provider == WSC_SECURITY_PROVIDER_ANTIVIRUS)

            mov hr,PtrProduct.get_ProductStateTimestamp(&PtrVal)
            .if (FAILED(hr))

                wprintf("get_ProductStateTimestamp failed with error: 0x%d\n", hr)
                jmp done
            .endif
            wprintf("Product state timestamp: %s\n", PtrVal)

            ;; Caller is responsible for freeing the string

            SysFreeString(PtrVal)
            mov PtrVal,NULL
        .endif

        PtrProduct.Release()
        mov PtrProduct,NULL
    .endf

done:

    .if PtrVal

        SysFreeString(PtrVal)
    .endif
    .if PtrProductList

        PtrProductList.Release()
    .endif
    .if PtrProduct

        PtrProduct.Release()
    .endif
    .return hr

GetSecurityProducts endp

PrintUsage proc

    wprintf("Usage: WscApiSample.exe [-av | -as | -fw]\n")
    wprintf("   av: Query Antivirus programs\n")
    wprintf("   as: Query Antispyware programs\n")
    wprintf("   fw: Query Firewall programs\n\n")
    ret

PrintUsage endp

wmain proc uses rsi rdi rbx argc:int_t, argv:ptr LPCWSTR

    .new rc:int_t = 0
    .new hr:HRESULT = S_OK
    .new iProviderCount:int_t = 0
    .new providers[3]:WSC_SECURITY_PROVIDER

    .if (argc < 2 || argc > 4)

        PrintUsage()
        .return -1
    .endif

    ;;
    ;; Parse command line arguments
    ;;
    mov rsi,argv
    add rsi,LPCWSTR

    .for (edi = 0, ebx = 1: ebx < argc: ebx++, rsi+=LPCWSTR)

        .if (_wcsnicmp([rsi], "-av", MAX_PATH) == 0)

            mov providers[rdi*4],WSC_SECURITY_PROVIDER_ANTIVIRUS
            inc edi

        .elseif (_wcsnicmp([rsi], "-as", MAX_PATH) == 0)

            mov providers[rdi*4],WSC_SECURITY_PROVIDER_ANTISPYWARE
            inc edi

        .elseif (_wcsnicmp([rsi], "-fw", MAX_PATH) == 0)

            mov providers[rdi*4],WSC_SECURITY_PROVIDER_FIREWALL
            inc edi

        .else

            PrintUsage()
            .return -1
        .endif
    .endf

    CoInitializeEx( 0, COINIT_APARTMENTTHREADED )

    .for (ebx = 0: ebx < edi: ebx++)

        ;;
        ;; Query security products of the specified type (AV, AS, or FW)
        ;;
        mov hr,GetSecurityProducts(providers[rbx*4])
        .if (FAILED(hr))

            mov rc,-1
            .break
        .endif
    .endf

    CoUninitialize()
    .return rc

wmain endp

    end _tstart
