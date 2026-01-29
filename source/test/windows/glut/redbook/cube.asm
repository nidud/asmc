;
; https://www.opengl.org/archives/resources/code/samples/redbook/cube.asm
;
include GL/glut.inc

.code

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glShadeModel(GL_FLAT)
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)
   glColor3f(1.0, 1.0, 1.0)
   glLoadIdentity()

   gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
   glScalef(1.0, 2.0, 1.0)
   glutWireCube(1.0)
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport (0, 0, ecx, edx)
   glMatrixMode (GL_PROJECTION)
   glLoadIdentity()
   glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0)
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
