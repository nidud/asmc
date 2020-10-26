include shlobj.inc
include stdio.inc
include tchar.inc

ifdef __PE__
.data
IID_IWebBrowser2 GUID _IID_IWebBrowser2
CLSID_InternetExplorer GUID _CLSID_InternetExplorer
endif

.code

_tmain proc

  local pWebBrowser:ptr IWebBrowser2
  local pFullName:ptr BSTR

    CoInitialize(NULL)
    .ifd CoCreateInstance(
            &CLSID_InternetExplorer,
            NULL,
            CLSCTX_LOCAL_SERVER,
            &IID_IWebBrowser2,
            &pWebBrowser ) == S_OK

        pWebBrowser.get_FullName(&pFullName)
        _tprintf("%s\n", pFullName)
    .endif
    CoUninitialize()
    xor eax,eax
    ret

_tmain endp

    end _tstart
