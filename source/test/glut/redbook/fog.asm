;
; https://www.opengl.org/archives/resources/code/samples/redbook/fog.asm
;
include GL/glut.inc
include math.inc
include stdio.inc
include tchar.inc

.data
fogMode int_t 0

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

init proc

    .data
    position GLfloat 0.5, 0.5, 3.0, 0.0
    .code

    glEnable(GL_DEPTH_TEST)

    glLightfv(GL_LIGHT0, GL_POSITION, &position)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)

        .new mat[3]:GLfloat

        mov mat[0],0.1745
        mov mat[4],0.01175
        mov mat[8],0.01175

        glMaterialfv(GL_FRONT, GL_AMBIENT, &mat)
        mov mat[0],0.61424
        mov mat[4],0.04136
        mov mat[8],0.04136
        glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat)
        mov mat[0],0.727811
        mov mat[4],0.626959
        mov mat[8],0.626959
        glMaterialfv(GL_FRONT, GL_SPECULAR, &mat)
        glMaterialf(GL_FRONT, GL_SHININESS, 0.6*128.0)

    glEnable(GL_FOG)

        .new fogColor[4]:GLfloat

        mov fogColor[0],0.5
        mov fogColor[4],0.5
        mov fogColor[8],0.5
        mov fogColor[12],1.0

        mov fogMode,GL_EXP
        glFogi(GL_FOG_MODE, fogMode)
        glFogfv(GL_FOG_COLOR, &fogColor)
        glFogf(GL_FOG_DENSITY, 0.35)
        glHint(GL_FOG_HINT, GL_DONT_CARE)
        glFogf(GL_FOG_START, 1.0)
        glFogf(GL_FOG_END, 5.0)

    glClearColor(0.5, 0.5, 0.5, 1.0)
    ret

init endp



renderSphere proc x:GLfloat, y:GLfloat, z:GLfloat

    glPushMatrix()
    glTranslatef(x, y, z)
    glutSolidSphere(0.4, 16, 16)
    glPopMatrix()
    ret

renderSphere endp

display proc

    glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
    renderSphere(-2.0, -0.5, -1.0)
    renderSphere(-1.0, -0.5, -2.0)
    renderSphere(0.0, -0.5, -3.0)
    renderSphere(1.0, -0.5, -4.0)
    renderSphere(2.0, -0.5, -5.0)
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
        mulsd xmm2,-2.5
        mulsd xmm3,2.5
        glOrtho (-2.5, 2.5, xmm2, xmm3, -10.0, 10.0);
    .else
        divsd xmm0,xmm1
        movsd xmm1,xmm0
        mulsd xmm1,2.5
        mulsd xmm0,-2.5
        glOrtho(xmm0, xmm1, -2.5, 2.5, -10.0, 10.0);
    .endif
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    ret

reshape endp


keyboard proc key:byte, x:int_t, y:int_t

    .switch ecx
      .case 'f'
      .case 'F'
         .if (fogMode == GL_EXP)
            mov fogMode,GL_EXP2
            printf ("Fog mode is GL_EXP2\n")
         .elseif (fogMode == GL_EXP2)
            mov fogMode,GL_LINEAR
            printf ("Fog mode is GL_LINEAR\n")
         .elseif (fogMode == GL_LINEAR)
            mov fogMode,GL_EXP
            printf("Fog mode is GL_EXP\n")
         .endif
         glFogi(GL_FOG_MODE, fogMode)
         glutPostRedisplay()
         .endc
      .case 27:
         exit(0);
         .endc
   .endsw
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
