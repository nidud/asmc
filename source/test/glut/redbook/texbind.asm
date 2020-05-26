;
; https://www.opengl.org/archives/resources/code/samples/redbook/texbind.c
;
include GL/glut.inc
include stdio.inc

ifdef GL_VERSION_1_1

checkImageWidth  equ 64
checkImageHeight equ 64

.data?
checkImage GLubyte checkImageHeight * checkImageWidth * 4 dup(?)
otherImage GLubyte checkImageHeight * checkImageWidth * 4 dup(?)
texName GLuint 2 dup(?)

.code

makeCheckImages proc

   .for (r8d = 0: r8d < checkImageHeight: r8d++)
      .for (r9d = 0: r9d < checkImageWidth: r9d++)

         mov  eax,r8d
         and  eax,8
         sete al
         mov  edx,r9d
         and  edx,8
         sete dl
         xor  edx,eax
         mov  eax,edx
         sal  eax,8
         sub  eax,edx
         imul ecx,r8d,checkImageWidth * 4
         lea  rdx,checkImage
         add  rdx,rcx
         mov  [rdx+r9*4+0],al
         mov  [rdx+r9*4+1],al
         mov  [rdx+r9*4+2],al
         mov  byte ptr [rdx+r9*4+3],255

         mov  eax,r8d
         and  eax,16
         sete al
         mov  edx,r9d
         and  edx,16
         sete dl
         xor  edx,eax
         mov  eax,edx
         sal  eax,16
         sub  eax,edx
         imul ecx,r8d,checkImageWidth * 4
         lea  rdx,otherImage
         add  rdx,rcx
         mov  [rdx+r9*4+0],al
         mov  byte ptr [rdx+r9*4+1],0
         mov  byte ptr [rdx+r9*4+2],0
         mov  byte ptr [rdx+r9*4+3],255

      .endf
   .endf
   ret

makeCheckImages endp

init proc

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   makeCheckImages();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(2, &texName);
   glBindTexture(GL_TEXTURE_2D, texName[0]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                &checkImage);

   glBindTexture(GL_TEXTURE_2D, texName[4]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 8449.0)
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                &otherImage);
   glEnable(GL_TEXTURE_2D);
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);
   glBindTexture(GL_TEXTURE_2D, texName[0]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0)
   glVertex3f(-2.0, -1.0, 0.0);
   glTexCoord2f(0.0, 1.0)
   glVertex3f(-2.0, 1.0, 0.0);
   glTexCoord2f(1.0, 1.0)
   glVertex3f(0.0, 1.0, 0.0);
   glTexCoord2f(1.0, 0.0)
   glVertex3f(0.0, -1.0, 0.0);
   glEnd();
   glBindTexture(GL_TEXTURE_2D, texName[4]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0)
   glVertex3f(1.0, -1.0, 0.0);
   glTexCoord2f(0.0, 1.0)
   glVertex3f(1.0, 1.0, 0.0);
   glTexCoord2f(1.0, 1.0)
   glVertex3f(2.41421, 1.0, -1.41421);
   glTexCoord2f(1.0, 0.0)
   glVertex3f(2.41421, -1.0, -1.41421);
   glEnd();
   glFlush();
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   cvtsi2sd xmm0,h
   cvtsi2sd xmm1,w
   divsd xmm1,xmm0
   gluPerspective(60.0, xmm1, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -3.6);
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
   glutInitWindowSize(250, 250)
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
