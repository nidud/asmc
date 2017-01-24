
c0.obj:
	asmc -nologo -Fo ..\..\lib\c0.obj crt.asm
	asmc -nologo -Fo ..\..\lib\w0.obj crtow.asm
	asmc -nologo -Fo ..\..\lib\d0.obj crtdll.asm
	asmc -nologo -Fo ..\..\lib\v0.obj -coff crtvc.asm

	asmc -nologo -coff -Zi -Fo ..\..\lib\c0d.obj crt.asm
	asmc -nologo -coff -Zi -Fo ..\..\lib\w0d.obj crtow.asm
	asmc -nologo -coff -Zi -Fo ..\..\lib\d0d.obj crtdll.asm
	asmc -nologo -coff -Zi -Fo ..\..\lib\v0d.obj crtvc.asm
