set debuginfod enabled on
set disassembly-flavor intel
tui new-layout layout1 {-horizontal { regs 1 asm 1 cmd 1 } 2 src 2 } 4 status 0
tui new-layout layout2 {-horizontal src 30 { regs 1 asm 1 cmd 1 } 50 } 80 status 0
layout layout1
break main
run
