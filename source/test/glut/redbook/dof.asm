;
; https://www.opengl.org/archives/resources/code/samples/redbook/dof.c
;
include GL/glut.inc
include math.inc
include jitter.inc


PI_ equ 3.14159265358979323846
.data
teapotList int_t 0

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

   movsd xmm0,pixdx
   mulsd xmm0,xwsize
   cvtsi2sd xmm1,viewport[2*4]
   movsd xmm2,eyedx
   mulsd xmm2,_near
   divsd xmm2,focus
   addsd xmm1,xmm2
   divsd xmm0,xmm1
   movsd x,xmm0

   movsd xmm0,pixdy
   mulsd xmm0,ywsize
   cvtsi2sd xmm1,viewport[3*4]
   addsd xmm1,xmm2
   divsd xmm0,xmm1
   movsd y,xmm0
   mov   rax,0x8000000000000000
   or    x,rax
   or    y,rax

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

   mov  rcx,eyedx
   mov  rdx,eyedy
   mov  rax,0x8000000000000000
   or   rcx,rax
   or   rdx,rax
   movq xmm0,rcx
   movq xmm1,rdx

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

   movsd top,cos(xmm0)
   movsd xmm1,sin(fov2)
   movsd xmm0,_near
   divsd xmm0,top
   divsd xmm0,xmm1
   movsd top,xmm0
   movsd bottom,xmm0
   mov   rax,0x8000000000000000
   or    bottom,rax
   mulsd xmm0,aspect
   movsd right,xmm0
   movsd left,xmm0
   or    left,rax

   accFrustum(left, right, bottom, top, _near, _far,
               pixdx, pixdy, eyedx, eyedy, focus)
   ret

accPerspective endp

init proc

   .data
   ambient      float 0.0, 0.0, 0.0, 1.0
   diffuse      float 1.0, 1.0, 1.0, 1.0
   specular     float 1.0, 1.0, 1.0, 1.0
   position     float 0.0, 3.0, 3.0, 0.0
   lmodel_ambient float 0.2, 0.2, 0.2, 1.0
   local_view   float 0.0
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

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glClearAccum(0.0, 0.0, 0.0, 0.0)

   ;; make teapot display list
   mov teapotList,glGenLists(1)
   glNewList(teapotList, GL_COMPILE)
   glutSolidTeapot(0.5)
   glEndList()
   ret

init endp

renderTeapot proc x:float, y:float, z:float,
   ambr:float, ambg:float, ambb:float,
   difr:float, difg:float, difb:float,
   specr:float, specg:float, specb:float, shine:float

   local mat[4]:float

   glPushMatrix()
   glTranslatef(x, y, z)

   mov mat[0*4],ambr
   mov mat[1*4],ambg
   mov mat[2*4],ambb
   mov mat[3*4],1.0
   glMaterialfv(GL_FRONT, GL_AMBIENT, &mat)

   mov mat[0*4],difr
   mov mat[1*4],difg
   mov mat[2*4],difb
   glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat)

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

display proc uses rsi

   local viewport[4]:int_t

   glGetIntegerv(GL_VIEWPORT, &viewport)
   glClear(GL_ACCUM_BUFFER_BIT)

   .for (esi = 0: esi < 8: esi++)
      glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
      cvtsi2sd xmm1,viewport[2*4]
      cvtsi2sd xmm0,viewport[3*4]
      divsd xmm1,xmm0
      lea rcx,j8
      cvtss2sd xmm0,[rcx+rsi*8].jitter_point.x
      cvtss2sd xmm2,[rcx+rsi*8].jitter_point.y
      mulsd xmm0,0.33
      mulsd xmm2,0.33
      accPerspective (45.0, xmm1, 1.0, 15.0, 0.0, 0.0, xmm0, xmm2, 5.0)

      ;; ruby, gold, silver, emerald, and cyan teapots
      renderTeapot(-1.1, -0.5, -4.5, 0.1745, 0.01175,
                    0.01175, 0.61424, 0.04136, 0.04136,
                    0.727811, 0.626959, 0.626959, 0.6)
      renderTeapot(-0.5, -0.5, -5.0, 0.24725, 0.1995,
                    0.0745, 0.75164, 0.60648, 0.22648,
                    0.628281, 0.555802, 0.366065, 0.4)
      renderTeapot(0.2, -0.5, -5.5, 0.19225, 0.19225,
                    0.19225, 0.50754, 0.50754, 0.50754,
                    0.508273, 0.508273, 0.508273, 0.4)
      renderTeapot(1.0, -0.5, -6.0, 0.0215, 0.1745, 0.0215,
                    0.07568, 0.61424, 0.07568, 0.633,
                    0.727811, 0.633, 0.6)
      renderTeapot(1.8, -0.5, -6.5, 0.0, 0.1, 0.06, 0.0,
                    0.50980392, 0.50980392, 0.50196078,
                    0.50196078, 0.50196078, 0.25)
      glAccum(GL_ACCUM, 0.125)
   .endf
   glAccum(GL_RETURN, 1.0)
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

   .switch key
      .case 27
         exit(0)
         .endc
    .endsw
    ret
keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB or GLUT_ACCUM or GLUT_DEPTH)
   glutInitWindowSize(400, 400)
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
