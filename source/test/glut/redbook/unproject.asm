;
; https://www.opengl.org/archives/resources/code/samples/redbook/unproject.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

display proc

   glClear(GL_COLOR_BUFFER_BIT);
   glFlush();
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport (0, 0, w, h)
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   cvtsi2sd xmm1,w
   cvtsi2sd xmm0,h
   divsd xmm1,xmm0
   gluPerspective (45.0, xmm1, 1.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   ret

reshape endp

mouse proc button:int_t, state:int_t, x:int_t, y:int_t

   local viewport[4]:GLint
   local mvmatrix[16]:GLdouble, projmatrix[16]:GLdouble
   local realy:GLint
   local wx:GLdouble, wy:GLdouble, wz:GLdouble

    .switch button
      .case GLUT_LEFT_BUTTON
         .if (state == GLUT_DOWN)

            glGetIntegerv (GL_VIEWPORT, &viewport);
            glGetDoublev (GL_MODELVIEW_MATRIX, &mvmatrix);
            glGetDoublev (GL_PROJECTION_MATRIX, &projmatrix);

            mov eax,viewport[3*4]
            sub eax,y
            sub eax,1
            mov realy,eax

            printf ("Coordinates at cursor are (%4d, %4d)\n", x, realy);
            cvtsi2sd xmm0,x
            cvtsi2sd xmm1,realy
            gluUnProject (xmm0, xmm1, 0.0,
               &mvmatrix, &projmatrix, &viewport, &wx, &wy, &wz);
            printf ("World coords at z=0.0 are (%f, %f, %f)\n",
               wx, wy, wz);
            cvtsi2sd xmm0,x
            cvtsi2sd xmm1,realy
            gluUnProject (xmm0, xmm1, 1.0,
               &mvmatrix, &projmatrix, &viewport, &wx, &wy, &wz);
            printf ("World coords at z=1.0 are (%f, %f, %f)\n",
               wx, wy, wz);
         .endif
         .endc
      .case GLUT_RIGHT_BUTTON
         .if (state == GLUT_DOWN)
            exit(0);
         .endif
         .endc
    .endsw
    ret

mouse endp

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
   glutReshapeFunc(&reshape)
   glutDisplayFunc(&display)
   glutKeyboardFunc(&keyboard)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
