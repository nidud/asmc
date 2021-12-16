# Makefile for Asmc Linux using GCC

AFLAGS = -nologo -nolib -Zp4 -elf -Cs -Isrc/inc -I../../include
ifdef X64
AFLAGS += -D__ASMC64__
BIN = asmc64
else
BIN = asmc
endif

all: $(BIN) clean

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
