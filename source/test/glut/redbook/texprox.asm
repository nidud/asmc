;
; https://www.opengl.org/archives/resources/code/samples/redbook/texprox.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

.code
ifdef GL_VERSION_1_1

glutExit proc retval:int_t
    exit(retval)
glutExit endp

init proc

   local proxyComponents:GLint

   glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA8, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
   glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0,
                            GL_TEXTURE_COMPONENTS, &proxyComponents);
   printf ("proxyComponents are %d\n", proxyComponents);
   .if (proxyComponents == GL_RGBA8)
      printf ("proxy allocation succeeded\n");
   .else
      printf ("proxy allocation failed\n");
   .endif

   glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA16,
                2048, 2048, 0,
                GL_RGBA, GL_UNSIGNED_SHORT, NULL);
   glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0,
                            GL_TEXTURE_COMPONENTS, &proxyComponents);
   printf ("proxyComponents are %d\n", proxyComponents);
   .if (proxyComponents == GL_RGBA16)
      printf ("proxy allocation succeeded\n");
   .else
      printf ("proxy allocation failed\n");
   .endif
   ret

init endp

display proc

   exit(0);
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport (0, 0, w, h)
   glMatrixMode (GL_PROJECTION)
   glLoadIdentity()
   ret

reshape endp

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
   glutMainLoop()
   xor eax,eax
   ret

main endp
else
int main(int argc, char** argv)
{
    fprintf (stderr, "This program demonstrates a feature which is not in OpenGL Version 1.0.\n");
    fprintf (stderr, "If your implementation of OpenGL Version 1.0 has the right extensions,\n");
    fprintf (stderr, "you may be able to modify this program to make it run.\n");
    return 0;
}
endif
    end _tstart
