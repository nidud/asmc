;
; https://www.opengl.org/archives/resources/code/samples/redbook/
;
include GL/glut.inc
include stdio.inc
include tchar.inc

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glEnable(GL_DEPTH_TEST)
   glShadeModel(GL_FLAT)
   glDepthRange(0.0, 1.0)
   ret

init endp

drawRects proc mode:GLenum

   .if ecx == GL_SELECT
      glLoadName(1)
   .endif
   glBegin(GL_QUADS)
   glColor3f(1.0, 1.0, 0.0)
   glVertex3i(2, 0, 0)
   glVertex3i(2, 6, 0)
   glVertex3i(6, 6, 0)
   glVertex3i(6, 0, 0)
   glEnd();
   .if (mode == GL_SELECT)
      glLoadName(2);
   .endif
   glBegin(GL_QUADS);
   glColor3f(0.0, 1.0, 1.0)
   glVertex3i(3, 2, -1)
   glVertex3i(3, 8, -1)
   glVertex3i(8, 8, -1)
   glVertex3i(8, 2, -1)
   glEnd();
   .if (mode == GL_SELECT)
      glLoadName(3);
   .endif
   glBegin(GL_QUADS)
   glColor3f(1.0, 0.0, 1.0)
   glVertex3i(0, 2, -2)
   glVertex3i(0, 7, -2)
   glVertex3i(5, 7, -2)
   glVertex3i(5, 2, -2)
   glEnd();
   ret

drawRects endp

processHits proc uses rsi rdi rbx hits:GLint, buffer:ptr GLuint

    local names:GLuint

    mov rdi,rdx
    printf("hits = %d\n", ecx)

    .for (esi = 0: esi < hits: esi++)
        mov ebx,[rdi]
        mov names,ebx
        printf(" number of names for hit = %d\n", ebx)
        add rdi,4
        mov ecx,0x7fffffff
        mov eax,[rdi]
        xor edx,edx
        div ecx
        cvtsi2sd xmm1,eax
        printf("  z1 is %g;", xmm1)
        add rdi,4
        mov ecx,0x7fffffff
        mov eax,[rdi]
        xor edx,edx
        div ecx
        cvtsi2sd xmm1,eax
        printf(" z2 is %g\n", xmm1)
        add rdi,4
        printf("   the name is ")
        .for (ebx = 0: ebx < names: ebx++)
            printf("%d ", [rdi])
            add rdi,4
        .endf
        printf("\n")
    .endf
    ret

processHits endp

BUFSIZE equ 512

pickRects proc button:int_t, state:int_t, x:int_t, y:int_t

   local selectBuf[BUFSIZE]:GLuint
   local hits:GLint
   local viewport[4]:GLint

   .return .if ecx != GLUT_LEFT_BUTTON || edx != GLUT_DOWN

   glGetIntegerv(GL_VIEWPORT, &viewport)

   glSelectBuffer(BUFSIZE, &selectBuf)
   glRenderMode(GL_SELECT)

   glInitNames()
   glPushName(0)

   glMatrixMode(GL_PROJECTION)
   glPushMatrix()
   glLoadIdentity()

   cvtsi2sd xmm0,x
   cvtsi2sd xmm2,y
   cvtsi2sd xmm1,viewport[3*4]
   subsd xmm1,xmm2
   gluPickMatrix(xmm0, xmm1, 5.0, 5.0, &viewport)
   glOrtho(0.0, 8.0, 0.0, 8.0, -0.5, 2.5)
   drawRects(GL_SELECT)
   glPopMatrix()
   glFlush()

   processHits(glRenderMode(GL_RENDER), &selectBuf)
   ret

pickRects endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
   drawRects(GL_RENDER)
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   glOrtho(0.0, 8.0, 0.0, 8.0, -0.5, 2.5)
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
   glutInitWindowSize(200, 200)
   glutInitWindowPosition(100, 100)
   mov rcx,argv
   glutCreateWindow([rcx])
   init()
   glutReshapeFunc(&reshape)
   glutDisplayFunc(&display)
   glutMouseFunc(&pickRects)
   glutKeyboardFunc(&keyboard)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
