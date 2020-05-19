;
; https://www.opengl.org/archives/resources/code/samples/redbook/texgen.c
;
include GL/glut.inc
include stdio.inc

stripeImageWidth equ 32

.data
stripeImage GLubyte 4*stripeImageWidth dup(?)

ifdef GL_VERSION_1_1
texName GLuint 0
endif

.code

makeStripeImage proc

    .for (r8 = &stripeImage, ecx = 0: ecx < stripeImageWidth: ecx++)

        xor eax,eax
        .if ecx <= 4
            mov al,255
        .endif
        mov [r8+rcx*4],al
        xor eax,eax
        .if ecx > 4
            mov al,255
        .endif
        mov [r8+rcx*4+1],al
        mov byte ptr [r8+rcx*4+2],0
        mov byte ptr [r8+rcx*4+3],255
    .endf
    ret

makeStripeImage endp

.data

xequalzero      GLfloat 1.0, 0.0, 0.0, 0.0
slanted         GLfloat 1.0, 1.0, 1.0, 0.0
currentCoeff    ptr_t 0 ; GLfloat *
currentPlane    GLenum 0
currentGenMode  GLint 0

.code

init proc

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);

   makeStripeImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

ifdef GL_VERSION_1_1
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_1D, texName);
endif
   glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
ifdef GL_VERSION_1_1
   glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, &stripeImage);
else
   glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, &stripeImage);
endif

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE)
   mov currentCoeff,&xequalzero
   mov currentGenMode,GL_OBJECT_LINEAR
   mov currentPlane,GL_OBJECT_PLANE
   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
   glTexGenfv(GL_S, currentPlane, currentCoeff);

   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_1D);
   glEnable(GL_CULL_FACE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_AUTO_NORMAL);
   glEnable(GL_NORMALIZE);
   glFrontFace(GL_CW);
   glCullFace(GL_BACK);
   glMaterialf(GL_FRONT, GL_SHININESS, 64.0);
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);

   glPushMatrix ();
   glRotatef(45.0, 0.0, 0.0, 1.0);
ifdef GL_VERSION_1_1
   glBindTexture(GL_TEXTURE_1D, texName);
endif
   glutSolidTeapot(2.0)
   glPopMatrix()
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   cvtsi2sd xmm0,h
   cvtsi2sd xmm1,w
   .if w <= h
      divsd xmm0,xmm1
      movsd xmm2,xmm0
      movsd xmm3,xmm0
      mulsd xmm2,-3.5
      mulsd xmm3,3.5
      glOrtho(-3.5, 3.5, xmm2, xmm3, -3.5, 3.5);
   .else
      divsd xmm1,xmm0
      movsd xmm0,xmm1
      mulsd xmm0,-3.5
      mulsd xmm1,3.5
      glOrtho(xmm0, xmm1, -3.5, 3.5, -3.5, 3.5);
   .endif
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

   .switch cl
      .case 'e'
      .case 'E'
         mov currentGenMode,GL_EYE_LINEAR;
         mov currentPlane,GL_EYE_PLANE;
         glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
         glTexGenfv(GL_S, currentPlane, currentCoeff);
         glutPostRedisplay();
         .endc
      .case 'o'
      .case 'O'
         mov currentGenMode,GL_OBJECT_LINEAR;
         mov currentPlane,GL_OBJECT_PLANE;
         glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
         glTexGenfv(GL_S, currentPlane, currentCoeff);
         glutPostRedisplay();
         .endc
      .case 's'
      .case 'S'
         mov currentCoeff,&slanted;
         glTexGenfv(GL_S, currentPlane, currentCoeff);
         glutPostRedisplay();
         .endc
      .case 'x'
      .case 'X'
         mov currentCoeff,&xequalzero;
         glTexGenfv(GL_S, currentPlane, currentCoeff);
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
   glutInitWindowSize(256, 256)
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
