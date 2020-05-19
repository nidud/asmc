;
; https://www.opengl.org/archives/resources/code/samples/redbook/planet.c
;
include GL/glut.inc

.data
year int_t 0
day  int_t 0

.code

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glShadeModel(GL_FLAT)
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)
   glColor3f(1.0, 1.0, 1.0)

   glPushMatrix()
   glutWireSphere(1.0, 20, 16)
   cvtsi2ss xmm0,year
   glRotatef(xmm0, 0.0, 1.0, 0.0)
   glTranslatef(2.0, 0.0, 0.0)
   cvtsi2ss xmm0,day
   glRotatef(xmm0, 0.0, 1.0, 0.0)
   glutWireSphere(0.2, 10, 8)
   glPopMatrix()
   glutSwapBuffers()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm0,h
   divsd xmm1,xmm0
   gluPerspective(60.0, xmm1, 1.0, 20.0)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

    .switch cl
      .case 'd'
         mov eax,day
         add eax,10
         mov ecx,360
         xor edx,edx
         div ecx
         mov day,edx
         glutPostRedisplay()
         .endc
      .case 'D'
         mov eax,day
         sub eax,10
         mov ecx,360
         xor edx,edx
         div ecx
         mov day,edx
         glutPostRedisplay()
         .endc
      .case 'y'
         mov eax,year
         add eax,5
         mov ecx,360
         xor edx,edx
         div ecx
         mov year,edx
         glutPostRedisplay()
         .endc
      .case 'Y'
         mov eax,year
         sub eax,5
         mov ecx,360
         xor edx,edx
         div ecx
         mov year,edx
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
