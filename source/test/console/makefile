flags = -q -Zp8 -ws -Cs
ifdef x86
flags += -8 -coff
else
flags += -win64 -frame
endif

.SUFFIXES: .asm .exe .obj

.asm.obj:
	asmc $(flags) $<
.asm.exe:
	asmc $(flags) -pe $<

ifndef x86
win64 = AddPackageSample.exe \
	AmsiStream.exe \
	AppVisibilitySample.exe \
	AsyncServer.exe \
	AudioClip.exe \
	DeviceIoControl.exe \
	DLEdit.exe \
	EventingController.exe \
	FindPackagesSample.exe \
	FlowText.obj \
	HttpToText.exe
endif
common= aclapi.exe \
	AddDumpSample.exe \
	ClipboardContent.exe \
	ClipboardDelete.exe \
	CompressAPI.exe \
	ConsoleEvent.exe \
	ConsoleScreenBuffer.exe \
	Contosolnk.exe \
	CreateAppx.exe \
	DirectXVideoMemory.exe \
	DHCPGetPolicy.exe \
	DHCPGetRelationship.exe \
	DHCPGetSystemTime.exe \
	DNSAsyncNetworkNameResolution.exe \
	EnumClipboard.exe \
	ExtendedFileAPIs.exe \
	FileOperationSample.obj \
	GetFirewallSettings.exe \
	GetNativeSystemInfo.exe \
	GetNetworkWin32.exe \
	GetNetworkWinrt.exe \
	GetSystemInfo.exe \
	HashComputation.exe \
	HtmlHelp.exe \
	HttpInternationalDomainName.exe \
	INetworkListManager.exe \
	JobObject.exe \
	MSXMLDynamDOM.exe \
	MSXMLLoadDom.exe \
	MSXMLQueryNodes.exe \
	MSXMLSaveDom.exe \
	MSXMLXSLT.exe \
	NetShare.exe \
	PeerGroup.exe \
	ProcessorInfo.exe \
	ProcList.exe \
	ProgramFiles.exe \
	SaveAsImageFileSample.exe \
	SearchEvents.obj \
	SetConsoleCtrlHandler.exe \
	SHBindToParent.exe \
	ShellExecuteEx.exe \
	threadpool.exe \
	WebBrowser.exe \
	WinInet.exe \
	WinNetWK.exe \
	WscApiSample.exe

build: $(common) $(win64)

clean:
ifdef YACC
	rm -f *.obj *.exe *.manifest
else
	del *.obj *.exe *.manifest
endif

