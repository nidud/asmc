!include srcpath

all: .lbc64 .build .startup .clean

.SUFFIXES: .lib
.EXTENSIONS: .def .lbc .lib

source_path = ..\def

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
	dbgeng.lib	\
	dbghelp.lib	\
	dhcpcsvc.lib	\
	dnsapi.lib	\
	dsuiext.lib	\
	dwmapi.lib	\
	elscore.lib	\
	evr.lib		\
	gdi32.lib	\
	glu32.lib	\
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
	ntdsapi.lib	\
	odbc32.lib	\
	odbccp32.lib	\
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
	virtdisk.lib	\
	webservices.lib \
	winbio.lib	\
	winfax.lib	\
	winhttp.lib	\
	wininet.lib	\
	winmm.lib	\
	winscard.lib	\
	wintrust.lib	\
	wldap32.lib	\
	ws2_32.lib	\
	wscapi.lib	\
	wsnmp32.lib	\
	wsock32.lib	\
	wtsapi32.lib	\
	xpsprint.lib

{$(source_path)}.def.lib:
	lbc64 $<
	libw /n /c /q /b /fac /i6 $*.lib @$*.lbc

.build: $(targets)

.lbc64:
	asmc -pe -D__PE__ $(source_path)\lbc64.asm

.startup:
	asmc -nologo -I$(inc_dir) -win64 -D_NOARGV crt.asm
	asmc -nologo -I$(inc_dir) -win64 -Fo $(lib_dir)\crtc.obj crt.asm
	asmc -nologo -I$(inc_dir) -win64 -D_DLL -Fo $(lib_dir)\crtdll.obj crt.asm
	asmc -nologo -I$(inc_dir) -win64 -ws -D_UNICODE -D_NOARGV -Fo $(lib_dir)\crtw.obj crt.asm
	asmc -nologo -I$(inc_dir) -win64 -ws -D_UNICODE -Fo $(lib_dir)\crtwc.obj crt.asm
	asmc -nologo -I$(inc_dir) -win64 -ws -D_UNICODE -D_DLL -Fo $(lib_dir)\crtwdll.obj crt.asm
	asmc -nologo -I$(inc_dir) -win64 -Zi -D_NOARGV -Fo $(lib_dir)\crtd.obj $(lib_dir)\crt.asm
	asmc -nologo -I$(inc_dir) -win64 -Zi -Fo $(lib_dir)\crtcd.obj $(lib_dir)\crt.asm
	asmc -nologo -I$(inc_dir) -win64 -Zi -D_DLL -Fo $(lib_dir)\crtdlld.obj $(lib_dir)\crt.asm
	asmc -nologo -I$(inc_dir) -win64 -Zi -ws -D_UNICODE -D_NOARGV -Fo $(lib_dir)\crtwd.obj $(lib_dir)\crt.asm
	asmc -nologo -I$(inc_dir) -win64 -Zi -ws -D_UNICODE -Fo $(lib_dir)\crtwcd.obj $(lib_dir)\crt.asm
	asmc -nologo -I$(inc_dir) -win64 -Zi -ws -D_UNICODE -D_DLL -Fo $(lib_dir)\crtwdlld.obj $(lib_dir)\crt.asm

.clean:
	del lbc64.exe
	del *.lbc
