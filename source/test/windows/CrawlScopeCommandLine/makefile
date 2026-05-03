CrawlScopeCommandLine:
	asmc64 -Fe$@ -ws *.asm
	$@  /enumerate_roots
	pause
	del *.obj
	del $@.exe
vs:
	project -p -u CrawlScopeCommandLine cmdline csmcmd
