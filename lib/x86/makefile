include srcpath

all: import build libc

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
	htmlhelp.lib	\
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
	UIAutomationCore.lib \
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

{$(lib_dir)\x86\def}.def.lib:
	libw /NOLOGO /MACHINE:X86 /OUT:$(lib_dir)\x86\$*.lib /DEF:$<

build: $(targets)

import:
	if not exist %AsmcDir%\bin\impdef32.exe (
	   asmc -pe -Fo%AsmcDir%\bin\impdef32.exe $(src_dir)\tools\impdef\impdef.asm
	)
	md $(lib_dir)\x86\def
	impdef32 -p$(lib_dir)\x86\def -c msvcrt sensorsapi wldap32
	impdef32 -p$(lib_dir)\x86\def $(targets)

obj_src = \
	crt/_tcrt0.obj	\
	crt/_tWinStart.obj \
	stdio/acrtiobfunc.obj

obj_lib = \
	_tcrt0.obj	\
	_tcrt0W.obj	\
	_tWinStart.obj	\
	_tWinStartW.obj \
	acrtiobfunc.obj

{$(src_dir)\libc}.asm.obj:
	asmc -c -nologo -nolib -coff -Cs -MT -MD $<
	asmc -c -nologo -nolib -coff -Cs -MT -MD -ws -Fo*W $<

libc: $(obj_src)
	libw -q -b -c -fac msvcrt.lib $(obj_lib)
	del $(obj_lib)
	del *W.obj

