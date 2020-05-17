;
; https://www.opengl.org/archives/resources/code/samples/redbook/checker.c
;
include GL/glut.inc
include stdio.inc

checkImageWidth  equ 64
checkImageHeight equ 64

.data?
checkImage GLubyte checkImageHeight * checkImageWidth * 4 dup(?)

ifdef GL_VERSION_1_1
.data
texName GLuint 0
endif

.code

makeCheckImage proc uses rsi rdi rbx

   .for (esi = 0: esi < checkImageHeight: esi++)
      .for (edi = 0: edi < checkImageWidth: edi++)

         mov  eax,esi
         and  eax,8
         sete al
         mov  edx,edi
         and  edx,8
         sete dl
         xor  edx,eax
         mov  eax,edx
         sal  eax,8
         sub  eax,edx
         imul ecx,esi,checkImageWidth * 4
         lea  rdx,checkImage
         add  rdx,rcx
         mov  [rdx+rdi*4+0],al
         mov  [rdx+rdi*4+1],al
         mov  [rdx+rdi*4+2],al
         mov  byte ptr [rdx+rdi*4+3],255
      .endf
   .endf
   ret

makeCheckImage endp

init proc

   glClearColor (0.0, 0.0, 0.0, 0.0)
   glShadeModel(GL_FLAT)
   glEnable(GL_DEPTH_TEST)

   makeCheckImage()
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1)

ifdef GL_VERSION_1_1
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName)
endif

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
ifdef GL_VERSION_1_1
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,
                0, GL_RGBA, GL_UNSIGNED_BYTE, &checkImage);
else
   glTexImage2D(GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight,
                0, GL_RGBA, GL_UNSIGNED_BYTE, &checkImage);
endif
   ret
init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
   glEnable(GL_TEXTURE_2D)
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)
ifdef GL_VERSION_1_1
   glBindTexture(GL_TEXTURE_2D, texName)
endif

   glBegin(GL_QUADS)
   glTexCoord2f(0.0, 0.0)
   glVertex3f(-2.0, -1.0, 0.0)
   glTexCoord2f(0.0, 1.0)
   glVertex3f(-2.0, 1.0, 0.0)
   glTexCoord2f(1.0, 1.0)
   glVertex3f(0.0, 1.0, 0.0)
   glTexCoord2f(1.0, 0.0)
   glVertex3f(0.0, -1.0, 0.0)

   glTexCoord2f(0.0, 0.0)
   glVertex3f(1.0, -1.0, 0.0)
   glTexCoord2f(0.0, 1.0)
   glVertex3f(1.0, 1.0, 0.0)
   glTexCoord2f(1.0, 1.0)
   glVertex3f(2.41421, 1.0, -1.41421)
   glTexCoord2f(1.0, 0.0)
   glVertex3f(2.41421, -1.0, -1.41421)
   glEnd()
   glFlush()
   glDisable(GL_TEXTURE_2D)
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm0,h
   cvtsi2sd xmm1,w
   divsd xmm1,xmm0
   gluPerspective(60.0, xmm1, 1.0, 30.0)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   glTranslatef(0.0, 0.0, -3.6)
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

    end _tstart
