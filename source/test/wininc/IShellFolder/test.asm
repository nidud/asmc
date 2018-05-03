;
; https://msdn.microsoft.com/en-us/library/windows/desktop/bb762114(v=vs.85).aspx
;
include windows.inc
include wininet.inc
include shlobj.inc
include shlwapi.inc
include stdio.inc
include tchar.inc

.data
GUID_NULL			GUID <0>
IID_IOleDocument		GUID _IID_IOleDocument
IID_IOleDocumentView		GUID _IID_IOleDocumentView
IID_IOleDocumentSite		GUID _IID_IOleDocumentSite
IID_IOleCommandTarget		GUID _IID_IOleCommandTarget
IID_IExplorerPaneVisibility	GUID _IID_IExplorerPaneVisibility
IID_IBandHost			GUID _IID_IBandHost
IID_INameSpaceTreeControl	GUID _IID_INameSpaceTreeControl
IID_INewMenuClient		GUID _IID_INewMenuClient
IID_IEnumerableView		GUID _IID_IEnumerableView
IID_IWebWizardExtension		GUID _IID_IWebWizardExtension
IID_IWizardSite			GUID _IID_IWizardSite
IID_IProfferService		GUID _IID_IProfferService
IID_ICommDlgBrowser		GUID _IID_ICommDlgBrowser
IID_IFolderView			GUID _IID_IFolderView
IID_IShellTaskScheduler		GUID _IID_IShellTaskScheduler
IID_IWebBrowserApp		GUID _IID_IWebBrowserApp
IID_IProtectFocus		GUID _IID_IProtectFocus
IID_IEnumOleDocumentViews	GUID _IID_IEnumOleDocumentViews
IID_IShellFolder		GUID _IID_IShellFolder

.code

main proc

  local psfParent:LPIShellFolder
  local pidlRelative:ptr PCUITEMID_CHILD
  local pidlItem:PIDLIST_ABSOLUTE
  local szDisplayName[MAX_PATH]:TCHAR
  local strret:STRRET

    mov pidlItem,ILCreateFromPath("C:\\")
    .ifd !SHBindToParent(pidlItem, &IID_IShellFolder, &psfParent, &pidlRelative)

	psfParent.GetDisplayNameOf(pidlRelative, SHGDN_NORMAL, &strret)
	psfParent.Release()
	StrRetToBuf(&strret, pidlRelative, &szDisplayName, MAX_PATH)
	printf("%s\n", &szDisplayName)
    .endif

    ILFree(pidlItem)
    xor eax,eax
    ret

main endp

    end _tstart
