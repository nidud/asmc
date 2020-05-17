;
; https://www.opengl.org/archives/resources/code/samples/redbook/bezsurf.c
;
include GL/glut.inc

.data
ctrlpoints GLfloat \ ;[4][4][3] = {
   -1.5, -1.5, 4.0, -0.5, -1.5, 2.0,
    0.5, -1.5, -1.0, 1.5, -1.5, 2.0,
   -1.5, -0.5, 1.0, -0.5, -0.5, 3.0,
    0.5, -0.5, 0.0, 1.5, -0.5, -1.0,
   -1.5, 0.5, 4.0, -0.5, 0.5, 0.0,
    0.5, 0.5, 3.0, 1.5, 0.5, 4.0,
   -1.5, 1.5, -2.0, -0.5, 1.5, -2.0,
    0.5, 1.5, 0.0, 1.5, 1.5, -1.0

.code

display proc uses rsi rdi

    glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
    glColor3f(1.0, 1.0, 1.0)
    glPushMatrix()
    glRotatef(85.0, 1.0, 1.0, 1.0)
    .for (esi = 0: esi <= 8: esi++)
        glBegin(GL_LINE_STRIP);
        .for (edi = 0: edi <= 30: edi++)

            cvtsi2ss xmm0,edi
            cvtsi2ss xmm1,esi
            divss xmm0,30.0
            divss xmm1,8.0
            glEvalCoord2f(xmm0, xmm1)
        .endf
        glEnd()
        glBegin(GL_LINE_STRIP)
        .for (edi = 0: edi <= 30: edi++)

            cvtsi2ss xmm1,edi
            cvtsi2ss xmm0,esi
            divss xmm1,30.0
            divss xmm0,8.0
            glEvalCoord2f(xmm0, xmm1)
        .endf
        glEnd()
    .endf
    glPopMatrix()
    glFlush()
    ret

display endp

init proc

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints);
   glEnable(GL_MAP2_VERTEX_3);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
   ret

init endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

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

   glMatrixMode(GL_MODELVIEW);
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

