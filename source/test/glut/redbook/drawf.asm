;
; https://www.opengl.org/archives/resources/code/samples/redbook/drawf.c
;
include GL/glut.inc

.data
rasters GLubyte \
   0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
   0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
   0xff, 0xc0, 0xff, 0xc0

.code

init proc

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
   glClearColor(0.0, 0.0, 0.0, 0.0)
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)
   glColor3f(1.0, 1.0, 1.0)
   glRasterPos2i(20, 20)
   glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, &rasters)
   glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, &rasters)
   glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, &rasters)
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm3,h
   glOrtho(0.0, xmm1, 0.0, xmm3, -1.0, 1.0)
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
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
   glutInitWindowSize(100, 100)
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
