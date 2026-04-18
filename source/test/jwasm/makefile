
# Build JWasm using LIBC and the C header files

JWasm.exe:
	cl -Isrc\H -I%ASMCDIR%\include\h -DNDEBUG -O1 -Os -w -Gm- -EHsc -MT -GS- -Gd -TC src\*.c -link -out:$@ -libpath:%ASMCDIR%\lib\x64
	del *.obj

