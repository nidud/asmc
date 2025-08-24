
all: heapwalk clean

heapwalk:
	asmc64 $@.asm
	$@
	@pause

clean:
	del heapwalk.exe
	del heapwalk.obj

vs:
	project -p heapwalk
