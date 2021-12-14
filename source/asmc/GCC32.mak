
AFLAGS = -nologo -nolib -Zp4 -elf -Cs -I../../include -Isrc/inc
ifdef X64
AFLAGS += -D__ASMC64__
BIN = asmc64
else
BIN = asmc
endif

OBJS =	src/asmc.o \
	src/asmerr.o \
	src/assemble.o \
	src/assert.o \
	src/assume.o \
	src/backptch.o \
	src/bin.o \
	src/branch.o \
	src/class.o \
	src/cmdline.o \
	src/codegen.o \
	src/coff.o \
	src/com.o \
	src/condasm.o \
	src/context.o \
	src/cpumodel.o \
	src/data.o \
	src/dbgcv.o \
	src/directiv.o \
	src/elf.o \
	src/end.o \
	src/enum.o \
	src/equate.o \
	src/expans.o \
	src/expreval.o \
	src/extern.o \
	src/fastcall.o \
	src/fastpass.o \
	src/fixup.o \
	src/for.o \
	src/fpfixup.o \
	src/hll.o \
	src/Indirection.o \
	src/input.o \
	src/invoke.o \
	src/label.o \
	src/linnum.o \
	src/listing.o \
	src/logo.o \
	src/loop.o \
	src/lqueue.o \
	src/ltype.o \
	src/macro.o \
	src/mangle.o \
	src/mem2mem.o \
	src/memalloc.o \
	src/namespace.o \
	src/new.o \
	src/omf.o \
	src/omffixup.o \
	src/omfint.o \
	src/operator.o \
	src/option.o \
	src/parser.o \
	src/posndir.o \
	src/pragma.o \
	src/preproc.o \
	src/proc.o \
	src/qfloat.o \
	src/reswords.o \
	src/return.o \
	src/safeseh.o \
	src/segment.o \
	src/simsegm.o \
	src/string.o \
	src/switch.o \
	src/symbols.o \
	src/tokenize.o \
	src/typeid.o \
	src/types.o \
	src/undef.o

LOBJS = asmc.o \
	asmerr.o \
	assemble.o \
	assert.o \
	assume.o \
	backptch.o \
	bin.o \
	branch.o \
	class.o \
	cmdline.o \
	codegen.o \
	coff.o \
	com.o \
	condasm.o \
	context.o \
	cpumodel.o \
	data.o \
	dbgcv.o \
	directiv.o \
	elf.o \
	end.o \
	enum.o \
	equate.o \
	expans.o \
	expreval.o \
	extern.o \
	fastcall.o \
	fastpass.o \
	fixup.o \
	for.o \
	fpfixup.o \
	hll.o \
	Indirection.o \
	input.o \
	invoke.o \
	label.o \
	linnum.o \
	listing.o \
	logo.o \
	loop.o \
	lqueue.o \
	ltype.o \
	macro.o \
	mangle.o \
	mem2mem.o \
	memalloc.o \
	namespace.o \
	new.o \
	omf.o \
	omffixup.o \
	omfint.o \
	operator.o \
	option.o \
	parser.o \
	posndir.o \
	pragma.o \
	preproc.o \
	proc.o \
	qfloat.o \
	reswords.o \
	return.o \
	safeseh.o \
	segment.o \
	simsegm.o \
	string.o \
	switch.o \
	symbols.o \
	tokenize.o \
	typeid.o \
	types.o \
	undef.o

.SUFFIXES:
.SUFFIXES: .asm .o

.asm.o:
	../../bin/asmc $(AFLAGS) $<

$(BIN): $(OBJS)
	gcc -o $@ $(LOBJS)

