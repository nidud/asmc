set debuginfod enabled on
set disassembly-flavor intel
tui new-layout mylayout regs 1 {-horizontal src 1 asm 1} 2 status 0 cmd 1
layout mylayout
break main
run
