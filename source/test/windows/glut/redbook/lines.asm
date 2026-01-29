;
; https://www.opengl.org/archives/resources/code/samples/redbook/lines.c
;
include GL/glut.inc

drawOneLine macro x1, y1, x2, y2
   glBegin(GL_LINES)
   glVertex2f((x1),(y1))
   glVertex2f((x2),(y2))
   exitm<glEnd()>
   endm

.code

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glShadeModel(GL_FLAT)
   ret

init endp

display proc uses rsi rdi

   glClear(GL_COLOR_BUFFER_BIT)
   glColor3f(1.0, 1.0, 1.0)
   glEnable(GL_LINE_STIPPLE)

   glLineStipple(1, 0x0101)
   drawOneLine(50.0, 125.0, 150.0, 125.0)
   glLineStipple(1, 0x00FF)
   drawOneLine(150.0, 125.0, 250.0, 125.0)
   glLineStipple(1, 0x1C47)
   drawOneLine(250.0, 125.0, 350.0, 125.0)

   glLineWidth(5.0)
   glLineStipple(1, 0x0101)
   drawOneLine(50.0, 100.0, 150.0, 100.0)
   glLineStipple(1, 0x00FF)
   drawOneLine(150.0, 100.0, 250.0, 100.0)
   glLineStipple(1, 0x1C47)
   drawOneLine(250.0, 100.0, 350.0, 100.0)
   glLineWidth(1.0)

   glLineStipple(1, 0x1C47)
   glBegin(GL_LINE_STRIP)
   .for (esi = 0: esi < 7: esi++)
      cvtsi2ss xmm0,esi
      mulss xmm0,50.0
      addss xmm0,50.0
      glVertex2f(xmm0, 75.0)
   .endf
   glEnd()

   .for (esi = 0: esi < 6: esi++)
      cvtsi2ss xmm0,esi
      mulss xmm0,50.0
      addss xmm0,50.0
      lea rax,[rsi+1]
      cvtsi2ss xmm2,eax
      mulss xmm2,50.0
      addss xmm2,50.0
      drawOneLine(xmm0, 50.0, xmm2, 50.0)
   .endf

   glLineStipple(5, 0x1C47)
   drawOneLine(50.0, 25.0, 350.0, 25.0)

   glDisable(GL_LINE_STIPPLE)
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm3,h
   gluOrtho2D(0.0, xmm1, 0.0, xmm3)
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

    .if key == 27
        exit(0)
    .endif
    ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
   glutInitWindowSize(400, 150)
   glutInitWindowPosition(100, 100)
   mov rcx,argv
   glutCreateWindow([rcx])
   init()
   glutReshapeFunc(&reshape)
   glutDisplayFunc(&display)
   glutKeyboardFunc(&keyboard)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
