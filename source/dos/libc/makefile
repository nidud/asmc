!include ../srcpath

$(LIBFILE).lib:
	iddc -ml -r *.idd
	asmc $(AFLAGS) -r $(src_dir)\libc\*.asm
	$(LIB) $(OFLAGS) *.obj
	del *.obj

