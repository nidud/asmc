;
; https://www.opengl.org/archives/resources/code/samples/redbook/accanti.c
;
include GL/glut.inc
include jitter.inc

    .code

init proc

    .data
    mat_ambient     real4 1.0, 1.0, 1.0, 1.0
    mat_specular    real4 1.0, 1.0, 1.0, 1.0
    light_position  real4 0.0, 0.0, 10.0, 1.0
    lm_ambient      real4 0.2, 0.2, 0.2, 1.0
    .code

    glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient)
    glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0)
    glLightfv(GL_LIGHT0, GL_POSITION, &light_position)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &lm_ambient)

    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_FLAT)

    glClearColor(0.0, 0.0, 0.0, 0.0)
    glClearAccum(0.0, 0.0, 0.0, 0.0)
    ret

init endp

displayObjects proc

    .data
    torus_diffuse   real4 0.7, 0.7, 0.0, 1.0
    cube_diffuse    real4 0.0, 0.7, 0.7, 1.0
    sphere_diffuse  real4 0.7, 0.0, 0.7, 1.0
    octa_diffuse    real4 0.7, 0.4, 0.4, 1.0

    .code
    glPushMatrix()
    glRotatef(30.0, 1.0, 0.0, 0.0)

    glPushMatrix()
    glTranslatef(-0.80, 0.35, 0.0)
    glRotatef(100.0, 1.0, 0.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &torus_diffuse)
    glutSolidTorus(0.275, 0.85, 16, 16)
    glPopMatrix()

    glPushMatrix()
    glTranslatef(-0.75, -0.50, 0.0)
    glRotatef(45.0, 0.0, 0.0, 1.0)
    glRotatef(45.0, 1.0, 0.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &cube_diffuse)
    glutSolidCube(1.5)
    glPopMatrix()

    glPushMatrix()
    glTranslatef(0.75, 0.60, 0.0)
    glRotatef(30.0, 1.0, 0.0, 0.0)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &sphere_diffuse)
    glutSolidSphere(1.0, 16, 16)
    glPopMatrix()

    glPushMatrix()
    glTranslatef(0.70, -0.90, 0.25)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &octa_diffuse)
    glutSolidOctahedron()
    glPopMatrix()

    glPopMatrix()
    ret

displayObjects endp

ACSIZE equ 8

display proc uses rsi

   local viewport[4]:int_t

    glGetIntegerv(GL_VIEWPORT, &viewport)

    glClear(GL_ACCUM_BUFFER_BIT)
    .for (esi = 0: esi < ACSIZE: esi++)
      glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
      glPushMatrix()

      lea       rcx,j8
      movss     xmm0,[rcx+rsi*8].jitter_point.x
      movss     xmm1,[rcx+rsi*8].jitter_point.y
      mulss     xmm0,4.5
      mulss     xmm1,4.5
      cvtsi2ss  xmm2,viewport[2*4]
      divss     xmm0,xmm2
      cvtsi2ss  xmm2,viewport[3*4]
      divss     xmm1,xmm2

      glTranslatef(xmm0, xmm1, 0.0)
      displayObjects()
      glPopMatrix()
      glAccum(GL_ACCUM, 1.0 / 8.0)
    .endf
    glAccum(GL_RETURN, 1.0)
    glFlush()
    ret
display endp

reshape proc w:int_t, h:int_t

    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    .if w <= h

        cvtsi2ss xmm2,h
        cvtsi2ss xmm0,w
        divss xmm2,xmm0
        movss xmm3,xmm2
        mulss xmm2,-2.25
        mulss xmm3,2.25

        cvtss2sd xmm2,xmm2
        cvtss2sd xmm3,xmm3

        glOrtho(-2.25, 2.25, xmm2, xmm3, -10.0, 10.0)

    .else

        cvtsi2ss xmm0,w
        cvtsi2ss xmm1,h
        divss xmm0,xmm1
        movss xmm1,xmm0
        mulss xmm0,-2.25
        mulss xmm1,2.25
        cvtss2sd xmm0,xmm0
        cvtss2sd xmm1,xmm1

        glOrtho(xmm0, xmm1, -2.25, 2.25, -10.0, 10.0)
    .endif
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

   .switch key
      .case 27
         exit(0)
         .endc
    .endsw
    ret
keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_ACCUM or GLUT_DEPTH)
   glutInitWindowSize(250, 250)
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
