.SUFFIXES: .asm .o

targets = \
	acos.o \
	acosf.o \
	asin.o \
	asinf.o \
	atan.o \
	atan2.o \
	atan2f.o \
	atanf.o \
	ceil.o \
	ceilf.o \
	cos.o \
	cosf.o \
	exp.o \
	exp2.o \
	exp2f.o \
	expf.o \
	floor.o \
	floorf.o \
	fmod.o \
	fmodf.o \
	log.o \
	log10.o \
	log10f.o \
	logf.o \
	pow.o \
	powf.o \
	round.o \
	roundf.o \
	sin.o \
	sinf.o \
	sqrt.o \
	sqrtf.o \
	tan.o \
	tanf.o

.asm.o:
	echo $*: >> result.txt
	asmc64 -q -MT $<
ifdef YACC
	./$* >> result.txt
	asmc64 -q -MD $<
	./$* >> result.txt
	@rm -f $*.o
	@rm -f $*
else
	$* >> result.txt
	asmc64 -q -pe $<
	$* >> result.txt
	asmc -q -coff $<
	$* >> result.txt
	asmc -q -pe $<
	$* >> result.txt
	del $*.obj
	del $*.exe
endif

build: $(targets)
