#
# Note: needs Open Watcom
#
UiaSimpleProvider.exe:
	wrc -r -I\watcom\h\nt UiaSimpleProvider.rc
	asmc -coff -ws -Cs -Fe$* *.asm -link -res:UiaSimpleProvider.res
	asmc -win6 -ws -Cs -Fe$*64 *.asm -link -res:UiaSimpleProvider.res
	$@
	del *.res
	del *.obj
