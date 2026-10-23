;
; https://www.opengl.org/archives/resources/code/samples/redbook/select.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

drawTriangle proc x1:GLfloat, y1:GLfloat, x2:GLfloat, y2:GLfloat, x3:GLfloat, y3:GLfloat, z:GLfloat

   glBegin(GL_TRIANGLES)
   glVertex3f(x1, y1, z)
   glVertex3f(x2, y2, z)
   glVertex3f(x3, y3, z)
   glEnd()
   ret

drawTriangle endp

drawViewVolume proc x1:GLfloat, x2:GLfloat, y1:GLfloat, y2:GLfloat, z1:GLfloat, z2:GLfloat

  local _z1:GLfloat
  local _z2:GLfloat

    movss xmm0,z1
    movss xmm1,z2
    movss xmm2,80000000r
    xorps xmm0,xmm2
    xorps xmm1,xmm2
    movss _z1,xmm0
    movss _z2,xmm1

   glColor3f(1.0, 1.0, 1.0)
   glBegin(GL_LINE_LOOP)
   glVertex3f(x1, y1, _z1)
   glVertex3f(x2, y1, _z1)
   glVertex3f(x2, y2, _z1)
   glVertex3f(x1, y2, _z1)
   glEnd()

   glBegin(GL_LINE_LOOP)
   glVertex3f(x1, y1, _z2)
   glVertex3f(x2, y1, _z2)
   glVertex3f(x2, y2, _z2)
   glVertex3f(x1, y2, _z2)
   glEnd()

   glBegin(GL_LINES)
   glVertex3f(x1, y1, _z1)
   glVertex3f(x1, y1, _z2)
   glVertex3f(x1, y2, _z1)
   glVertex3f(x1, y2, _z2)
   glVertex3f(x2, y1, _z1)
   glVertex3f(x2, y1, _z2)
   glVertex3f(x2, y2, _z1)
   glVertex3f(x2, y2, _z2)
   glEnd()
   ret

drawViewVolume endp

drawScene proc

   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   gluPerspective(40.0, 4.0/3.0, 1.0, 100.0)

   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   gluLookAt(7.5, 7.5, 12.5, 2.5, 2.5, -5.0, 0.0, 1.0, 0.0)
   glColor3f(0.0, 1.0, 0.0)
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -5.0)
   glColor3f(1.0, 0.0, 0.0)
   drawTriangle(2.0, 7.0, 3.0, 7.0, 2.5, 8.0, -5.0)
   glColor3f(1.0, 1.0, 0.0)
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, 0.0)
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -10.0)
   drawViewVolume(0.0, 5.0, 0.0, 5.0, 0.0, 10.0)
   ret

drawScene endp

processHits proc uses rbx hits:GLint, buffer:ptr GLuint

   local i:int_t, j:int_t
   local names:GLuint

   mov rbx,rdx
   printf("hits = %d\n", hits)

   .for (i = 0: i < hits: i++)
      mov names,[rbx]
      printf(" number of names for hit = %d\n", names)
      add rbx,4
      cvtsi2sd xmm1,[rbx]
      mov eax,0x7fffffff
      cvtsi2sd xmm0,eax
      divsd xmm1,xmm0
      printf("  z1 is %g;", xmm1)
      add rbx,4
      cvtsi2sd xmm1,[rbx]
      mov eax,0x7fffffff
      cvtsi2sd xmm0,eax
      divsd xmm1,xmm0
      printf(" z2 is %g\n", xmm1)
      add rbx,4
      printf ("   the name is ");
      .for (j = 0: j < names: j++)
         printf ("%d ", [rbx])
         add rbx,4
      .endf
      printf("\n")
   .endf
   ret

processHits endp

BUFSIZE equ 512

selectObjects proc

   local selectBuf[BUFSIZE]:GLuint
   local hits:GLint

   glSelectBuffer(BUFSIZE, &selectBuf)
   glRenderMode(GL_SELECT)

   glInitNames()
   glPushName(0)

   glPushMatrix()
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   glOrtho(0.0, 5.0, 0.0, 5.0, 0.0, 10.0)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   glLoadName(1)
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -5.0)
   glLoadName(2)
   drawTriangle(2.0, 7.0, 3.0, 7.0, 2.5, 8.0, -5.0)
   glLoadName(3)
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, 0.0)
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -10.0)
   glPopMatrix()
   glFlush()

   mov hits,glRenderMode(GL_RENDER)
   processHits(hits, &selectBuf)
   ret

selectObjects endp

init proc

   glEnable(GL_DEPTH_TEST)
   glShadeModel(GL_FLAT)
   ret

init endp

display proc

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
   drawScene()
   selectObjects()
   glFlush()
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
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_DEPTH)
   glutInitWindowSize(200, 200)
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
