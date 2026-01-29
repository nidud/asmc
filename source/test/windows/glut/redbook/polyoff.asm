;
; https://www.opengl.org/archives/resources/code/samples/redbook/polyoff.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

ifdef GL_VERSION_1_1
.data
list GLuint 0
spinx GLint 0
spiny GLint 0
tdist GLfloat 0.0
polyfactor GLfloat 1.0
polyunits GLfloat 1.0

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

display proc

    .data
    mat_ambient     GLfloat 0.8, 0.8, 0.8, 1.0
    mat_diffuse     GLfloat 1.0, 0.0, 0.5, 1.0
    mat_specular    GLfloat 1.0, 1.0, 1.0, 1.0
    gray            GLfloat 0.8, 0.8, 0.8, 1.0
    black           GLfloat 0.0, 0.0, 0.0, 1.0

    .code
    glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
    glPushMatrix()
    glTranslatef(0.0, 0.0, tdist)
    cvtsi2ss xmm0,spinx
    glRotatef(xmm0, 1.0, 0.0, 0.0)
    cvtsi2ss xmm0,spiny
    glRotatef(xmm0, 0.0, 1.0, 0.0)

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &gray)
    glMaterialfv(GL_FRONT, GL_SPECULAR, &black)
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0);
    glEnable(GL_POLYGON_OFFSET_FILL)
    glPolygonOffset(polyfactor, polyunits)
    glCallList(list)
    glDisable(GL_POLYGON_OFFSET_FILL)

    glDisable(GL_LIGHTING)
    glDisable(GL_LIGHT0)
    glColor3f (1.0, 1.0, 1.0)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
    glCallList(list)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)

    glPopMatrix()
    glFlush()
   ret

display endp

gfxinit proc

    .data
    light_ambient   GLfloat 0.0, 0.0, 0.0, 1.0
    light_diffuse   GLfloat 1.0, 1.0, 1.0, 1.0
    light_specular  GLfloat 1.0, 1.0, 1.0, 1.0
    light_position  GLfloat 1.0, 1.0, 1.0, 0.0
    global_ambient  GLfloat 0.2, 0.2, 0.2, 1.0
    .code

    glClearColor(0.0, 0.0, 0.0, 1.0)

    mov list,glGenLists(1)
    glNewList(list, GL_COMPILE)
    glutSolidSphere(1.0, 20, 12)
    glEndList()

    glEnable(GL_DEPTH_TEST)

    glLightfv (GL_LIGHT0, GL_AMBIENT, &light_ambient)
    glLightfv (GL_LIGHT0, GL_DIFFUSE, &light_diffuse)
    glLightfv (GL_LIGHT0, GL_SPECULAR, &light_specular)
    glLightfv (GL_LIGHT0, GL_POSITION, &light_position)
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, &global_ambient)
    ret

gfxinit endp

reshape proc w:int_t, h:int_t

    glViewport(0, 0, ecx, edx)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    cvtsi2sd xmm1,w
    cvtsi2sd xmm0,h
    divsd xmm1,xmm0
    gluPerspective(45.0, xmm1, 1.0, 10.0)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity()
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    ret

reshape endp

mouse proc button:int_t, state:int_t, x:int_t, y:int_t

    .switch ecx
    .case GLUT_LEFT_BUTTON
        .switch edx
        .case GLUT_DOWN
            mov eax,spinx
            add eax,5
            mov ecx,360
            xor edx,edx
            div ecx
            mov spinx,edx
            glutPostRedisplay();
            .endc
        .endsw
        .endc
    .case GLUT_MIDDLE_BUTTON
        .switch edx
        .case GLUT_DOWN
            mov eax,spiny
            add eax,5
            mov ecx,360
            xor edx,edx
            div ecx
            mov spiny,edx
            glutPostRedisplay()
            .endc
        .endsw
        .endc
    .case GLUT_RIGHT_BUTTON
        .switch edx
        .case GLUT_UP
            exit(0)
            .endc
        .endsw
        .endc
    .endsw
    ret

mouse endp

keyboard proc key:byte, x:int_t, y:int_t

    .switch cl
    .case 't'
        movss xmm0,tdist
        comiss xmm0,4.0
        .ifb
            addss xmm0,0.5
            movss tdist,xmm0
            glutPostRedisplay();
        .endif
        .endc
    .case 'T'
        movss xmm0,tdist
        comiss xmm0,-5.0
        .ifa
            subss xmm0,0.5
            movss tdist,xmm0
            glutPostRedisplay();
        .endif
        .endc
    .case 'F'
        movss xmm0,polyfactor
        addss xmm0,0.1
        movss polyfactor,xmm0
        cvtss2sd xmm0,xmm0
        printf("polyfactor is %f\n", xmm0)
        glutPostRedisplay()
        .endc
    .case 'f'
        movss xmm0,polyfactor
        subss xmm0,0.1
        movss polyfactor,xmm0
        cvtss2sd xmm0,xmm0
        printf("polyfactor is %f\n", xmm0)
        glutPostRedisplay()
        .endc
    .case 'U'
        movss xmm0,polyunits
        addss xmm0,0.1
        movss polyunits,xmm0
        cvtss2sd xmm0,xmm0
        printf("polyunits is %f\n", xmm0)
        glutPostRedisplay()
        .endc
    .case 'u'
        movss xmm0,polyunits
        subss xmm0,0.1
        movss polyunits,xmm0
        cvtss2sd xmm0,xmm0
        printf ("polyunits is %f\n", xmm0)
        glutPostRedisplay()
        .endc
    .endsw
    ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_DEPTH)
   mov rcx,argv
   glutCreateWindow([rcx])
   glutReshapeFunc(&reshape)
   glutDisplayFunc(&display)
   glutMouseFunc(&mouse)
   glutKeyboardFunc(&keyboard)
   gfxinit()
   glutMainLoop()
   xor eax,eax
   ret

main endp

else
main proc argc:int_t, argv:array_t
    fprintf(stderr, "This program demonstrates a feature which is not in OpenGL Version 1.0.\n");
    fprintf(stderr, "If your implementation of OpenGL Version 1.0 has the right extensions,\n");
    fprintf(stderr, "you may be able to modify this program to make it run.\n");
    xor eax,eax
    ret
main endp
endif

    end _tstart
