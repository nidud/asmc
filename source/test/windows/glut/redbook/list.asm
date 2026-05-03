;
; https://www.opengl.org/archives/resources/code/samples/redbook/list.c
;
include GL/glut.inc

.data
listName GLuint 0

.code

init proc

   mov listName,glGenLists(1)
   glNewList(listName, GL_COMPILE)
      glColor3f(1.0, 0.0, 0.0)
      glBegin(GL_TRIANGLES)
      glVertex2f(0.0, 0.0)
      glVertex2f(1.0, 0.0)
      glVertex2f(0.0, 1.0)
      glEnd()
      glTranslatef(1.5, 0.0, 0.0)
   glEndList()
   glShadeModel(GL_FLAT)
   ret

init endp

drawLine proc

   glBegin(GL_LINES)
   glVertex2f(0.0, 0.5)
   glVertex2f(15.0, 0.5)
   glEnd()
   ret

drawLine endp

display proc uses rsi

   glClear(GL_COLOR_BUFFER_BIT)
   glColor3f(0.0, 1.0, 0.0)
   .for (esi = 0: esi < 10: esi++)
      glCallList(listName)
   .endf
   drawLine()
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm0,w
   cvtsi2sd xmm1,h
   .if w <= h
      divsd xmm1,xmm0
      movsd xmm2,xmm1
      mulsd xmm2,-0.5
      mulsd xmm1,1.5
      gluOrtho2D(0.0, 2.0, xmm2, xmm1)
   .else
      divsd xmm0,xmm1
      mulsd xmm0,2.0
      gluOrtho2D(0.0, xmm0, -0.5, 1.5)
   .endif
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
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
   glutInitWindowSize(650, 50)
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
