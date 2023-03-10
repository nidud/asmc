hello-world:
	asmc64 -Zp8 -Cs -fpic ../../gtk-4.0/hello-world.asm
	asmc64 -Zp8 -Cs -fpic ../../gtk-4.0/builder.asm
	asmc64 -Zp8 -Cs -fpic ../../gtk-4.0/drawing.asm
	asmc64 -Zp8 -Cs -fpic ../../gtk-4.0/grid-packing.asm
	asmc64 -Zp8 -Cs -fpic ../../gtk-4.0/plugman.asm
	asmc64 -Zp8 -Cs -fpic ../../gtk-4.0/action-namespace.asm
	asmc64 -Zp8 -Cs -fpic ../../gtk-4.0/sunny.asm
	gcc -o hello-world hello-world.o `pkg-config --cflags --libs gtk4`
	gcc -o builder builder.o `pkg-config --cflags --libs gtk4`
	gcc -o drawing drawing.o `pkg-config --cflags --libs gtk4`
	gcc -o grid-packing grid-packing.o `pkg-config --cflags --libs gtk4`
	gcc -o plugman plugman.o `pkg-config --cflags --libs gtk4`
	gcc -o action-namespace action-namespace.o `pkg-config --cflags --libs gtk4`
	gcc -o sunny sunny.o `pkg-config --cflags --libs gtk4`


clean:
	rm *.o
	rm hello-world
	rm builder
	rm drawing
	rm grid-packing
	rm plugman
	rm action-namespace
	rm sunny
