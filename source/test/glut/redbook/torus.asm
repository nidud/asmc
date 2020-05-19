;
; https://www.opengl.org/archives/resources/code/samples/redbook/torus.c
;
include GL/glut.inc
include stdio.inc
include math.inc

PI_ equ 3.14159265358979323846

.data
theTorus GLuint 0

.code

torus proc uses rsi rdi rbx numc:int_t, numt:int_t

    local s:double, t:double, x:double, y:double, z:double, twopi:double

    movsd xmm0,2.0 * PI_
    movsd twopi,xmm0

    .for (esi = 0: esi < numc: esi++)

        glBegin(GL_QUAD_STRIP)

        .for (edi = 0: edi <= numt: edi++)

            .fors (ebx = 1: ebx >= 0: ebx--)

                lea rax,[rsi+rbx]
                cdq
                idiv numc
                cvtsi2sd xmm0,edx
                addsd xmm0,0.5
                movsd s,xmm0

                mov eax,edi
                cdq
                idiv numt
                cvtsi2sd xmm0,edx
                movsd t,xmm0

                mulsd xmm0,twopi
                cvtsi2sd xmm1,numt
                divsd xmm0,xmm1
                movsd z,xmm0
                movsd x,cos(xmm0)

                movsd xmm0,s
                mulsd xmm0,twopi
                cvtsi2sd xmm1,numc
                divsd xmm0,xmm1
                cos(xmm0)
                mulsd xmm0,0.1
                addsd xmm0,1.0
                movsd y,xmm0
                mulsd xmm0,x
                movsd x,xmm0

                sin(z)
                mulsd xmm0,y
                movsd y,xmm0

                movsd xmm0,s
                mulsd xmm0,twopi
                cvtsi2sd xmm1,numc
                divsd xmm0,xmm1
                sin(xmm0)
                mulsd xmm0,0.1
                movsd z,xmm0

                movsd xmm0,x
                movsd xmm0,y
                movsd xmm0,z
                cvtsd2ss xmm0,xmm0
                cvtsd2ss xmm1,xmm1
                cvtsd2ss xmm2,xmm2

                glVertex3f(xmm0, xmm1, xmm2);
            .endf
        .endf
        glEnd();
    .endf
    ret

torus endp

init proc

   mov theTorus,glGenLists (1);
   glNewList(theTorus, GL_COMPILE);
   torus(8, 25);
   glEndList();

   glShadeModel(GL_FLAT);
   glClearColor(0.0, 0.0, 0.0, 0.0);
   ret
init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glCallList(theTorus);
   glFlush();
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity();
   cvtsi2sd xmm1,w
   cvtsi2sd xmm0,h
   divsd xmm1,xmm0
   gluPerspective(30.0, xmm1, 1.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

   .switch cl
   .case 'x'
   .case 'X'
      glRotatef(30.0, 1.0, 0.0, 0.0);
      glutPostRedisplay();
      .endc
   .case 'y'
   .case 'Y'
      glRotatef(30.0, 0.0, 1.0, 0.0);
      glutPostRedisplay();
      .endc
   .case 'i'
   .case 'I'
      glLoadIdentity();
      gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
      glutPostRedisplay();
      .endc
   .case 27
      exit(0);
      .endc
   .endsw
   ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
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
