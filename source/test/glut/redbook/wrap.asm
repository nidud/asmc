;
; https://www.opengl.org/archives/resources/code/samples/redbook/wrap.c
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

makeCheckImage proc

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
      .endf
   .endf
   ret

makeCheckImage endp

init proc

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   makeCheckImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

ifdef GL_VERSION_1_1
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
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

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
ifdef GL_VERSION_1_1
   glBindTexture(GL_TEXTURE_2D, texName);
endif

   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0)
   glVertex3f(-2.0, -1.0, 0.0);
   glTexCoord2f(0.0, 3.0)
   glVertex3f(-2.0, 1.0, 0.0);
   glTexCoord2f(3.0, 3.0)
   glVertex3f(0.0, 1.0, 0.0);
   glTexCoord2f(3.0, 0.0)
   glVertex3f(0.0, -1.0, 0.0);

   glTexCoord2f(0.0, 0.0)
   glVertex3f(1.0, -1.0, 0.0);
   glTexCoord2f(0.0, 3.0)
   glVertex3f(1.0, 1.0, 0.0);
   glTexCoord2f(3.0, 3.0)
   glVertex3f(2.41421, 1.0, -1.41421);
   glTexCoord2f(3.0, 0.0)
   glVertex3f(2.41421, -1.0, -1.41421);
   glEnd();
   glFlush();
   glDisable(GL_TEXTURE_2D);
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h);
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

    .switch cl
      .case 's'
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
         glutPostRedisplay();
         .endc
      .case 'S'
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
         glutPostRedisplay();
         .endc
      .case 't'
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
         glutPostRedisplay();
         .endc
      .case 'T'
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
         glutPostRedisplay();
         .endc
      .case 27
         exit(0);
         .endc
    .endsw
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
