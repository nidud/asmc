;
; https://www.opengl.org/archives/resources/code/samples/redbook/double.c
;
include GL/glut.inc

.data
spin GLfloat 0.0

.code
display proc

   glClear(GL_COLOR_BUFFER_BIT)
   glPushMatrix()
   glRotatef(spin, 0.0, 0.0, 1.0)
   glColor3f(1.0, 1.0, 1.0)
   glRectf(-25.0, -25.0, 25.0, 25.0)
   glPopMatrix()

   glutSwapBuffers()
   ret

display endp

spinDisplay proc

    movss xmm0,spin
    addss xmm0,2.0
    comiss xmm0,360.0
    .ifa
        subss xmm0,360.0
    .endif
    movss spin,xmm0
    glutPostRedisplay();
    ret

spinDisplay endp

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glShadeModel(GL_FLAT)
   ret

init endp

reshape proc w:int_t, h:int_t

   glViewport (0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   ret

reshape endp

mouse proc button:int_t, state:int_t, x:int_t, y:int_t

   .switch ecx
      .case GLUT_LEFT_BUTTON
         .if edx == GLUT_DOWN
            glutIdleFunc(spinDisplay)
         .endif
         .endc
      .case GLUT_MIDDLE_BUTTON
      .case GLUT_RIGHT_BUTTON
         .if edx == GLUT_DOWN
            glutIdleFunc(NULL)
         .endif
         .endc
   .endsw
   ret

mouse endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_DOUBLE or GLUT_RGB)
   glutInitWindowSize(250, 250)
   glutInitWindowPosition(100, 100)
   mov rcx,argv
   glutCreateWindow([rcx])
   init()
   glutDisplayFunc(&display)
   glutReshapeFunc(&reshape)
   glutMouseFunc(&mouse)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
