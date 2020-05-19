;
; https://www.opengl.org/archives/resources/code/samples/redbook/varray.c
;
include GL/glut.inc
include stdio.inc

ifdef GL_VERSION_1_1
POINTER         equ 1
INTERLEAVED     equ 2

DRAWARRAY       equ 1
ARRAYELEMENT    equ 2
DRAWELEMENTS    equ 3
.data
setupMethod int_t POINTER;
derefMethod int_t DRAWARRAY;

.code

setupPointers proc
   .data
   vertices GLint 25, 25,
                       100, 325,
                       175, 25,
                       175, 325,
                       250, 25,
                       325, 325
   colors GLfloat 1.0, 0.2, 0.2,
                       0.2, 0.2, 1.0,
                       0.8, 1.0, 0.2,
                       0.75, 0.75, 0.75,
                       0.35, 0.35, 0.35,
                       0.5, 0.5, 0.5

   .code
   glEnableClientState (GL_VERTEX_ARRAY);
   glEnableClientState (GL_COLOR_ARRAY);

   glVertexPointer (2, GL_INT, 0, &vertices);
   glColorPointer (3, GL_FLOAT, 0, &colors);
   ret

setupPointers endp

setupInterleave proc
   .data
   intertwined GLfloat \
      1.0, 0.2, 1.0, 100.0, 100.0, 0.0,
       1.0, 0.2, 0.2, 0.0, 200.0, 0.0,
       1.0, 1.0, 0.2, 100.0, 300.0, 0.0,
       0.2, 1.0, 0.2, 200.0, 300.0, 0.0,
       0.2, 1.0, 1.0, 300.0, 200.0, 0.0,
       0.2, 0.2, 1.0, 200.0, 100.0, 0.0
   .code
   glInterleavedArrays (GL_C3F_V3F, 0, &intertwined);
   ret

setupInterleave endp

init proc

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   setupPointers ();
   ret

init endp

display proc

   glClear (GL_COLOR_BUFFER_BIT);

   .if (derefMethod == DRAWARRAY)
      glDrawArrays (GL_TRIANGLES, 0, 6);
   .elseif (derefMethod == ARRAYELEMENT)
      glBegin (GL_TRIANGLES);
      glArrayElement (2);
      glArrayElement (3);
      glArrayElement (5);
      glEnd ();

   .elseif (derefMethod == DRAWELEMENTS)
      .data
      indices GLuint 0, 1, 3, 4
      .code

      glDrawElements (GL_POLYGON, 4, GL_UNSIGNED_INT, &indices)
   .endif
   glFlush ();
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport (0, 0, w, h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   cvtsi2sd xmm1,w
   cvtsi2sd xmm3,h
   gluOrtho2D (0.0, xmm1, 0.0, xmm3)
   ret

reshape endp

mouse proc button:int_t, state:int_t, x:int_t, y:int_t

    .switch button
      .case GLUT_LEFT_BUTTON
         .if (state == GLUT_DOWN)
            .if (setupMethod == POINTER)
               mov setupMethod,INTERLEAVED;
               setupInterleave();

            .elseif (setupMethod == INTERLEAVED)
               mov setupMethod,POINTER
               setupPointers();
            .endif
            glutPostRedisplay();
         .endif
         .endc
      .case GLUT_MIDDLE_BUTTON
      .case GLUT_RIGHT_BUTTON
         .if (state == GLUT_DOWN)
            .if (derefMethod == DRAWARRAY)
               mov derefMethod,ARRAYELEMENT
            .elseif (derefMethod == ARRAYELEMENT)
               mov derefMethod,DRAWELEMENTS;
            .elseif (derefMethod == DRAWELEMENTS)
               mov derefMethod,DRAWARRAY
            .endif
            glutPostRedisplay();
         .endif
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
   glutInitWindowSize(350, 350)
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

else
main proc argc:int_t, argv:array_t
    fprintf(&stderr, "This program demonstrates a feature which is not in OpenGL Version 1.0.\n");
    fprintf(&stderr, "If your implementation of OpenGL Version 1.0 has the right extensions,\n");
    fprintf(&stderr, "you may be able to modify this program to make it run.\n");
   xor eax,eax
   ret
main endp
endif
    end _tstart
