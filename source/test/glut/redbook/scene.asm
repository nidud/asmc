;
; https://www.opengl.org/archives/resources/code/samples/redbook/scene.c
;
include GL/glut.inc

.code

init proc

   .data
   light_ambient  GLfloat 0.0, 0.0, 0.0, 1.0
   light_diffuse  GLfloat 1.0, 1.0, 1.0, 1.0
   light_specular GLfloat 1.0, 1.0, 1.0, 1.0
   light_position GLfloat 1.0, 1.0, 1.0, 0.0

   .code
   glLightfv(GL_LIGHT0, GL_AMBIENT, &light_ambient)
   glLightfv(GL_LIGHT0, GL_DIFFUSE, &light_diffuse)
   glLightfv(GL_LIGHT0, GL_SPECULAR, &light_specular)
   glLightfv(GL_LIGHT0, GL_POSITION, &light_position)

   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   glEnable(GL_DEPTH_TEST)
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)

   glPushMatrix()
   glRotatef(20.0, 1.0, 0.0, 0.0)

   glPushMatrix()
   glTranslatef(-0.75, 0.5, 0.0)
   glRotatef(90.0, 1.0, 0.0, 0.0)
   glutSolidTorus(0.275, 0.85, 15, 15)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(-0.75, -0.5, 0.0)
   glRotatef(270.0, 1.0, 0.0, 0.0);
   glutSolidCone(1.0, 2.0, 15, 15)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(0.75, 0.0, -1.0)
   glutSolidSphere(1.0, 15, 15)
   glPopMatrix()

   glPopMatrix()
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm0,h
   .if w <= h
      divsd xmm1,xmm0
      movsd xmm2,xmm1
      movsd xmm3,xmm1
      mulsd xmm2,-2.5
      mulsd xmm3,2.5
      glOrtho(-2.5, 2.5, xmm2, xmm3, -10.0, 10.0)
   .else
      divsd xmm0,xmm1
      movsd xmm1,xmm0
      mulsd xmm0,-2.5
      mulsd xmm1,2.5
      glOrtho(xmm0, xmm1, -2.5, 2.5, -10.0, 10.0)
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
