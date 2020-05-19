;
; https://www.opengl.org/archives/resources/code/samples/redbook/robot.c
;
include GL/glut.inc

.data
shoulder int_t 0
elbow    int_t 0

.code

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glShadeModel(GL_FLAT)
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)
   glPushMatrix()
   glTranslatef(-1.0, 0.0, 0.0)
   cvtsi2ss xmm0,shoulder
   glRotatef(xmm0, 0.0, 0.0, 1.0)
   glTranslatef(1.0, 0.0, 0.0)
   glPushMatrix()
   glScalef(2.0, 0.4, 1.0)
   glutWireCube(1.0)
   glPopMatrix()

   glTranslatef (1.0, 0.0, 0.0)
   cvtsi2ss xmm0,elbow
   glRotatef(xmm0, 0.0, 0.0, 1.0)
   glTranslatef(1.0, 0.0, 0.0)
   glPushMatrix()
   glScalef(2.0, 0.4, 1.0)
   glutWireCube(1.0)
   glPopMatrix()

   glPopMatrix()
   glutSwapBuffers()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm0,h
   divsd xmm1,xmm0
   gluPerspective(65.0, xmm1, 1.0, 20.0)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   glTranslatef(0.0, 0.0, -5.0)
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

   .switch cl
      .case 's'
         mov eax,shoulder
         add eax,5
         mov ecx,360
         xor edx,edx
         div ecx
         mov shoulder,edx
         glutPostRedisplay()
         .endc
      .case 'S'
         mov eax,shoulder
         sub eax,5
         mov ecx,360
         xor edx,edx
         div ecx
         mov shoulder,edx
         glutPostRedisplay()
         .endc
      .case 'e'
         mov eax,elbow
         add eax,5
         mov ecx,360
         xor edx,edx
         div ecx
         mov elbow,edx
         glutPostRedisplay()
         .endc
      .case 'E'
         mov eax,elbow
         sub eax,5
         mov ecx,360
         xor edx,edx
         div ecx
         mov elbow,edx
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
   glutInitDisplayMode(GLUT_DOUBLE or GLUT_RGB)
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
