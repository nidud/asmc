;
; https://www.opengl.org/archives/resources/code/samples/redbook/teapots.c
;
include GL/glut.inc

.data
teapotList GLuint 0

.code

init proc

   .data
   ambient  GLfloat 0.0, 0.0, 0.0, 1.0
   diffuse  GLfloat 1.0, 1.0, 1.0, 1.0
   specular GLfloat 1.0, 1.0, 1.0, 1.0
   position GLfloat 0.0, 3.0, 3.0, 0.0

   lmodel_ambient   GLfloat 0.2, 0.2, 0.2, 1.0
   local_view       GLfloat 0.0

   .code
   glLightfv(GL_LIGHT0, GL_AMBIENT, &ambient)
   glLightfv(GL_LIGHT0, GL_DIFFUSE, &diffuse)
   glLightfv(GL_LIGHT0, GL_POSITION, &position)
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &lmodel_ambient)
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, &local_view)

   glFrontFace(GL_CW)
   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   glEnable(GL_AUTO_NORMAL)
   glEnable(GL_NORMALIZE)
   glEnable(GL_DEPTH_TEST)

   mov teapotList,glGenLists(1)
   glNewList(teapotList, GL_COMPILE)
   glutSolidTeapot(1.0)
   glEndList()
   ret

init endp

renderTeapot proc x:GLfloat, y:GLfloat,
   ambr:GLfloat, ambg:GLfloat, ambb:GLfloat,
   difr:GLfloat, difg:GLfloat, difb:GLfloat,
   specr:GLfloat, specg:GLfloat, specb:GLfloat, shine:GLfloat

   local mat[4]:GLfloat

   glPushMatrix()
   glTranslatef(x, y, 0.0)
   mov mat[0*4],ambr
   mov mat[1*4],ambg
   mov mat[2*4],ambb
   mov mat[3*4],1.0
   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat)
   mov mat[0*4],difr
   mov mat[1*4],difg
   mov mat[2*4],difb
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat);
   mov mat[0*4],specr
   mov mat[1*4],specg
   mov mat[2*4],specb
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat)
   movss xmm2,shine
   mulss xmm2,128.0
   glMaterialf(GL_FRONT, GL_SHININESS, xmm2)
   glCallList(teapotList)
   glPopMatrix()
   ret

renderTeapot endp

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
   renderTeapot(2.0, 17.0, 0.0215, 0.1745, 0.0215,
      0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633, 0.6);
   renderTeapot(2.0, 14.0, 0.135, 0.2225, 0.1575,
      0.54, 0.89, 0.63, 0.316228, 0.316228, 0.316228, 0.1);
   renderTeapot(2.0, 11.0, 0.05375, 0.05, 0.06625,
      0.18275, 0.17, 0.22525, 0.332741, 0.328634, 0.346435, 0.3);
   renderTeapot(2.0, 8.0, 0.25, 0.20725, 0.20725,
      1, 0.829, 0.829, 0.296648, 0.296648, 0.296648, 0.088);
   renderTeapot(2.0, 5.0, 0.1745, 0.01175, 0.01175,
      0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6);
   renderTeapot(2.0, 2.0, 0.1, 0.18725, 0.1745,
      0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1);
   renderTeapot(6.0, 17.0, 0.329412, 0.223529, 0.027451,
      0.780392, 0.568627, 0.113725, 0.992157, 0.941176, 0.807843,
      0.21794872);
   renderTeapot(6.0, 14.0, 0.2125, 0.1275, 0.054,
      0.714, 0.4284, 0.18144, 0.393548, 0.271906, 0.166721, 0.2);
   renderTeapot(6.0, 11.0, 0.25, 0.25, 0.25,
      0.4, 0.4, 0.4, 0.774597, 0.774597, 0.774597, 0.6);
   renderTeapot(6.0, 8.0, 0.19125, 0.0735, 0.0225,
      0.7038, 0.27048, 0.0828, 0.256777, 0.137622, 0.086014, 0.1);
   renderTeapot(6.0, 5.0, 0.24725, 0.1995, 0.0745,
      0.75164, 0.60648, 0.22648, 0.628281, 0.555802, 0.366065, 0.4);
   renderTeapot(6.0, 2.0, 0.19225, 0.19225, 0.19225,
      0.50754, 0.50754, 0.50754, 0.508273, 0.508273, 0.508273, 0.4);
   renderTeapot(10.0, 17.0, 0.0, 0.0, 0.0, 0.01, 0.01, 0.01,
      0.50, 0.50, 0.50, 0.25);
   renderTeapot(10.0, 14.0, 0.0, 0.1, 0.06, 0.0, 0.50980392, 0.50980392,
      0.50196078, 0.50196078, 0.50196078, 0.25);
   renderTeapot(10.0, 11.0, 0.0, 0.0, 0.0,
      0.1, 0.35, 0.1, 0.45, 0.55, 0.45, 0.25);
   renderTeapot(10.0, 8.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0,
      0.7, 0.6, 0.6, 0.25);
   renderTeapot(10.0, 5.0, 0.0, 0.0, 0.0, 0.55, 0.55, 0.55,
      0.70, 0.70, 0.70, 0.25);
   renderTeapot(10.0, 2.0, 0.0, 0.0, 0.0, 0.5, 0.5, 0.0,
      0.60, 0.60, 0.50, 0.25);
   renderTeapot(14.0, 17.0, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01,
      0.4, 0.4, 0.4, 0.078125);
   renderTeapot(14.0, 14.0, 0.0, 0.05, 0.05, 0.4, 0.5, 0.5,
      0.04, 0.7, 0.7, 0.078125);
   renderTeapot(14.0, 11.0, 0.0, 0.05, 0.0, 0.4, 0.5, 0.4,
      0.04, 0.7, 0.04, 0.078125);
   renderTeapot(14.0, 8.0, 0.05, 0.0, 0.0, 0.5, 0.4, 0.4,
      0.7, 0.04, 0.04, 0.078125);
   renderTeapot(14.0, 5.0, 0.05, 0.05, 0.05, 0.5, 0.5, 0.5,
      0.7, 0.7, 0.7, 0.078125);
   renderTeapot(14.0, 2.0, 0.05, 0.05, 0.0, 0.5, 0.5, 0.4,
      0.7, 0.7, 0.04, 0.078125);
   glFlush();
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm0,w
   cvtsi2sd xmm1,h
   .if w <= h
      divsd xmm1,xmm0
      mulsd xmm1,16.0
      glOrtho(0.0, 16.0, 0.0, xmm1, -10.0, 10.0)
   .else
      divsd xmm0,xmm1
      mulsd xmm0,16.0
      glOrtho(0.0, xmm0, 0.0, 16.0, -10.0, 10.0)
   .endif
   glMatrixMode(GL_MODELVIEW)
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
