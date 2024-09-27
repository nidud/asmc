ifndef CC
CC = LIBW
endif

all: import build

.SUFFIXES: .lib
.EXTENSIONS: .def .lib

targets = \
	aclui.lib	\
	activeds.lib	\
	advapi32.lib	\
	authz.lib	\
	avrt.lib	\
	bcrypt.lib	\
	cabinet.lib	\
	clusapi.lib	\
	comctl32.lib	\
	comdlg32.lib	\
	credui.lib	\
	crypt32.lib	\
	cryptui.lib	\
	cryptxml.lib	\
	d3d11.lib	\
	dbghelp.lib	\
	dhcpcsvc.lib	\
	dnsapi.lib	\
	dsuiext.lib	\
	dwmapi.lib	\
	elscore.lib	\
	evr.lib		\
	gdi32.lib	\
	glu32.lib	\
	glut32.lib	\
	gpedit.lib	\
	httpapi.lib	\
	icm32.lib	\
	icmui.lib	\
	imagehlp.lib	\
	imm32.lib	\
	iphlpapi.lib	\
	kernel32.lib	\
	ktmw32.lib	\
	loadperf.lib	\
	lz32.lib	\
	mapi32.lib	\
	mf.lib		\
	mfplat.lib	\
	mfplay.lib	\
	mfreadwrite.lib \
	mgmtapi.lib	\
	mpr.lib		\
	mprapi.lib	\
	msacm32.lib	\
	mscms.lib	\
	msi.lib		\
	msimg32.lib	\
	msvcrt.lib	\
	mswsock.lib	\
	msxml6.lib	\
	ncrypt.lib	\
	netapi32.lib	\
	normaliz.lib	\
	ntdll.lib	\
	ntdsapi.lib	\
	ntvdm.lib	\
	odbc32.lib	\
	odbccp32.lib	\
	oldnames.lib	\
	ole32.lib	\
	oleacc.lib	\
	oleaut32.lib	\
	oledlg.lib	\
	opengl32.lib	\
	p2p.lib		\
	pdh.lib		\
	powrprof.lib	\
	psapi.lib	\
	rasapi32.lib	\
	rasdlg.lib	\
	resutils.lib	\
	rpcns4.lib	\
	rpcrt4.lib	\
	rstrtmgr.lib	\
	rtm.lib		\
	rtutils.lib	\
	scarddlg.lib	\
	secur32.lib	\
	sensapi.lib	\
	sensorsapi.lib	\
	setupapi.lib	\
	sfc.lib		\
	shell32.lib	\
	shlwapi.lib	\
	snmpapi.lib	\
	sti.lib		\
	tapi32.lib	\
	traffic.lib	\
	urlmon.lib	\
	user32.lib	\
	userenv.lib	\
	usp10.lib	\
	uxtheme.lib	\
	version.lib	\
	virtdisk.lib	\
	webservices.lib \
	winbio.lib	\
	winfax.lib	\
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
	wtsapi32.lib

{def}.def.lib:
	$(CC) /NOLOGO /MACHINE:X86 /OUT:$*.lib /DEF:$<

build: $(targets)

import:
	if not exist ..\..\bin\impdef32.exe (
	   asmc -pe -Fo..\..\bin\impdef32.exe ..\..\source\tools\impdef\impdef.asm
	)
	md def
	impdef32 -pdef -c msvcrt sensorsapi wldap32
	impdef32 -pdef $(targets)
