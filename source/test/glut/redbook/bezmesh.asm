;
; https://www.opengl.org/archives/resources/code/samples/redbook/
;
include GL/glut.inc

.data
ctrlpoints real4 \
   -1.5, -1.5, 4.0,
   -0.5, -1.5, 2.0,
    0.5, -1.5, -1.0,
    1.5, -1.5, 2.0,
   -1.5, -0.5, 1.0,
   -0.5, -0.5, 3.0,
    0.5, -0.5, 0.0,
    1.5, -0.5, -1.0,
   -1.5, 0.5, 4.0,
   -0.5, 0.5, 0.0,
    0.5, 0.5, 3.0,
    1.5, 0.5, 4.0,
   -1.5, 1.5, -2.0,
   -0.5, 1.5, -2.0,
    0.5, 1.5, 0.0,
    1.5, 1.5, -1.0

.code

initlights proc

   .data
   ambient       real4 0.2, 0.2, 0.2, 1.0
   position      real4 0.0, 0.0, 2.0, 1.0
   mat_diffuse   real4 0.6, 0.6, 0.6, 1.0
   mat_specular  real4 1.0, 1.0, 1.0, 1.0
   mat_shininess real4 50.0

   .code

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glLightfv(GL_LIGHT0, GL_AMBIENT, &ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, &position);

   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, &mat_shininess);
   ret

initlights endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);
   glPushMatrix();
   glRotatef(85.0, 1.0, 1.0, 1.0);
   glEvalMesh2(GL_FILL, 0, 20, 0, 20);
   glPopMatrix();
   glFlush();
   ret

display endp

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints);
   glEnable(GL_MAP2_VERTEX_3);
   glEnable(GL_AUTO_NORMAL);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   initlights()
   ret

init endp

reshape proc w:int_t, h:int_t

    glViewport(0, 0, ecx, edx)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    .if w <= h

        cvtsi2ss xmm2,h
        cvtsi2ss xmm0,w
        divss xmm2,xmm0
        movss xmm3,xmm2
        mulss xmm2,-4.0
        mulss xmm3,4.0
        cvtss2sd xmm2,xmm2
        cvtss2sd xmm3,xmm3

        glOrtho(-4.0, 4.0, xmm2, xmm3, -4.0, 4.0);
    .else

        cvtsi2ss xmm0,w
        cvtsi2ss xmm1,h
        divss xmm0,xmm1
        movss xmm1,xmm0
        mulss xmm0,-4.0
        mulss xmm1,4.0
        cvtss2sd xmm0,xmm0
        cvtss2sd xmm1,xmm1
        glOrtho(xmm0, xmm1, -4.0, 4.0, -4.0, 4.0);
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
