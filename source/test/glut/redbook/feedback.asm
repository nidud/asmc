;
; https://www.opengl.org/archives/resources/code/samples/redbook/feedback.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

init proc

   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   ret

init endp

drawGeometry proc mode:GLenum

   glBegin(GL_LINE_STRIP)
   glNormal3f(0.0, 0.0, 1.0)
   glVertex3f(30.0, 30.0, 0.0)
   glVertex3f(50.0, 60.0, 0.0)
   glVertex3f(70.0, 40.0, 0.0)
   glEnd()
   .if (mode == GL_FEEDBACK)
      glPassThrough(1.0)
   .endif
   glBegin(GL_POINTS)
   glVertex3f(-100.0, -100.0, -100.0)
   glEnd()
   .if (mode == GL_FEEDBACK)
      glPassThrough(2.0)
   .endif
   glBegin(GL_POINTS)
   glNormal3f(0.0, 0.0, 1.0)
   glVertex3f(50.0, 50.0, 0.0)
   glEnd()
   ret

drawGeometry endp

print3DcolorVertex proc uses rsi rdi rbx size:GLint, count:ptr GLint,
                         buffer:ptr GLfloat
    mov rdi,rdx
    mov rbx,r8

    printf("  ")
    .for (esi = 0: esi < 7: esi++)

        mov ecx,size
        sub ecx,[rdi]
        movss xmm1,[rbx+rcx*4]
        cvtss2sd xmm1,xmm1
        printf("%4.2f ", xmm1)
        dec int_t ptr [rdi]
    .endf
    printf("\n")
    ret

print3DcolorVertex endp

printBuffer proc uses rsi rdi rbx size:GLint, buffer:ptr GLfloat

  local token:real8
  local count:GLint

    mov esi,ecx
    mov rbx,rdx
    mov count,ecx

    .while count

        mov ecx,esi
        sub ecx,count
        movss xmm0,[rbx+rcx*4]
        cvtss2si eax,xmm0
        dec count

        .if eax == GL_PASS_THROUGH_TOKEN
            cvtss2sd xmm1,xmm0
            movsd token,xmm1
            printf("GL_PASS_THROUGH_TOKEN\n")
            printf("  %4.2f\n", token)
            dec count
        .elseif eax == GL_POINT_TOKEN
            printf("GL_POINT_TOKEN\n")
            print3DcolorVertex(esi, &count, rbx)
        .elseif eax == GL_LINE_TOKEN
            printf("GL_LINE_TOKEN\n")
            print3DcolorVertex(esi, &count, rbx)
            print3DcolorVertex(esi, &count, rbx)
        .elseif eax == GL_LINE_RESET_TOKEN
            printf("GL_LINE_RESET_TOKEN\n")
            print3DcolorVertex(esi, &count, rbx)
            print3DcolorVertex(esi, &count, rbx)
        .endif
    .endw
    ret

printBuffer endp

display proc

   local feedBuffer[1024]:GLfloat
   local size:GLint

   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   glOrtho(0.0, 100.0, 0.0, 100.0, 0.0, 1.0)

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glClear(GL_COLOR_BUFFER_BIT);
   drawGeometry(GL_RENDER)

   glFeedbackBuffer(1024, GL_3D_COLOR, &feedBuffer)
   glRenderMode(GL_FEEDBACK)
   drawGeometry(GL_FEEDBACK)
   mov size,glRenderMode(GL_RENDER)
   printBuffer(size, &feedBuffer)
   ret

display endp

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
   glutDisplayFunc(&display)
   glutKeyboardFunc(&keyboard)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
