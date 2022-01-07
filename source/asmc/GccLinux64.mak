# Makefile for Asmc Linux using GCC

AFLAGS = -nologo -nolib -Zp8 -elf64 -Cs -Iinc -I../../include
ifdef X64
AFLAGS += -DASMC64
BIN = asmc64
else
BIN = asmc
endif

all: $(BIN) clean

OBJS =	x64/asmc.o \
	x64/asmerr.o \
	x64/assemble.o \
	x64/assert.o \
	x64/assume.o \
	x64/backptch.o \
	x64/bin.o \
	x64/branch.o \
	x64/class.o \
	x64/cmdline.o \
	x64/codegen.o \
	x64/coff.o \
	x64/com.o \
	x64/condasm.o \
	x64/context.o \
	x64/cpumodel.o \
	x64/data.o \
	x64/dbgcv.o \
	x64/directiv.o \
	x64/elf.o \
	x64/end.o \
	x64/enum.o \
	x64/equate.o \
	x64/expans.o \
	x64/expreval.o \
	x64/extern.o \
	x64/fastcall.o \
	x64/fastpass.o \
	x64/fixup.o \
	x64/for.o \
	x64/fpfixup.o \
	x64/hll.o \
	x64/Indirection.o \
	x64/input.o \
	x64/invoke.o \
	x64/label.o \
	x64/linnum.o \
	x64/listing.o \
	x64/logo.o \
	x64/loop.o \
	x64/lqueue.o \
	x64/ltype.o \
	x64/macro.o \
	x64/mangle.o \
	x64/mem2mem.o \
	x64/memalloc.o \
	x64/namespace.o \
	x64/new.o \
	x64/omf.o \
	x64/omffixup.o \
	x64/omfint.o \
	x64/operator.o \
	x64/option.o \
	x64/parser.o \
	x64/posndir.o \
	x64/pragma.o \
	x64/preproc.o \
	x64/proc.o \
	x64/qfloat.o \
	x64/reswords.o \
	x64/return.o \
	x64/safeseh.o \
	x64/segment.o \
	x64/simsegm.o \
	x64/string.o \
	x64/switch.o \
	x64/symbols.o \
	x64/tokenize.o \
	x64/typeid.o \
	x64/types.o \
	x64/undef.o

.SUFFIXES:
.SUFFIXES: .asm .o

.asm.o:
	../../bin/asmc $(AFLAGS) -Fo $*.o $<

$(BIN): $(OBJS)
	gcc -o $@ -z --execstack -z --stacksize=0x20000 $^

clean:
	rm -f $(OBJS)

install:
	install $(BIN) /usr/local/bin
