;
; https://www.opengl.org/archives/resources/code/samples/redbook/model.c
;
include GL/glut.inc

.code

init proc

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
   ret

init endp

draw_triangle proc

   glBegin(GL_LINE_LOOP)
   glVertex2f(0.0, 25.0)
   glVertex2f(25.0, -25.0)
   glVertex2f(-25.0, -25.0)
   glEnd()
   ret

draw_triangle endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)
   glColor3f(1.0, 1.0, 1.0)

   glLoadIdentity()
   glColor3f(1.0, 1.0, 1.0)
   draw_triangle()

   glEnable(GL_LINE_STIPPLE)
   glLineStipple(1, 0xF0F0)
   glLoadIdentity()
   glTranslatef(-20.0, 0.0, 0.0)
   draw_triangle()

   glLineStipple(1, 0xF00F)
   glLoadIdentity()
   glScalef(1.5, 0.5, 1.0)
   draw_triangle()

   glLineStipple(1, 0x8888)
   glLoadIdentity()
   glRotatef(90.0, 0.0, 0.0, 1.0)
   draw_triangle()
   glDisable(GL_LINE_STIPPLE)

   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport (0, 0, ecx, edx)
   glMatrixMode (GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm0,w
   cvtsi2sd xmm1,h
   .if w <= h
      divsd xmm1,xmm0
      movsd xmm2,xmm1
      movsd xmm3,xmm1
      mulsd xmm2,-50.0
      mulsd xmm3,50.0
      glOrtho(-50.0, 50.0, xmm2, xmm3, -1.0, 1.0);
   .else
      divsd xmm0,xmm1
      movsd xmm1,xmm0
      mulsd xmm0,-50.0
      mulsd xmm1,50.0
      glOrtho(xmm0, xmm1, -50.0, 50.0, -1.0, 1.0)
   .endif
   glMatrixMode(GL_MODELVIEW)
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
   glutInitWindowSize(500, 500)
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
