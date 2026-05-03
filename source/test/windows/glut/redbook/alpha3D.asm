;
; https://www.opengl.org/archives/resources/code/samples/redbook/alpha3D.c
;
include GL/glut.inc
include stdio.inc

MAXZ equ 8.0
MINZ equ -8.0
ZINC equ 0.4

.data
solidZ          real4 MAXZ
transparentZ    real4 MINZ
sphereList      GLuint 0
cubeList        GLuint 0

.code

init proc

   .data
   mat_specular     GLfloat 1.0, 1.0, 1.0, 0.15
   mat_shininess    GLfloat 100.0
   position         GLfloat 0.5, 0.5, 1.0, 0.0
   .code

   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, &mat_shininess)
   glLightfv(GL_LIGHT0, GL_POSITION, &position)

   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   glEnable(GL_DEPTH_TEST)

   mov sphereList,glGenLists(1)
   glNewList(eax, GL_COMPILE)
   glutSolidSphere(0.4, 16, 16)
   glEndList()

   mov cubeList,glGenLists(1)
   glNewList(eax, GL_COMPILE)
   glutSolidCube(0.6)
   glEndList()
   ret
init endp

display proc

   .data
   mat_solid        GLfloat 0.75, 0.75, 0.0, 1.0
   mat_zero         GLfloat 0.0, 0.0, 0.0, 1.0
   mat_transparent  GLfloat 0.0, 0.8, 0.8, 0.6
   mat_emission     GLfloat 0.0, 0.3, 0.3, 0.6
   .code

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)

   glPushMatrix()
   glTranslatef(-0.15, -0.15, solidZ)
   glMaterialfv(GL_FRONT, GL_EMISSION, &mat_zero)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_solid)
   glCallList(sphereList)
   glPopMatrix()

   glPushMatrix()
   glTranslatef(0.15, 0.15, transparentZ)
   glRotatef(15.0, 1.0, 1.0, 0.0)
   glRotatef(30.0, 0.0, 1.0, 0.0)
   glMaterialfv(GL_FRONT, GL_EMISSION, &mat_emission)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_transparent)
   glEnable(GL_BLEND)
   glDepthMask(GL_FALSE)
   glBlendFunc(GL_SRC_ALPHA, GL_ONE)
   glCallList(cubeList)
   glDepthMask(GL_TRUE)
   glDisable(GL_BLEND)
   glPopMatrix()

   glutSwapBuffers()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()

   cvtsi2sd xmm0,h
   cvtsi2sd xmm1,w

   .if w <= h

      divsd xmm0,xmm1
      movsd xmm2,xmm0
      mulsd xmm2,-1.5
      mulsd xmm0,1.5
      movsd xmm3,xmm0

      glOrtho(-1.5, 1.5, xmm2, xmm3, -10.0, 10.0)
   .else

      divsd xmm1,xmm0
      movsd xmm0,xmm1
      mulsd xmm0,-1.5
      mulsd xmm1,1.5

      glOrtho(xmm0, xmm1, -1.5, 1.5, -10.0, 10.0)
   .endif
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   ret

reshape endp

animate proc

    movss  xmm0,solidZ
    movss  xmm1,transparentZ
    xor    eax,eax
    comiss xmm0,MINZ
    .ifnb
        inc eax
    .else
        comiss xmm1,MAXZ
        .ifnb
            inc eax
        .endif
    .endif

   .if eax
      glutIdleFunc(NULL)
   .else
      subss xmm0,ZINC
      movss solidZ,xmm0
      addss xmm1,ZINC
      movss transparentZ,xmm1
      glutPostRedisplay()
   .endif
   ret

animate endp

keyboard proc key:byte, x:int_t, y:int_t

    .switch cl
      .case 'a'
      .case 'A'
        mov solidZ,MAXZ
        mov transparentZ,MINZ
        glutIdleFunc(&animate)
        .endc
      .case 'r'
      .case 'R'
        mov solidZ,MAXZ
        mov transparentZ,MINZ
        glutPostRedisplay()
        .endc
      .case 27
        exit(0)
    .endsw
    ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_DEPTH)
   glutInitWindowSize(500, 500)
   ;glutInitWindowPosition(100, 100)
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
