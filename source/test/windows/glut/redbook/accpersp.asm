;
; https://www.opengl.org/archives/resources/code/samples/redbook/accpersp.c
;
include GL/glut.inc
include math.inc
include jitter.inc


PI_ equ 3.14159265358979323846

.code

accFrustum proc left:double, right:double, bottom:double,
   top:double, _near:double, _far:double, pixdx:double,
   pixdy:double, eyedx:double, eyedy:double, focus:double

   local xwsize:double, ywsize:double
   local x:double, y:double
   local viewport[4]:int_t

   subsd xmm1,xmm0 ; left
   movsd xwsize,xmm1
   subsd xmm3,xmm2 ; bottom
   movsd ywsize,xmm3

   glGetIntegerv(GL_VIEWPORT, &viewport)

   movsd xmm3,8000000000000000r
   movsd xmm2,eyedx
   mulsd xmm2,_near
   divsd xmm2,focus

   movsd xmm0,pixdx
   mulsd xmm0,xwsize
   cvtsi2sd xmm1,viewport[2*4]
   divsd xmm0,xmm1
   addsd xmm0,xmm2
   xorps xmm0,xmm3
   movsd x,xmm0

   movsd xmm0,pixdy
   mulsd xmm0,ywsize
   cvtsi2sd xmm1,viewport[3*4]
   divsd xmm0,xmm1
   addsd xmm0,xmm2
   xorps xmm0,xmm3
   movsd y,xmm0

   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()

   movsd xmm0,left
   addsd xmm0,x
   movsd xmm1,right
   addsd xmm1,x
   movsd xmm2,bottom
   addsd xmm2,y
   movsd xmm3,top
   addsd xmm3,y

   glFrustum(xmm0, xmm1, xmm2, xmm3, _near, _far)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()

   movsd xmm0,eyedx
   movsd xmm1,eyedy
   movsd xmm2,8000000000000000r
   xorps xmm0,xmm2
   xorps xmm1,xmm2

   glTranslatef(xmm0, xmm1, 0.0)
   ret

accFrustum endp

accPerspective proc fovy:double, aspect:double,
   _near:double, _far:double, pixdx:double, pixdy:double,
   eyedx:double, eyedy:double, focus:double

   local fov2:double,left:double,right:double,bottom:double,top:double

   mulsd xmm0,PI_
   divsd xmm0,180.0
   divsd xmm0,2.0
   movsd fov2,xmm0

   movsd top,sin(xmm0)
   cos(fov2)
   divsd xmm0,top
   movsd xmm1,_near
   divsd xmm1,xmm0
   movsd xmm3,xmm1 ; top = near / (cos(fov2) / sin(fov2))

   movsd xmm4,8000000000000000r
   movsd xmm2,xmm1
   xorps xmm2,xmm4 ; bottom = -top

   mulsd xmm1,aspect
   movsd xmm0,xmm1 ; right = top * aspect
   xorps xmm0,xmm4 ; left = -right

   accFrustum(xmm0, xmm1, xmm2, xmm3, _near, _far, pixdx, pixdy, eyedx, eyedy, focus)
   ret

accPerspective endp

init proc

   .data
   mat_ambient  GLfloat 1.0, 1.0, 1.0, 1.0
   mat_specular GLfloat 1.0, 1.0, 1.0, 1.0
   light_position GLfloat 0.0, 0.0, 10.0, 1.0
   lm_ambient   GLfloat 0.2, 0.2, 0.2, 1.0
   .code

   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient)
   glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular)
   glMaterialf(GL_FRONT, GL_SHININESS, 50.0)
   glLightfv(GL_LIGHT0, GL_POSITION, &light_position)
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &lm_ambient)

   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   glEnable(GL_DEPTH_TEST)
   glShadeModel(GL_FLAT)

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glClearAccum(0.0, 0.0, 0.0, 0.0)
   ret
init endp

displayObjects proc

    .data
    torus_diffuse   real4 0.7, 0.7, 0.0, 1.0
    cube_diffuse    real4 0.0, 0.7, 0.7, 1.0
    sphere_diffuse  real4 0.7, 0.0, 0.7, 1.0
    octa_diffuse    real4 0.7, 0.4, 0.4, 1.0

    .code
    glPushMatrix()

    glTranslatef (0.0, 0.0, -5.0)
    glRotatef (30.0, 1.0, 0.0, 0.0)

   glPushMatrix ();
   glTranslatef (-0.80, 0.35, 0.0);
   glRotatef (100.0, 1.0, 0.0, 0.0);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &torus_diffuse);
   glutSolidTorus (0.275, 0.85, 16, 16);
   glPopMatrix ();

   glPushMatrix ();
   glTranslatef (-0.75, -0.50, 0.0);
   glRotatef (45.0, 0.0, 0.0, 1.0);
   glRotatef (45.0, 1.0, 0.0, 0.0);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &cube_diffuse);
   glutSolidCube (1.5);
   glPopMatrix ();

   glPushMatrix ();
   glTranslatef (0.75, 0.60, 0.0);
   glRotatef (30.0, 1.0, 0.0, 0.0);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &sphere_diffuse);
   glutSolidSphere (1.0, 16, 16);
   glPopMatrix ();

   glPushMatrix ();
   glTranslatef (0.70, -0.90, 0.25);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &octa_diffuse);
   glutSolidOctahedron ();
   glPopMatrix ();

   glPopMatrix ();
   ret

displayObjects endp

ACSIZE  equ 8

display proc uses rsi rdi

   local viewport[4]:GLint

   glGetIntegerv(GL_VIEWPORT, &viewport)

   glClear(GL_ACCUM_BUFFER_BIT);
    .for (rdi = &j8, esi = 0: esi < ACSIZE: esi++, rdi += 8)
      glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)

      cvtss2sd xmm4,[rdi].jitter_point.x
      cvtss2sd xmm5,[rdi].jitter_point.y
      cvtsi2sd xmm1,viewport[2*4]
      cvtsi2sd xmm0,viewport[3*4]
      divsd xmm1,xmm0

      accPerspective (50.0, xmm1, 1.0, 15.0, xmm4, xmm5, 0.0, 0.0, 1.0)
      displayObjects()
      glAccum(GL_ACCUM, 1.0/8.0)
   .endf
   glAccum(GL_RETURN, 1.0)
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
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
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_ACCUM or GLUT_DEPTH)
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
