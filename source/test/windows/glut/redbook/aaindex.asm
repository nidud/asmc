;
; https://www.opengl.org/archives/resources/code/samples/redbook/aaindex.c
;
include GL/glut.inc

RAMPSIZE   equ 16
RAMP1START equ 32
RAMP2START equ 48

    .data
    rotAngle real4 0.0

    .code

init proc uses rsi rdi

   .for (edi = 0: edi < RAMPSIZE: edi++)

      cvtsi2ss xmm0,edi
      movss xmm2,16.0
      divss xmm0,xmm2
      movd esi,xmm0
      glutSetColor(&[edi+RAMP1START], 0.0, xmm2, 0.0)
      movd xmm3,esi
      glutSetColor(&[edi+RAMP2START], 0.0, 0.0, xmm3)
   .endf

   glEnable(GL_LINE_SMOOTH)
   glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE)
   glLineWidth(1.5)

   glClearIndex(32.0)
   ret
init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)

   glIndexi(RAMP1START)
   glPushMatrix()

   mov eax,rotAngle
   or  eax,0x80000000
   movd xmm0,eax
   glRotatef(xmm0, 0.0, 0.0, 0.1)
   glBegin(GL_LINES)
   glVertex2f(-0.5, 0.5)
   glVertex2f(0.5, -0.5)
   glEnd()
   glPopMatrix()

   glIndexi(RAMP2START)
   glPushMatrix()
   glRotatef(rotAngle, 0.0, 0.0, 0.1)
   glBegin(GL_LINES)
   glVertex2f(0.5, 0.5)
   glVertex2f(-0.5, -0.5)
   glEnd ()
   glPopMatrix()

   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()

   cvtsi2ss  xmm3,h
   cvtsi2ss  xmm1,w
   divss     xmm3,xmm1

   .if (w <= h)

      movss     xmm2,-1.0
      mulss     xmm2,xmm3
      movss     xmm0,1.0
      mulss     xmm3,xmm0

      gluOrtho2D(-1.0, 1.0, xmm2, xmm3)
   .else

      movss     xmm0,-1.0
      mulss     xmm0,xmm3
      movss     xmm1,1.0
      mulss     xmm1,xmm3

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
      .case 27
         exit(0)
    .endsw
    ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_INDEX)
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
