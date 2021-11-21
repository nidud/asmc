InstructionTiming.exe:
    asmc64 $*.asm
    linkw system con_64 file $*
    $@ > InstructionTiming.txt
    type InstructionTiming.txt
    pause

