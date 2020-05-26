;
; https://www.opengl.org/archives/resources/code/samples/redbook/surface.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

.data
ctlpoints GLfloat 4*4*3 dup(?)
theNurb ptr_t 0 ; GLUnurbsObj *
showPoints int_t 0

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

init_surface proc

   .for (r8 = &ctlpoints, ecx = 0: ecx < 4: ecx++)
      .for (edx = 0: edx < 4: edx++)

         imul       eax,ecx,4*3
         imul       r9d,edx,3
         add        eax,r9d
         cvtsi2ss   xmm0,ecx
         cvtsi2ss   xmm1,edx
         subss      xmm0,1.5
         subss      xmm1,1.5
         mulss      xmm0,2.0
         mulss      xmm1,2.0
         movss      [r8][rax*4][0*4],xmm0
         movss      [r8][rax*4][1*4],xmm1

         .if ((ecx == 1 || ecx == 2) && (edx == 1 || edx == 2))
            movss xmm0,3.0
            movss [r8][rax*4][2*4],xmm0
         .else
            movss xmm0,-3.0
            movss [r8][rax*4][2*4],xmm0
         .endif
      .endf
   .endf
   ret

init_surface endp

nurbsError proc errorCode:GLenum

   local estring:ptr GLubyte

   mov estring,gluErrorString(errorCode)
   fprintf(&stderr, "Nurbs Error: %s\n", estring)
   exit(0)
nurbsError endp

init proc

   .data
   mat_diffuse   GLfloat 0.7, 0.7, 0.7, 1.0
   mat_specular  GLfloat 1.0, 1.0, 1.0, 1.0
   mat_shininess GLfloat 100.0
   .code
   glClearColor(0.0, 0.0, 0.0, 0.0)
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, &mat_shininess)

   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   glEnable(GL_DEPTH_TEST)
   glEnable(GL_AUTO_NORMAL)
   glEnable(GL_NORMALIZE)

   init_surface()

   mov theNurb,gluNewNurbsRenderer()
   gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0)
   gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, 100012.0); GLU_FILL)
   gluNurbsCallback(theNurb, GLU_ERROR, &nurbsError)
   ret

init endp

display proc uses rsi rdi rbx
   .data
   knots GLfloat 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0
   .code

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)

   glPushMatrix()
   glRotatef(330.0, 1.0, 0.0, 0.0)
   glScalef(0.5, 0.5, 0.5)

   gluBeginSurface(theNurb)
   gluNurbsSurface(theNurb, 8, &knots, 8, &knots, 4 * 3, 3, &ctlpoints, 4, 4, GL_MAP2_VERTEX_3)
   gluEndSurface(theNurb)

   .if showPoints

      glPointSize(5.0)
      glDisable(GL_LIGHTING)
      glColor3f(1.0, 1.0, 0.0)
      glBegin(GL_POINTS)

      .for (esi = 0: esi < 4: esi++)
         .for (edi = 0: edi < 4: edi++)

            imul eax,esi,4*3
            imul edx,edi,3
            add  eax,edx
            lea  rcx,ctlpoints

            glVertex3f([rcx][rax*4][0*4], [rcx][rax*4][1*4], [rcx][rax*4][2*4])
         .endf
      .endf
      glEnd()
      glEnable(GL_LIGHTING)
   .endif
   glPopMatrix()
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm0,h
   divsd xmm1,xmm0
   gluPerspective(45.0, xmm1, 3.0, 8.0)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   glTranslatef(0.0, 0.0, -5.0)
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

   .switch cl
      .case 'c'
      .case 'C'
         xor showPoints,1
         glutPostRedisplay()
         .endc
      .case 27
         exit(0)
         .endc
   .endsw
   ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_DEPTH)
   glutInitWindowSize(500, 500)
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
