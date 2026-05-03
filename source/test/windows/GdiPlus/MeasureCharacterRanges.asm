;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-measurecharacterranges
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"MeasureCharacterRanges">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

    ;; Brushes and pens used for drawing and painting

   .new blueBrush:SolidBrush(Blue)  ; Color(255, 0, 0, 255)
   .new redBrush:SolidBrush(Red)    ; Color(100, 255, 0, 0)
   .new blackPen:Pen(White)         ; Color(255, 0, 0, 0)

    ;; Layout rectangles used for drawing strings

   .new layoutRect_A:RectF( 20.0, 20.0, 130.0, 130.0)
   .new layoutRect_B:RectF(160.0, 20.0, 165.0, 130.0)
   .new layoutRect_C:RectF(335.0, 20.0, 165.0, 130.0)

    ;; Three different ranges of character positions within the string

   .new c3:CharacterRange(30, 15)
   .new c2:CharacterRange(15, 2)
   .new charRanges:CharacterRange(3, 5)

    ;; Font and string format to apply to string when drawing

   .new myFont:Font(L"Times New Roman", 16.0)
   .new strFormat:StringFormat()

    ;; Other variables

   .new pCharRangeRegions:ptr Region    ;; pointer to CharacterRange regions
   .new i:SINT                          ;; loop counter
   .new count:SINT                      ;; number of character ranges set
   .new string:ptr word

    mov string,&@CStr(L"The quick, brown fox easily jumps over the lazy dog.")

    ;; Set three ranges of character positions.

    strFormat.SetMeasurableCharacterRanges(3, &charRanges)

    ;; Get the number of ranges that have been set, and allocate memory to
    ;; store the regions that correspond to the ranges.

    mov count,strFormat.GetMeasurableCharacterRangeCount()
    imul ecx,eax,Region
    mov pCharRangeRegions,GdipAlloc(rcx)

    .for ( i = 0: i < count: i++)
        imul ecx,i,Region
        add  rcx,pCharRangeRegions
        GdipCreateRegion(rcx)
    .endf

    ;; Get the regions that correspond to the ranges within the string when
    ;; layout rectangle A is used. Then draw the string, and show the regions.
    g.MeasureCharacterRanges(string, -1, &myFont, layoutRect_A, &strFormat, count, pCharRangeRegions)
    g.DrawString(string, -1, &myFont, layoutRect_A, &strFormat, &blueBrush)
    g.DrawRectangle(&blackPen, layoutRect_A)

    .for ( i = 0: i < count: i++)
        imul eax,i,Region
        add  rax,pCharRangeRegions
        g.FillRegion(&redBrush, rax)
    .endf

    ;; Get the regions that correspond to the ranges within the string when
    ;; layout rectangle B is used. Then draw the string, and show the regions.

    g.MeasureCharacterRanges(string, -1, &myFont, layoutRect_B, &strFormat, count, pCharRangeRegions)
    g.DrawString(string, -1, &myFont, layoutRect_B, &strFormat, &blueBrush)
    g.DrawRectangle(&blackPen, layoutRect_B)

    .for ( i = 0: i < count: i++ )
        imul eax,i,Region
        add  rax,pCharRangeRegions
        g.FillRegion(&redBrush, rax)
    .endf

    ;; Get the regions that correspond to the ranges within the string when
    ;; layout rectangle C is used. Set trailing spaces to be included in the
    ;; regions. Then draw the string, and show the regions.

    strFormat.SetFormatFlags(StringFormatFlagsMeasureTrailingSpaces)

    g.MeasureCharacterRanges(string, -1, &myFont, layoutRect_C, &strFormat, count, pCharRangeRegions)
    g.DrawString(string, -1, &myFont, layoutRect_C, &strFormat, &blueBrush)
    g.DrawRectangle(&blackPen, layoutRect_C)

    .for ( i = 0: i < count: i++ )
        imul eax,i,Region
        add  rax,pCharRangeRegions
        g.FillRegion(&redBrush, rax)
    .endf

    ;; Delete memory for the range regions.

    GdipFree(pCharRangeRegions)
    g.Release()

    ret

OnPaint endp

include Graphics.inc

