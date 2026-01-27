include srcpath

ifndef CC
CC = LIBW
crtpath = ..\..\source\libc\crt
crtflag = -c -q -win64 -Cs -MT -MD
endif

all: import build

.SUFFIXES: .lib
.EXTENSIONS: .def .lib

targets = \
	aclui.lib	\
	activeds.lib	\
	advapi32.lib	\
	advpack.lib	\
	appmgmts.lib	\
	appmgr.lib	\
	authz.lib	\
	avifil32.lib	\
	avrt.lib	\
	basesrv.lib	\
	bcrypt.lib	\
	cabinet.lib	\
	cfgmgr32.lib	\
	clusapi.lib	\
	comctl32.lib	\
	combase.lib	\
	comdlg32.lib	\
	compstui.lib	\
	comsvcs.lib	\
	credui.lib	\
	crypt32.lib	\
	cryptdll.lib	\
	cryptnet.lib	\
	cryptui.lib	\
	cryptxml.lib	\
	cscdll.lib	\
	d2d1.lib	\
	d3d11.lib	\
	d3d9.lib	\
	d3dcompiler_43.lib \
	d3dcompiler_47.lib \
	davclnt.lib	\
	dbgeng.lib	\
	dbghelp.lib	\
	dciman32.lib	\
	dcomp.lib	\
	ddraw.lib	\
	devenum.lib	\
	devmgr.lib	\
	dhcpcsvc.lib	\
	dhcpsapi.lib	\
	dinput8.lib	\
	dnsapi.lib	\
	dsound.lib	\
	dsprop.lib	\
	dssec.lib	\
	dsuiext.lib	\
	dwmapi.lib	\
	dwrite.lib	\
	dxtmsft.lib	\
	dxtrans.lib	\
	els.lib		\
	elscore.lib	\
	esent.lib	\
	evr.lib		\
	faultrep.lib	\
	feclient.lib	\
	gdi32.lib	\
	gdiplus.lib	\
	glmf32.lib	\
	glu32.lib	\
	glut32.lib	\
	gpedit.lib	\
	hid.lib		\
	hlink.lib	\
	httpapi.lib	\
	icm32.lib	\
	icmui.lib	\
	iesetup.lib	\
	imagehlp.lib	\
	imgutil.lib	\
	imm32.lib	\
	inseng.lib	\
	iphlpapi.lib	\
	kernel32.lib	\
	kernelbase.lib	\
	ksuser.lib	\
	ktmw32.lib	\
	libcmt.lib	\
	loadperf.lib	\
	lz32.lib	\
	Magnification.lib \
	mapi32.lib	\
	mf.lib		\
	mfplat.lib	\
	mfplay.lib	\
	mfreadwrite.lib \
	mgmtapi.lib	\
	mmcndmgr.lib	\
	mpr.lib		\
	mprapi.lib	\
	msaatext.lib	\
	msacm32.lib	\
	mscms.lib	\
	msdmo.lib	\
	msi.lib		\
	msimg32.lib	\
	mspatcha.lib	\
	msrating.lib	\
	mstask.lib	\
	msv1_0.lib	\
	msvcrt.lib	\
	msvfw32.lib	\
	mswsock.lib	\
	msxml3.lib	\
	msxml6.lib	\
	mtxdm.lib	\
	netapi32.lib	\
	newdev.lib	\
	normaliz.lib	\
	ntdll.lib	\
	ntdsapi.lib	\
	ntlanman.lib	\
	ntmarta.lib	\
	ntvdm64.lib	\
	objsel.lib	\
	odbc32.lib	\
	odbcbcp.lib	\
	odbccp32.lib	\
	ole32.lib	\
	oleacc.lib	\
	oleaut32.lib	\
	oledlg.lib	\
	oldnames.lib	\
	opengl32.lib	\
	p2p.lib		\
	p2pgraph.lib	\
	pdh.lib		\
	powrprof.lib	\
	psapi.lib	\
	rasapi32.lib	\
	rasdlg.lib	\
	resutils.lib	\
	riched20.lib	\
	rpcns4.lib	\
	rpcrt4.lib	\
	rstrtmgr.lib	\
	rtm.lib		\
	rtutils.lib	\
	samlib.lib	\
	samsrv.lib	\
	scecli.lib	\
	scesrv.lib	\
	schannel.lib	\
	SearchSDK.lib	\
	secur32.lib	\
	security.lib	\
	sens.lib	\
	sensapi.lib	\
	sensorsapi.lib	\
	setupapi.lib	\
	sfc.lib		\
	shell32.lib	\
	shfolder.lib	\
	shcore.lib	\
	shlwapi.lib	\
	snmpapi.lib	\
	spoolss.lib	\
	ssdpapi.lib	\
	sti.lib		\
	t2embed.lib	\
	tapi32.lib	\
	traffic.lib	\
	UIAutomationCore.lib \
	urlmon.lib	\
	user32.lib	\
	userenv.lib	\
	usp10.lib	\
	uxtheme.lib	\
	version.lib	\
	virtdisk.lib	\
	vssapi.lib	\
	webservices.lib \
	wer.lib		\
	winbio.lib	\
	Windows.storage.lib \
	winhttp.lib	\
	wininet.lib	\
	winmm.lib	\
	winscard.lib	\
	winspool.lib	\
	wintrust.lib	\
	wldap32.lib	\
	ws2_32.lib	\
	wscapi.lib	\
	wsnmp32.lib	\
	wsock32.lib	\
	wtsapi32.lib	\
	xmllite.lib	\
	xolehlp.lib	\
	xpsprint.lib

{$(lib_dir)\x64\def}.def.lib:
	$(CC) /NOLOGO /MACHINE:X64 /OUT:$(lib_dir)\x64\$*.lib /DEF:$<

build: $(targets)
ifeq LIBW $(CC)
	asmc $(crtflag) -Fo crt0 $(crtpath)\_tcrt0.asm
	asmc $(crtflag) -Fo WinStart $(crtpath)\_tWinStart.asm
	asmc $(crtflag) -Fo wcrt0 -ws $(crtpath)\_tcrt0.asm
	asmc $(crtflag) -Fo wWinStart -ws $(crtpath)\_tWinStart.asm
	libw -q -b -c -fac msvcrt.lib crt0.obj wcrt0.obj WinStart.obj wWinStart.obj
	del crt0.obj wcrt0.obj WinStart.obj wWinStart.obj
endif

import:
	if not exist %AsmcDir%\bin\impdef64.exe (
	   asmc64 -pe -Fo%AsmcDir%\bin\impdef64.exe $(src_dir)\tools\impdef\impdef.asm
	)
	md $(lib_dir)\x64\def
	impdef64 -p$(lib_dir)\x64\def $(targets)
