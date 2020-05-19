;
; https://www.opengl.org/archives/resources/code/samples/redbook/
;
include GL/glut.inc
include stdio.inc
include tchar.inc

checkImageWidth     equ 64
checkImageHeight    equ 64

.data?
checkImage GLubyte checkImageHeight * checkImageWidth * 3 dup(?)

.data
zoomFactor  GLdouble 1.0
height      GLint 0

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

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
         imul ecx,esi,checkImageWidth * 3
         lea  rdx,checkImage
         add  rdx,rcx
         imul ecx,edi,3
         mov  [rdx+rcx+0],al
         mov  [rdx+rcx+1],al
         mov  [rdx+rcx+2],al
      .endf
   .endf
   ret

makeCheckImage endp

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0)
   glShadeModel(GL_FLAT)
   makeCheckImage()
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
   ret

init endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)
   glRasterPos2i(0, 0)
   glDrawPixels(checkImageWidth, checkImageHeight, GL_RGB,
                GL_UNSIGNED_BYTE, &checkImage)
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   mov height,edx
   glViewport(0, 0, ecx, edx)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm3,h
   gluOrtho2D(0.0, xmm1, 0.0, xmm3)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   ret

reshape endp

motion proc x:int_t, y:int_t

   mov eax,height
   sub eax,edx
   glRasterPos2i(ecx, eax)
   glPixelZoom(zoomFactor, zoomFactor)
   glCopyPixels(0, 0, checkImageWidth, checkImageHeight, GL_COLOR)
   glPixelZoom(1.0, 1.0)
   glFlush()
   ret

motion endp

keyboard proc key:byte, x:int_t, y:int_t

    .switch cl
      .case 'r'
      .case 'R'
         movsd xmm0,1.0
         movsd zoomFactor,xmm0
         glutPostRedisplay()
         printf("zoomFactor reset to 1.0\n")
         .endc
      .case 'z'
         movsd xmm0,zoomFactor
         addsd xmm0,0.5
         comisd xmm0,3.0
         .ifnb
            movsd xmm0,3.0
         .endif
         movsd zoomFactor,xmm0
         printf("zoomFactor is now %4.1f\n", zoomFactor)
         .endc
      .case 'Z'
         movsd xmm0,zoomFactor
         subsd xmm0,0.5
         comisd xmm0,0.5
         .ifna
            movsd xmm0,0.5
         .endif
         movsd zoomFactor,xmm0
         printf("zoomFactor is now %4.1f\n", zoomFactor)
         .endc
      .case 27
         exit(0)
         .endc
    .endsw
    ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
   glutInitWindowSize(250, 250)
   glutInitWindowPosition(100, 100)
   mov rcx,argv
   glutCreateWindow([rcx])
   init()
   glutReshapeFunc(&reshape)
   glutDisplayFunc(&display)
   glutKeyboardFunc(&keyboard)
   glutMotionFunc(&motion)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
