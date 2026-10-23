;
; https://www.opengl.org/archives/resources/code/samples/redbook/light.c
;
include GL/glut.inc

.code

init proc

   .data
   mat_specular     GLfloat 1.0, 1.0, 1.0, 1.0
   mat_shininess    GLfloat 50.0
   light_position   GLfloat 1.0, 1.0, 1.0, 0.0
   .code

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glShadeModel(GL_SMOOTH)

   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, &mat_shininess)
   glLightfv(GL_LIGHT0, GL_POSITION, &light_position)

   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   glEnable(GL_DEPTH_TEST)
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
   glutSolidSphere(1.0, 20, 16)
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
      movsd xmm3,xmm1
      mulsd xmm2,-1.5
      mulsd xmm3,1.5
      glOrtho(-1.5, 1.5, xmm2, xmm3, -10.0, 10.0)
   .else
      divsd xmm0,xmm1
      movsd xmm1,xmm0
      mulsd xmm0,-1.5
      mulsd xmm1,1.5
      glOrtho(xmm0, xmm1, -1.5, 1.5, -10.0, 10.0)
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
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_DEPTH)
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
