targets = \
	acos.asm \
	acosf.asm \
	asin.asm \
	asinf.asm \
	atan.asm \
	atan2.asm \
	atan2f.asm \
	atanf.asm \
	ceil.asm \
	ceilf.asm \
	cos.asm \
	cosf.asm \
	exp.asm \
	exp2.asm \
	exp2f.asm \
	expf.asm \
	floor.asm \
	floorf.asm \
	fmod.asm \
	fmodf.asm \
	log.asm \
	log10.asm \
	log10f.asm \
	logf.asm \
	pow.asm \
	powf.asm \
	round.asm \
	roundf.asm \
	sin.asm \
	sinf.asm \
	sqrt.asm \
	sqrtf.asm \
	tan.asm \
	tanf.asm

.asm.obj:
	echo $*: >> result.txt
	asmc64 -q $*.asm
ifdef YACC
	./$* >> result.txt
	@pause
	@rm -f $*.o
	@rm -f $*
else
	$* >> result.txt
	asmc64 -q -pe $*.asm
	$* >> result.txt
	asmc -q -coff $*.asm
	$* >> result.txt
	asmc -q -pe $*.asm
	$* >> result.txt
	del $*.obj
	del $*.exe
endif

build: $(targets)
