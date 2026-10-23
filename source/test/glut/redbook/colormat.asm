;
; https://www.opengl.org/archives/resources/code/samples/redbook/colormat.c
;
include GL/glut.inc

.data
diffuseMaterial GLfloat 0.5, 0.5, 0.5, 1.0

.code

init proc

    .data
    mat_specular   GLfloat 1.0, 1.0, 1.0, 1.0
    light_position GLfloat 1.0, 1.0, 1.0, 0.0
    .code

    glClearColor(0.0, 0.0, 0.0, 0.0)
    glShadeModel(GL_SMOOTH)
    glEnable(GL_DEPTH_TEST)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuseMaterial)
    glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0)
    glLightfv(GL_LIGHT0, GL_POSITION, &light_position)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)

    glColorMaterial(GL_FRONT, GL_DIFFUSE)
    glEnable(GL_COLOR_MATERIAL)
    ret

init endp

display proc

    glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
    glutSolidSphere(1.0, 20, 16)
    glFlush()
    ret

display endp

reshape proc w:int_t, h:int_t

    glViewport (0, 0, ecx, edx)
    glMatrixMode (GL_PROJECTION)
    glLoadIdentity()
    cvtsi2sd xmm0,w
    .if w <= h
        cvtsi2sd xmm2,h
        divsd xmm2,xmm0
        movsd xmm3,xmm2
        mulsd xmm2,-1.5
        mulsd xmm3,1.5
        glOrtho(-1.5, 1.5, xmm2, xmm3, -10.0, 10.0)
    .else
        cvtsi2sd xmm1,h
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

mouse proc button:int_t, state:int_t, x:int_t, y:int_t

    .switch ecx
      .case GLUT_LEFT_BUTTON
         .if edx == GLUT_DOWN
            movss xmm0,diffuseMaterial
            addss xmm0,0.1
            comiss xmm0,1.0
            .ifa
               xorps xmm0,xmm0
            .endif
            movss diffuseMaterial,xmm0
            glColor4fv(&diffuseMaterial)
            glutPostRedisplay()
         .endif
         .endc
      .case GLUT_MIDDLE_BUTTON
         .if edx == GLUT_DOWN
            movss xmm0,diffuseMaterial[4]
            addss xmm0,0.1
            comiss xmm0,1.0
            .ifa
               xorps xmm0,xmm0
            .endif
            movss diffuseMaterial[4],xmm0
            glColor4fv(&diffuseMaterial)
            glutPostRedisplay()
         .endif
         .endc
      .case GLUT_RIGHT_BUTTON
         .if edx == GLUT_DOWN
            movss xmm0,diffuseMaterial[8]
            addss xmm0,0.1
            comiss xmm0,1.0
            .ifa
               xorps xmm0,xmm0
            .endif
            movss diffuseMaterial[8],xmm0
            glColor4fv(&diffuseMaterial)
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
    glutKeyboardFunc(&keyboard)
    glutMouseFunc(&mouse)
    glutMainLoop()
    xor eax,eax
    ret

main endp

    end _tstart
