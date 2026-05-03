;
; https://www.opengl.org/archives/resources/code/samples/redbook/material.c
;
include GL/glut.inc

.code

init proc

   .data
   ambient          GLfloat 0.0, 0.0, 0.0, 1.0
   diffuse          GLfloat 1.0, 1.0, 1.0, 1.0
   specular         GLfloat 1.0, 1.0, 1.0, 1.0
   position         GLfloat 0.0, 3.0, 2.0, 0.0
   lmodel_ambient   GLfloat 0.4, 0.4, 0.4, 1.0
   local_view       GLfloat 0.0
   .code

   glClearColor(0.0, 0.1, 0.1, 0.0)
   glEnable(GL_DEPTH_TEST)
   glShadeModel(GL_SMOOTH)

   glLightfv(GL_LIGHT0, GL_AMBIENT, &ambient)
   glLightfv(GL_LIGHT0, GL_DIFFUSE, &diffuse)
   glLightfv(GL_LIGHT0, GL_POSITION, &position)
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &lmodel_ambient)
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, &local_view)

   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   ret

init endp

display proc

   .data
   no_mat           GLfloat 0.0, 0.0, 0.0, 1.0
   mat_ambient      GLfloat 0.7, 0.7, 0.7, 1.0
   mat_ambient_color GLfloat 0.8, 0.8, 0.2, 1.0
   mat_diffuse      GLfloat 0.1, 0.5, 0.8, 1.0
   mat_specular     GLfloat 1.0, 1.0, 1.0, 1.0
   no_shininess     GLfloat 0.0
   low_shininess    GLfloat 5.0
   high_shininess   GLfloat 100.0
   mat_emission     GLfloat 0.3, 0.2, 0.2, 0.0
   .code

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)

   glPushMatrix()
   glTranslatef(-3.75, 3.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &no_mat)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &no_mat)
   glMaterialfv(GL_FRONT, GL_SHININESS, &no_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &no_mat)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(-1.25, 3.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &no_mat)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, &low_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &no_mat)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(1.25, 3.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &no_mat)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, &high_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, &no_mat)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(3.75, 3.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &no_mat)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &no_mat)
   glMaterialfv(GL_FRONT, GL_SHININESS, &no_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &mat_emission)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(-3.75, 0.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &no_mat)
   glMaterialfv(GL_FRONT, GL_SHININESS, &no_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &no_mat)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(-1.25, 0.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, &low_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &no_mat)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(1.25, 0.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, &high_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &no_mat)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(3.75, 0.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &no_mat)
   glMaterialfv(GL_FRONT, GL_SHININESS, &no_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &mat_emission)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix();

   glPushMatrix()
   glTranslatef(-3.75, -3.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient_color)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &no_mat)
   glMaterialfv(GL_FRONT, GL_SHININESS, &no_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &no_mat)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glPushMatrix();
   glTranslatef(-1.25, -3.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient_color)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, &low_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &no_mat)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(1.25, -3.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient_color)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, &high_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &no_mat)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(3.75, -3.0, 0.0)
   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient_color)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &no_mat)
   glMaterialfv(GL_FRONT, GL_SHININESS, &no_shininess)
   glMaterialfv(GL_FRONT, GL_EMISSION, &mat_emission)
   glutSolidSphere(1.0, 16, 16)
   glPopMatrix()

   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   mov eax,h
   shl eax,1
   cvtsi2sd xmm0,w
   cvtsi2sd xmm1,eax
   .if w <= eax
      divsd xmm1,xmm0
      movsd xmm2,xmm1
      movsd xmm3,xmm1
      mulsd xmm2,-3.0
      mulsd xmm3,3.0
      glOrtho(-6.0, 6.0, xmm2, xmm3, -10.0, 10.0);
   .else
      divsd xmm0,xmm1
      movsd xmm1,xmm0
      mulsd xmm0,-6.0
      mulsd xmm1,6.0
      glOrtho(xmm0, xmm1, -3.0, 3.0, -10.0, 10.0)
   .endif
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity();
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
   glutInitWindowSize(600, 600)
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
