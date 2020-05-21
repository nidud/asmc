;
; https://www.opengl.org/archives/resources/code/samples/redbook/aapoly.c
;
include GL/glut.inc
include stdio.inc
include string.inc

.data
polySmooth GLboolean GL_TRUE

.code

init proc

   glCullFace(GL_BACK)
   glEnable(GL_CULL_FACE)
   glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE)
   glClearColor(0.0, 0.0, 0.0, 0.0)
   ret

init endp

NFACE equ 6
NVERT equ 8

drawCube proc x0:GLdouble, x1:GLdouble, y0:GLdouble, y1:GLdouble,
        z0:GLdouble, z1:GLdouble
   .data
   v GLfloat 8*3 dup(?)
   c GLfloat 0.0, 0.0, 0.0, 1.0,  1.0, 0.0, 0.0, 1.0,
             0.0, 1.0, 0.0, 1.0,  1.0, 1.0, 0.0, 1.0,
             0.0, 0.0, 1.0, 1.0,  1.0, 0.0, 1.0, 1.0,
             0.0, 1.0, 1.0, 1.0,  1.0, 1.0, 1.0, 1.0

   indices GLubyte 4, 5, 6, 7,  2, 3, 7, 6,  0, 4, 7, 3,
                   0, 1, 5, 4,  1, 5, 6, 2,  0, 3, 2, 1
   .code

   cvtsd2ss xmm0,xmm0
   movss v[0*12+0*4],xmm0
   movss v[3*12+0*4],xmm0
   movss v[4*12+0*4],xmm0
   movss v[7*12+0*4],xmm0

   cvtsd2ss xmm0,xmm1
   movss v[1*12+0*4],xmm0
   movss v[2*12+0*4],xmm0
   movss v[5*12+0*4],xmm0
   movss v[6*12+0*4],xmm0

   cvtsd2ss xmm0,xmm2
   movss v[0*12+1*4],xmm0
   movss v[1*12+1*4],xmm0
   movss v[4*12+1*4],xmm0
   movss v[5*12+1*4],xmm0

   cvtsd2ss xmm0,xmm3
   movss v[2*12+1*4],xmm0
   movss v[3*12+1*4],xmm0
   movss v[6*12+1*4],xmm0
   movss v[7*12+1*4],xmm0

   movsd xmm0,z0
   cvtsd2ss xmm0,xmm0
   movss v[0*12+2*4],xmm0
   movss v[1*12+2*4],xmm0
   movss v[2*12+2*4],xmm0
   movss v[3*12+2*4],xmm0

   movsd xmm0,z1
   cvtsd2ss xmm0,xmm0
   movss v[4*12+2*4],xmm0
   movss v[5*12+2*4],xmm0
   movss v[6*12+2*4],xmm0
   movss v[7*12+2*4],xmm0

ifdef GL_VERSION_1_1
   glEnableClientState(GL_VERTEX_ARRAY)
   glEnableClientState(GL_COLOR_ARRAY)
   glVertexPointer(3, GL_FLOAT, 0, &v)
   glColorPointer(4, GL_FLOAT, 0, &c)
   glDrawElements(GL_QUADS, NFACE*4, GL_UNSIGNED_BYTE, &indices)
   glDisableClientState(GL_VERTEX_ARRAY)
   glDisableClientState(GL_COLOR_ARRAY)
else
   printf ("If this is GL Version 1.0, ");
   printf ("vertex arrays are not supported.\n");
   exit(1);
endif
    ret

drawCube endp

display proc

   .if polySmooth
      glClear(GL_COLOR_BUFFER_BIT)
      glEnable(GL_BLEND)
      glEnable(GL_POLYGON_SMOOTH)
      glDisable(GL_DEPTH_TEST)
   .else
      glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
      glDisable(GL_BLEND)
      glDisable(GL_POLYGON_SMOOTH)
      glEnable(GL_DEPTH_TEST)
   .endif

   glPushMatrix()
   glTranslatef(0.0, 0.0, -8.0)
   glRotatef(30.0, 1.0, 0.0, 0.0)
   glRotatef(60.0, 0.0, 1.0, 0.0)
   drawCube(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5)
   glPopMatrix()

   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm0,h
   cvtsi2sd xmm1,w
   divsd xmm1,xmm0
   gluPerspective(30.0, xmm1, 1.0, 20.0)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

   .switch cl
      .case 't'
      .case 'T'
         xor polySmooth,GL_TRUE
         glutPostRedisplay()
         .endc
      .case 27
         exit(0)
   .endsw
   ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_ALPHA or GLUT_DEPTH)
   glutInitWindowSize(200, 200)
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

