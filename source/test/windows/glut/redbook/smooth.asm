;
; https://www.opengl.org/archives/resources/code/samples/redbook/smooth.c
;
include GL/glut.inc

.code

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glShadeModel(GL_SMOOTH)
   ret

init endp

triangle proc

   glBegin(GL_TRIANGLES)
   glColor3f(1.0, 0.0, 0.0)
   glVertex2f(5.0, 5.0)
   glColor3f(0.0, 1.0, 0.0)
   glVertex2f(25.0, 5.0)
   glColor3f(0.0, 0.0, 1.0)
   glVertex2f(5.0, 25.0)
   glEnd()
   ret

triangle endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)
   triangle()
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm0,w
   cvtsi2sd xmm1,h
   .if w <= h
      movsd xmm3,xmm1
      divsd xmm3,xmm0
      mulsd xmm3,30.0
      gluOrtho2D(0.0, 30.0, 0.0, xmm3)
   .else
      divsd xmm0,xmm1
      movsd xmm1,xmm0
      mulsd xmm1,30.0
      gluOrtho2D(0.0, xmm1, 0.0, 30.0)
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
