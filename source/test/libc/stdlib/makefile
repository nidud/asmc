.SUFFIXES: .asm .exe

.asm.exe:
	asmc64 -q -MT -Fe $*.exe $<

targets = \
	abort.exe \
	allmul.exe \
	args.exe \
	argv.exe \
	assert.exe \
	exec.exe \
	getenv.exe \
	searchenv.exe \
	spawn.exe \
	system.exe \
	_atodbl.exe \
	_fullpath.exe \
	_gcvt.exe \
	_makepath.exe

build: $(targets)
ifdef YACC
	rm -f *.o
else
	del *.obj
endif

clean:
ifdef YACC
	rm -f *.exe *.o
else
	del *.exe *.obj
endif
