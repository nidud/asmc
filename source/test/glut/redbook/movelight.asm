;
; https://www.opengl.org/archives/resources/code/samples/redbook/movelight.c
;
include GL/glut.inc

.data
spin int_t 0

.code

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glShadeModel(GL_SMOOTH)
   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   glEnable(GL_DEPTH_TEST)
   ret

init endp

display proc

   .data
   position GLfloat 0.0, 0.0, 1.5, 1.0

   .code

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
   glPushMatrix()
   gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)

   glPushMatrix()
   cvtsi2sd xmm0,spin
   glRotated(xmm0, 1.0, 0.0, 0.0)
   glLightfv(GL_LIGHT0, GL_POSITION, &position)

   glTranslated(0.0, 0.0, 1.5)
   glDisable(GL_LIGHTING)
   glColor3f(0.0, 1.0, 1.0)
   glutWireCube(0.1)
   glEnable(GL_LIGHTING)
   glPopMatrix()

   glutSolidTorus(0.275, 0.85, 8, 15)
   glPopMatrix()
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm0,h
   divsd xmm1,xmm0
   gluPerspective(40.0, xmm1, 1.0, 20.0)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   ret

reshape endp

mouse proc button:int_t, state:int_t, x:int_t, y:int_t

   .switch ecx
      .case GLUT_LEFT_BUTTON
         .if edx == GLUT_DOWN
            xor edx,edx
            mov eax,spin
            add eax,30
            mov ecx,360
            div ecx
            mov spin,edx
            glutPostRedisplay()
         .endif
         .endc
   .endsw
   ret

mouse endp

keyboard proc key:byte, x:int_t, y:int_t

    .if key == 27
        exit(0)
    .endif
    ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_DEPTH)
   glutInitWindowSize(500, 500)
   glutInitWindowPosition(100, 100)
   mov rcx,argv
   glutCreateWindow([rcx])
   init()
   glutReshapeFunc(&reshape)
   glutDisplayFunc(&display)
   glutMouseFunc(&mouse)
   glutKeyboardFunc(&keyboard)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
