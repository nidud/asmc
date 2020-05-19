;
; https://www.opengl.org/archives/resources/code/samples/redbook/picksquare.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

.data?
board int_t 3*3 dup(?)

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

init proc uses rdi

   lea rdi,board
   mov ecx,3*3
   xor eax,eax
   rep stosd
   glClearColor(0.0, 0.0, 0.0, 0.0)
   ret

init endp

drawSquares proc uses rsi rdi mode:GLenum

   .for (esi = 0: esi < 3: esi++)
      .if mode == GL_SELECT
         glLoadName(esi)
      .endif
      .for (edi = 0: edi < 3: edi++)
         .if mode == GL_SELECT
            glPushName(edi)
         .endif
         cvtsi2ss xmm0,esi
         divss xmm0,3.0
         cvtsi2ss xmm1,edi
         divss xmm1,3.0
         imul ecx,esi,3*4
         lea rdx,board
         cvtsi2ss xmm2,[rdx+rdi*4]
         divss xmm2,3.0
         glColor3f(xmm0, xmm1, xmm2)
         glRecti(esi, esi, &[esi+1], &[edi+1])
         .if mode == GL_SELECT
            glPopName()
         .endif
      .endf
   .endf
   ret

drawSquares endp

processHits proc uses rsi rdi rbx hits:GLint, buffer:ptr GLuint

    local names:GLuint, ii:GLuint, jj:GLuint

    mov rdi,rdx
    printf ("hits = %d\n", ecx)

    .for (esi = 0: esi < hits: esi++)
        mov ebx,[rdi]
        mov names,ebx
        printf(" number of names for this hit = %d\n", ebx)
        add rdi,4
        mov ecx,0x7fffffff
        mov eax,[rdi]
        cvtsi2sd xmm0,ecx
        cvtsi2sd xmm1,eax
        divsd xmm1,xmm0
        printf("  z1 is %g;", xmm1)
        add rdi,4
        mov ecx,0x7fffffff
        mov eax,[rdi]
        cvtsi2sd xmm0,ecx
        cvtsi2sd xmm1,eax
        divsd xmm1,xmm0
        printf(" z2 is %g\n", xmm1)
        add rdi,4
        printf ("   names are ")
        .for (ebx = 0: ebx < names: ebx++)
            mov edx,[rdi]
            printf("%d ", edx)
            mov eax,[rdi]
            .if (ebx == 0)
                mov ii,eax
            .elseif (ebx == 1)
                mov jj,eax
            .endif
            add rdi,4
        .endf
        printf("\n")
        imul ecx,ii,3
        add ecx,jj
        lea rbx,board
        mov eax,[rbx+rcx*4]
        inc eax
        xor edx,edx
        mov r8d,3
        div r8d
        mov [rbx+rcx*4],eax
   .endf
   ret

processHits endp

BUFSIZE equ 512

pickSquares proc button:int_t, state:int_t, x:int_t, y:int_t

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

   gluOrtho2D(0.0, 3.0, 0.0, 3.0)
   drawSquares(GL_SELECT)

   glMatrixMode(GL_PROJECTION)
   glPopMatrix()
   glFlush()

   processHits(glRenderMode(GL_RENDER), &selectBuf)
   glutPostRedisplay()
   ret

pickSquares endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)
   drawSquares(GL_RENDER)
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   gluOrtho2D(0.0, 3.0, 0.0, 3.0)
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
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
   glutInitWindowSize(100, 100)
   glutInitWindowPosition(100, 100)
   mov rcx,argv
   glutCreateWindow([rcx])
   init()
   glutReshapeFunc(&reshape)
   glutDisplayFunc(&display)
   glutMouseFunc(&pickSquares)
   glutKeyboardFunc(&keyboard)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
