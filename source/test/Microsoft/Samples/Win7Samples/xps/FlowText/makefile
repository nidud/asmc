
FlowTextMain.exe:
    asmc64 -q -ws -Cs FlowTextMain.asm
    asmc64 -q -ws -Cs LayoutToCanvasBuilder.asm
    linkw system con_64W file FlowTextMain, LayoutToCanvasBuilder
    $@
    del *.obj
