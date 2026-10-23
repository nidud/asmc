;
; https://www.opengl.org/archives/resources/code/samples/redbook/clip.c
;
include GL/glut.inc

.code

init proc

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT)
   ret

init endp

display proc

   .data
   eqn  GLdouble 0.0, 1.0, 0.0, 0.0
   eqn2 GLdouble 1.0, 0.0, 0.0, 0.0

   .code

   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f (1.0, 1.0, 1.0);
   glPushMatrix();
   glTranslatef (0.0, 0.0, -5.0);

   glClipPlane (GL_CLIP_PLANE0, &eqn)
   glEnable (GL_CLIP_PLANE0);

   glClipPlane (GL_CLIP_PLANE1, &eqn2);
   glEnable (GL_CLIP_PLANE1);

   glRotatef (90.0, 1.0, 0.0, 0.0);
   glutWireSphere(1.0, 20, 16);
   glPopMatrix();

   glFlush ();
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport (0, 0, ecx, edx);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   cvtsi2sd xmm1,w
   cvtsi2sd xmm0,h
   divsd xmm1,xmm0
   gluPerspective(60.0, xmm1, 1.0, 20.0)
   glMatrixMode (GL_MODELVIEW);
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
