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
	asmc $(flags) -peg $<

ifndef x86
win64 = CpuUsage.exe \
	DirectCompositionEffects.exe \
	Direct3D11Tutorial04.obj \
	Direct3D11Tutorial05.obj \
	DirectXLights.exe \
	DirectXMatrices.exe \
	DirectXMeshes.exe \
	DirectXTextures.exe \
	DirectXVertices.exe \
	Fireworks.exe \
	GeometryRealizationSample.exe \
	ListViewSample.exe \
	MTGestures.eax \
	SimplePathAnimationSample.exe \
	TimerCoalescence.exe \
	WicViewerGdiPlus.exe \
	wrl.exe \
	yuruyurau1.exe \
	yuruyurau2.exe \
	yuruyurau3.exe \
	yuruyurau4.exe \
	yuruyurau5.exe \
	yuruyurau6.exe \
	Zoom.exe
endif

common= BouncingBalls.exe \
	CreateFont.exe \
	DesktopToastsSample.exe \
	DesktopToastsUninstall.eax \
	Direct2DHelloWorld.exe \
	Direct2DInteropSample.exe \
	Direct3D11Tutorial01.exe \
	Direct3D11Tutorial02.exe \
	Direct3D11Tutorial03.exe \
	DirectXCreateDevice.exe \
	FullscreenMagnifierSample.exe \
	GdiBeziercurve.exe \
	GdiLinejoins.exe \
	GdiLines.exe \
	GdiPenstyles.exe \
	GdiPixels.exe \
	GdiRectangle.exe \
	GdiSolidbrush.exe \
	IdentifyInputSource.exe \
	IPicture.exe \
	MagnifierSample.exe \
	SimpleDirect2dApplication.exe \
	TaskDialog.exe \
	WicAnimatedGif.exe

build: $(common) $(win64)

clean:
ifdef YACC
	rm -f *.exe *.manifest
else
	del *.obj *.exe *.manifest
endif

DesktopToastsUninstall.eax:
	asmc $(flags) -pe DesktopToastsUninstall.asm
