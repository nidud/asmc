;
; https://www.opengl.org/archives/resources/code/samples/redbook/aargb.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

    .data
    rotAngle real4 0.0

    .code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

init proc

   local values[2]:real4

   glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &values)
   printf("GL_LINE_WIDTH_GRANULARITY value is %3.1f\n", values)

   glGetFloatv(GL_LINE_WIDTH_RANGE, &values)
   printf ("GL_LINE_WIDTH_RANGE values are %3.1f %3.1f\n",
      values, values[4])

   glEnable(GL_LINE_SMOOTH)
   glEnable(GL_BLEND)
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
   glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE)
   glLineWidth(1.5)

   glClearColor(0.0, 0.0, 0.0, 0.0)

   ret
init endp

;; Draw 2 diagonal lines to form an X

display proc

   glClear(GL_COLOR_BUFFER_BIT)

   glColor3f(0.0, 1.0, 0.0)
   glPushMatrix()

   mov eax,rotAngle
   or  eax,0x80000000
   movd xmm0,eax
   glRotatef(xmm0, 0.0, 0.0, 0.1)
   glBegin(GL_LINES);
   glVertex2f(-0.5, 0.5)
   glVertex2f(0.5, -0.5)
   glEnd()
   glPopMatrix()

   glColor3f(0.0, 0.0, 1.0)
   glPushMatrix()
   glRotatef(rotAngle, 0.0, 0.0, 0.1)
   glBegin(GL_LINES)
   glVertex2f(0.5, 0.5)
   glVertex2f(-0.5, -0.5)
   glEnd()
   glPopMatrix()

   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()

   cvtsi2ss  xmm3,h
   cvtsi2ss  xmm1,w
   divss     xmm3,xmm1
   .if w <= h
      movss  xmm2,-1.0
      mulss  xmm2,xmm3
      movss  xmm0,1.0
      mulss  xmm3,xmm0
      cvtss2sd xmm2,xmm2
      cvtss2sd xmm3,xmm3
      gluOrtho2D(-1.0, 1.0, xmm2, xmm3)
   .else
      movss  xmm0,-1.0
      mulss  xmm0,xmm3
      movss  xmm1,1.0
      mulss  xmm1,xmm3
      cvtss2sd xmm0,xmm0
      cvtss2sd xmm1,xmm1
      gluOrtho2D(xmm0, xmm1, -1.0, 1.0)
   .endif
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

   .switch key
      .case 'r'
      .case 'R'
         movss   xmm0,rotAngle
         addss   xmm0,20.0
         movss   rotAngle,xmm0
         ucomiss xmm0,360.0
         .ifnb
             mov rotAngle,0.0
         .endif
         glutPostRedisplay()
         .endc
      .case 27  ;; Escape Key
         exit(0)
         .endc
      .default
         .endc
    .endsw
    ret
keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
   glutInitWindowSize(200, 200)
   mov rcx,argv
   glutCreateWindow([rcx])
   init()
   glutReshapeFunc(&reshape)
   glutKeyboardFunc(&keyboard)
   glutDisplayFunc(&display)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
