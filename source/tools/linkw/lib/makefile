#
# Makefile for OW.LIB
#
WATCOM  = \WATCOM
MSVC	= \VC
!ifdef CXX
debug	= 1
!endif
!ifdef debug
OUTP	= owd
CC	= $(MSVC)\bin\cl
CFLAGS  = -c -nologo -Zi -Od -DINSIDE_WLINK -DIDE_PGM -Isrc\h -I$(MSVC)\include
LIBMAKE = lib /out:$@
!else
OUTP	= ow
CC	= $(WATCOM)\binnt\wcc386
CFLAGS  = -q -zc -bc -bt=nt -ox -s -DINSIDE_WLINK -DNDEBUG -DIDE_PGM -I$(WATCOM)\h;src\h
LIBMAKE = libw -q -b -n -c $@
!endif

{src}.c.obj:
	$(CC) $(CFLAGS) $<

{src}.asm.obj:
	asmc -coff -Zi $<

dw_objs = \
	dwlngen.obj	dwutils.obj

orl_objs = \
	omfload.obj	omfmunge.obj	omfentr.obj	omfflhn.obj  \
	omfdrctv.obj	elfentr.obj	elflwlv.obj	elfflhn.obj  \
	elfload.obj	coffentr.obj	cofflwlv.obj	coffflhn.obj \
	coffload.obj	coffimpl.obj	orlentry.obj	orlflhnd.obj \
	orlhash.obj

# Objects needed for a stripped down wres lib that can only read string resources

wres_core_objs = \
	loadfind.obj	loadstr.obj	mrrdrh.obj	ralliae.obj  \
	rclosef.obj	rduint16.obj	rduint32.obj	rduint8.obj  \
	resseek.obj	ropenfro.obj	rrdstr.obj	rrnamoor.obj \
	varstr.obj	wraddres.obj	wrerror.obj	wrfindrs.obj \
	wrfirres.obj	wrfree.obj	wrfreedi.obj	wrgetli.obj  \
	wridcmp.obj	wridexby.obj	wridfnoo.obj	wridfrnu.obj \
	wridfrst.obj	wridnacm.obj	wriidfn.obj	wrinitdi.obj \
	wriswrf.obj	wrreaddi.obj	wrrewrid.obj	wrrfrr.obj   \
	wrrftr.obj	wrrhr.obj

# Additional objects for the full wres library

wres_more_objs = \
	loadres.obj	mropnewf.obj	rdlli.obj	resaccel.obj \
	resbitmp.obj	resdiag.obj	resfont.obj	resiccu.obj  \
	resmenu.obj	resnamor.obj	resraw.obj	resstr.obj   \
	restbar.obj	restell.obj	resver.obj	rillia.obj   \
	rillib.obj	ropenfrw.obj	rrlli.obj	wrauto.obj   \
	wrchkwrf.obj	wrdelrs.obj	wresrtns.obj	wrfilein.obj \
	wrgetri.obj	wrgetti.obj	wrhidcmp.obj	wrhidfno.obj \
	wrhidfre.obj	wrhidfrn.obj	wrhidfrs.obj	wridfree.obj \
	wridnfst.obj	wridtnoo.obj	wridtonu.obj	wridtost.obj \
	wrihidf.obj	wrisempt.obj	wrislr.obj	write.obj    \
	wrmergdi.obj	wrnextrs.obj	wropnewf.obj	wrrfwrid.obj \
	wrrwrid.obj	wrwritdi.obj

lib_objs = \
!ifdef debug
	alloca.obj	itoa.obj	dir.obj		gtcmd.obj \
!endif
	$(dw_objs) $(orl_objs) $(wres_core_objs) $(wres_more_objs)

$(OUTP).lib: $(lib_objs)
	$(LIBMAKE) *.obj
	@del *.obj
