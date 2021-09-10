;
; https://www.opengl.org/archives/resources/code/samples/redbook/hello.c
;
include GL/glut.inc

.code

display proc

   glClear (GL_COLOR_BUFFER_BIT);

   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3f (0.25, 0.25, 0.0);
      glVertex3f (0.75, 0.25, 0.0);
      glVertex3f (0.75, 0.75, 0.0);
      glVertex3f (0.25, 0.75, 0.0);
   glEnd();

   glFlush ();
   ret

display endp

init proc

   glClearColor (0.0, 0.0, 0.0, 0.0);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
   ret

init endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
   glutInitWindowSize(250, 250)
   glutInitWindowPosition(100, 100)
   glutCreateWindow("hello")
   init()
   glutDisplayFunc(&display)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
