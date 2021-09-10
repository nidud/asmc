;
; https://www.opengl.org/archives/resources/code/samples/redbook/quadric.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

.data
startList GLuint ?

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

errorCallback proc errorCode:GLenum

   local estring:ptr GLubyte

   mov estring,gluErrorString(errorCode)
   fprintf(&stderr, "Quadric Error: %s\n", estring)
   exit(0)
   ret

errorCallback endp

init proc

   .data

   qobj             PVOID 0 ;GLUquadricObj *
   mat_ambient      GLfloat 0.5, 0.5, 0.5, 1.0
   mat_specular     GLfloat 1.0, 1.0, 1.0, 1.0
   mat_shininess    GLfloat 50.0
   light_position   GLfloat 1.0, 1.0, 1.0, 0.0
   model_ambient    GLfloat 0.5, 0.5, 0.5, 1.0

   .code

   glClearColor(0.0, 0.0, 0.0, 0.0)

   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialfv(GL_FRONT, GL_SHININESS, &mat_shininess)
   glLightfv(GL_LIGHT0, GL_POSITION, &light_position)
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &model_ambient)

   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   glEnable(GL_DEPTH_TEST)

   mov startList,glGenLists(4)
   mov qobj,gluNewQuadric()
   gluQuadricCallback(qobj, GLU_ERROR, &errorCallback)

   gluQuadricDrawStyle(qobj, GLU_FILL)
   gluQuadricNormals(qobj, GLU_SMOOTH)
   glNewList(startList, GL_COMPILE)
   gluSphere(qobj, 0.75, 15, 10)
   glEndList()

   gluQuadricDrawStyle(qobj, GLU_FILL)
   gluQuadricNormals(qobj, GLU_FLAT)
   mov ecx,startList
   add ecx,1
   glNewList(ecx, GL_COMPILE)
   gluCylinder(qobj, 0.5, 0.3, 1.0, 15, 5)
   glEndList()

   gluQuadricDrawStyle(qobj, GLU_LINE)
   gluQuadricNormals(qobj, GLU_NONE)
   mov ecx,startList
   add ecx,2
   glNewList(ecx, GL_COMPILE)
   gluDisk(qobj, 0.25, 1.0, 20, 4)
   glEndList()

   gluQuadricDrawStyle(qobj, GLU_SILHOUETTE)
   gluQuadricNormals(qobj, GLU_NONE)
   mov ecx,startList
   add ecx,3
   glNewList(ecx, GL_COMPILE)
   gluPartialDisk(qobj, 0.0, 1.0, 20, 4, 0.0, 225.0)
   glEndList()
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
   glPushMatrix()

   glEnable(GL_LIGHTING)
   glShadeModel(GL_SMOOTH)
   glTranslatef(-1.0, -1.0, 0.0)
   glCallList(startList)

   glShadeModel(GL_FLAT)
   glTranslatef(0.0, 2.0, 0.0)
   glPushMatrix()
   glRotatef(300.0, 1.0, 0.0, 0.0)
   mov ecx,startList
   add ecx,1
   glCallList(ecx)
   glPopMatrix()

   glDisable(GL_LIGHTING)
   glColor3f(0.0, 1.0, 1.0)
   glTranslatef(2.0, -2.0, 0.0)
   mov ecx,startList
   add ecx,2
   glCallList(ecx)

   glColor3f(1.0, 1.0, 0.0)
   glTranslatef(0.0, 2.0, 0.0)
   mov ecx,startList
   add ecx,3
   glCallList(ecx)

   glPopMatrix()
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm0,w
   cvtsi2sd xmm1,h
   .if w <= h
      divsd xmm1,xmm0
      movsd xmm2,xmm1
      movsd xmm3,xmm1
      mulsd xmm2,-2.5
      mulsd xmm3,2.5
      glOrtho(-2.5, 2.5, xmm2, xmm3, -10.0, 10.0)
   .else
      divsd xmm0,xmm1
      movsd xmm1,xmm0
      mulsd xmm0,-2.5
      mulsd xmm1,2.5
      glOrtho(xmm0, xmm1, -2.5, 2.5, -10.0, 10.0)
   .endif
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
