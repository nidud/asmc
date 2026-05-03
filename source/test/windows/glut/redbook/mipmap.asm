;
; https://www.opengl.org/archives/resources/code/samples/redbook/mipmap.c
;
include GL/glut.inc

.data?
mipmapImage32   GLubyte 32*32*4 dup(?)
mipmapImage16   GLubyte 16*16*4 dup(?)
mipmapImage8    GLubyte 8*8*4 dup(?)
mipmapImage4    GLubyte 4*4*4 dup(?)
mipmapImage2    GLubyte 2*2*4 dup(?)
mipmapImage1    GLubyte 1*1*4 dup(?)

ifdef GL_VERSION_1_1
texName GLuint ?
endif

.code

makeImages proc uses rsi rdi

   mov eax,255
   .for (esi = 0: esi < 32: esi++)
      .for (edi = 0: edi < 32: edi++)
         imul ecx,esi,32 * 4
         lea  rdx,mipmapImage32
         add  rdx,rcx
         mov  [rdx+rdi*4+0],al
         mov  [rdx+rdi*4+1],al
         mov  [rdx+rdi*4+2],ah
         mov  [rdx+rdi*4+3],al
      .endf
   .endf
   .for (esi = 0: esi < 16: esi++)
      .for (edi = 0: edi < 16: edi++)
         imul ecx,esi,16 * 4
         lea  rdx,mipmapImage16
         add  rdx,rcx
         mov  [rdx+rdi*4+0],al
         mov  [rdx+rdi*4+1],ah
         mov  [rdx+rdi*4+2],al
         mov  [rdx+rdi*4+3],al
      .endf
   .endf
   .for (esi = 0: esi < 8: esi++)
      .for (edi = 0: edi < 8: edi++)
         imul ecx,esi,8 * 4
         lea  rdx,mipmapImage8
         add  rdx,rcx
         mov  [rdx+rdi*4+0],al
         mov  [rdx+rdi*4+1],ah
         mov  [rdx+rdi*4+2],ah
         mov  [rdx+rdi*4+3],al
      .endf
   .endf
   .for (esi = 0: esi < 4: esi++)
      .for (edi = 0: edi < 4: edi++)
         imul ecx,esi,4 * 4
         lea  rdx,mipmapImage4
         add  rdx,rcx
         mov  [rdx+rdi*4+0],ah
         mov  [rdx+rdi*4+1],al
         mov  [rdx+rdi*4+2],ah
         mov  [rdx+rdi*4+3],al
      .endf
   .endf
   .for (rcx = &mipmapImage2, esi = 0: esi < 2: esi++)
      .for (edi = 0: edi < 2: edi++)
         imul edx,esi,2*4
         add rdx,rcx
         mov [rdx+rdi*4+0],ah
         mov [rdx+rdi*4+1],ah
         mov [rdx+rdi*4+2],al
         mov [rdx+rdi*4+3],al
      .endf
   .endf
   lea rdx,mipmapImage1
   mov [rdx+0],al
   mov [rdx+1],al
   mov [rdx+2],al
   mov [rdx+3],al
   ret

makeImages endp

init proc

   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);

   glTranslatef(0.0, 0.0, -3.6);
   makeImages();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

ifdef GL_VERSION_1_1
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
endif
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                   GL_NEAREST_MIPMAP_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, &mipmapImage32)
   glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA, 16, 16, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, &mipmapImage16)
   glTexImage2D(GL_TEXTURE_2D, 2, GL_RGBA, 8, 8, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, &mipmapImage8)
   glTexImage2D(GL_TEXTURE_2D, 3, GL_RGBA, 4, 4, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, &mipmapImage4)
   glTexImage2D(GL_TEXTURE_2D, 4, GL_RGBA, 2, 2, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, &mipmapImage2)
   glTexImage2D(GL_TEXTURE_2D, 5, GL_RGBA, 1, 1, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, &mipmapImage1)

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 8449.0)
   glEnable(GL_TEXTURE_2D);
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
ifdef GL_VERSION_1_1
   glBindTexture(GL_TEXTURE_2D, texName)
endif
   glBegin(GL_QUADS)
   glTexCoord2f(0.0, 0.0)
   glVertex3f(-2.0, -1.0, 0.0)
   glTexCoord2f(0.0, 8.0)
   glVertex3f(-2.0, 1.0, 0.0)
   glTexCoord2f(8.0, 8.0)
   glVertex3f(2000.0, 1.0, -6000.0)
   glTexCoord2f(8.0, 0.0)
   glVertex3f(2000.0, -1.0, -6000.0)
   glEnd();
   glFlush();
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm0,h
   divsd xmm1,xmm0
   gluPerspective(60.0, xmm1, 1.0, 30000.0)
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
   glutInitWindowPosition(50, 50)
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

