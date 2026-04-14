
# Build JWasm using LIBC and the C header files

JWasm.exe:
	cl -Isrc\H -I%ASMCDIR%\include\h -JMC -DNDEBUG -O1 -Os -w -Gm- -EHsc -MT -GS- -Gd -TC src\*.c -link -out:$@ -defaultlib:%ASMCDIR%\lib\x64\libc.lib
	del *.obj

