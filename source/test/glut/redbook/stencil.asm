;
; https://www.opengl.org/archives/resources/code/samples/redbook/stencil.c
;
include GL/glut.inc

YELLOWMAT equ 1
BLUEMAT   equ 2

.code

init proc

   .data
   align 4
   yellow_diffuse   GLfloat 0.7, 0.7, 0.0, 1.0
   yellow_specular  GLfloat 1.0, 1.0, 1.0, 1.0
   blue_diffuse     GLfloat 0.1, 0.1, 0.7, 1.0
   blue_specular    GLfloat 0.1, 1.0, 1.0, 1.0
   position_one     GLfloat 1.0, 1.0, 1.0, 0.0

   .code

   glNewList(YELLOWMAT, GL_COMPILE)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &yellow_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &yellow_specular)
   glMaterialf(GL_FRONT, GL_SHININESS, 64.0)
   glEndList()

   glNewList(BLUEMAT, GL_COMPILE)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &blue_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &blue_specular)
   glMaterialf(GL_FRONT, GL_SHININESS, 45.0)
   glEndList()

   glLightfv(GL_LIGHT0, GL_POSITION, &position_one)

   glEnable(GL_LIGHT0)
   glEnable(GL_LIGHTING)
   glEnable(GL_DEPTH_TEST)

   glClearStencil(0x0)
   glEnable(GL_STENCIL_TEST)
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)

   glStencilFunc(GL_EQUAL, 0x1, 0x1)
   glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP)
   glCallList(BLUEMAT)
   glutSolidSphere(0.5, 15, 15)

   glStencilFunc(GL_NOTEQUAL, 0x1, 0x1)
   glPushMatrix()
      glRotatef(45.0, 0.0, 0.0, 1.0)
      glRotatef(45.0, 0.0, 1.0, 0.0)
      glCallList(YELLOWMAT)
      glutSolidTorus(0.275, 0.85, 15, 15)
      glPushMatrix()
         glRotatef(90.0, 1.0, 0.0, 0.0)
         glutSolidTorus(0.275, 0.85, 15, 15)
      glPopMatrix()
   glPopMatrix()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)

   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm0,w
   cvtsi2sd xmm1,h
   .if (w <= h)
      divsd xmm1,xmm0
      movsd xmm2,xmm1
      movsd xmm3,xmm1
      mulsd xmm2,-3.0
      mulsd xmm3,3.0
      gluOrtho2D(-3.0, 3.0, xmm2, xmm3)
   .else
      divsd xmm0,xmm1
      movsd xmm1,xmm0
      mulsd xmm0,-3.0
      mulsd xmm1,3.0
      gluOrtho2D(xmm0, xmm1, -3.0, 3.0)
   .endif
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()

   glClear(GL_STENCIL_BUFFER_BIT)
   glStencilFunc(GL_ALWAYS, 0x1, 0x1)
   glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE)
   glBegin(GL_QUADS)
      glVertex2f(-1.0, 0.0)
      glVertex2f(0.0, 1.0)
      glVertex2f(1.0, 0.0)
      glVertex2f(0.0, -1.0)
   glEnd()

   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm0,h
   divsd xmm1,xmm0
   gluPerspective(45.0, xmm1, 3.0, 7.0)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   glTranslatef(0.0, 0.0, -5.0)
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
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_DEPTH or GLUT_STENCIL)
   glutInitWindowSize(400, 400)
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
