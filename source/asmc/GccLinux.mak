# Makefile for Asmc Linux using GCC

AFLAGS = -nologo -nolib -Zp4 -elf -Cs -Iinc -I../../include
ifdef ASMC64
AFLAGS += -DASMC64
BIN = asmc64
else
BIN = asmc
endif

all: $(BIN) clean

OBJS =	x86/asmc.o \
	x86/asmerr.o \
	x86/assemble.o \
	x86/assert.o \
	x86/assume.o \
	x86/backptch.o \
	x86/bin.o \
	x86/branch.o \
	x86/class.o \
	x86/cmdline.o \
	x86/codegen.o \
	x86/coff.o \
	x86/com.o \
	x86/condasm.o \
	x86/context.o \
	x86/cpumodel.o \
	x86/data.o \
	x86/dbgcv.o \
	x86/directiv.o \
	x86/elf.o \
	x86/end.o \
	x86/enum.o \
	x86/equate.o \
	x86/expans.o \
	x86/expreval.o \
	x86/extern.o \
	x86/fastcall.o \
	x86/fastpass.o \
	x86/fixup.o \
	x86/for.o \
	x86/fpfixup.o \
	x86/hll.o \
	x86/Indirection.o \
	x86/input.o \
	x86/invoke.o \
	x86/label.o \
	x86/linnum.o \
	x86/listing.o \
	x86/logo.o \
	x86/loop.o \
	x86/lqueue.o \
	x86/ltype.o \
	x86/macro.o \
	x86/mangle.o \
	x86/mem2mem.o \
	x86/memalloc.o \
	x86/namespace.o \
	x86/new.o \
	x86/omf.o \
	x86/omffixup.o \
	x86/omfint.o \
	x86/operator.o \
	x86/option.o \
	x86/parser.o \
	x86/posndir.o \
	x86/pragma.o \
	x86/preproc.o \
	x86/proc.o \
	x86/qfloat.o \
	x86/reswords.o \
	x86/return.o \
	x86/safeseh.o \
	x86/segment.o \
	x86/simsegm.o \
	x86/string.o \
	x86/switch.o \
	x86/symbols.o \
	x86/tokenize.o \
	x86/typeid.o \
	x86/types.o \
	x86/undef.o

.SUFFIXES:
.SUFFIXES: .asm .o

.asm.o:
	../../bin/asmc $(AFLAGS) -Fo $*.o $<

$(BIN): $(OBJS)
	gcc -m32 -o $@ $^

clean:
	rm -f $(OBJS)

install:
	install $(BIN) /usr/local/bin
