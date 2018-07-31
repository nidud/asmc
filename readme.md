# Asmc Macro Assembler

   Asmc is a MASM compatible assembler with support for OMF/COFF/ELF[64]
   in addition to BIN, Windows PE, and DOS MZ format.

   It includes instructions up to AVX2 and AVX512.

## Requirements

   ASMC.EXE should run on any 32- or 64-bit Windows.

   Memory requirements depend on the source which is assembled. The source
   itself is not kept in memory, but the symbol table is, and this table
   can easily grow to several MBs if huge amounts of equates are defined.
