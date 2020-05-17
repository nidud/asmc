;
; https://www.opengl.org/archives/resources/code/samples/redbook/alpha.c
;
include GL/glut.inc

.data
leftFirst int_t GL_TRUE

.code

init proc

   glEnable(GL_BLEND)
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
   glShadeModel(GL_FLAT)
   glClearColor(0.0, 0.0, 0.0, 0.0)
   ret

init endp

drawLeftTriangle proc

   glBegin (GL_TRIANGLES);
      glColor4f(1.0, 1.0, 0.0, 0.75);
      glVertex3f(0.1, 0.9, 0.0);
      glVertex3f(0.1, 0.1, 0.0);
      glVertex3f(0.7, 0.5, 0.0);
   glEnd();
   ret

drawLeftTriangle endp

drawRightTriangle proc

   glBegin (GL_TRIANGLES);
      glColor4f(0.0, 1.0, 1.0, 0.75);
      glVertex3f(0.9, 0.9, 0.0);
      glVertex3f(0.3, 0.5, 0.0);
      glVertex3f(0.9, 0.1, 0.0);
   glEnd();
   ret

drawRightTriangle endp

display proc

   glClear(GL_COLOR_BUFFER_BIT);

   .if leftFirst
      drawLeftTriangle();
      drawRightTriangle();
   .else
      drawRightTriangle();
      drawLeftTriangle();
   .endif

   glFlush();
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity();

   cvtsi2ss xmm0,h
   cvtsi2ss xmm1,w

   .if w <= h

      mulss xmm0,1.0
      divss xmm0,xmm1
      cvtss2sd xmm3,xmm0
      gluOrtho2D(0.0, 1.0, 0.0, xmm3)

   .else
      mulss xmm1,1.0
      divss xmm1,xmm0
      cvtss2sd xmm1,xmm1
      gluOrtho2D (0.0, xmm1, 0.0, 1.0);
   .endif
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

   .switch cl
      .case 't'
      .case 'T'
	 xor leftFirst,1
	 glutPostRedisplay()
	 .endc
      .case 27
	 exit(0)
	 .endc
      .default
	 .endc
   .endsw
   ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
   glutInitWindowSize(200, 200)
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
