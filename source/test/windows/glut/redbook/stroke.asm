;
; https://www.opengl.org/archives/resources/code/samples/redbook/stroke.c
;
include GL/glut.inc
include string.inc

PT      equ 1
STROKE  equ 2
_END    equ 3

CP struct
   x    GLfloat ?
   y    GLfloat ?
   type int_t ?
CP ends

.data

Adata CP \
   {0.0, 0.0, PT}, {0.0, 9.0, PT},     {1.0, 10.0, PT}, {4.0, 10.0, PT},
   {5.0, 9.0, PT}, {5.0, 0.0, STROKE}, {0.0, 5.0, PT},  {5.0,  5.0, _END}

Edata CP \
   {5.0, 0.0, PT}, {0.0, 0.0, PT}, {0.0, 10.0, PT}, {5.0, 10.0, STROKE},
   {0.0, 5.0, PT}, {4.0, 5.0, _END}

Pdata CP \
   {0.0, 0.0, PT}, {0.0, 10.0, PT},  {4.0, 10.0, PT}, {5.0, 9.0, PT}, {5.0, 6.0, PT},
   {4.0, 5.0, PT}, {0.0, 5.0, _END}

Rdata CP \
   {0.0, 0.0, PT}, {0.0, 10.0, PT},  {4.0, 10.0, PT}, {5.0, 9.0, PT}, {5.0, 6.0, PT},
   {4.0, 5.0, PT}, {0.0, 5.0, STROKE}, {3.0, 5.0, PT}, {5.0, 0.0, _END}

Sdata CP \
   {0.0, 1.0, PT}, {1.0, 0.0, PT}, {4.0, 0.0, PT}, {5.0, 1.0, PT}, {5.0, 4.0, PT},
   {4.0, 5.0, PT}, {1.0, 5.0, PT}, {0.0, 6.0, PT}, {0.0, 9.0, PT}, {1.0, 10.0, PT},
   {4.0, 10.0, PT}, {5.0, 9.0, _END}

.code

drawLetter proc uses rbx l:ptr CP

   mov rbx,l
   glBegin(GL_LINE_STRIP)
   .while 1
      .switch ([rbx].CP.type)
         .case PT
            glVertex2fv(&[rbx].CP.x)
            .endc
         .case STROKE
            glVertex2fv(&[rbx].CP.x)
            glEnd()
            glBegin(GL_LINE_STRIP)
            .endc
         .case _END
            glVertex2fv(&[rbx].CP.x)
            glEnd()
            glTranslatef(8.0, 0.0, 0.0)
            .return
      .endsw
      add rbx,CP
   .endw
   ret

drawLetter endp

init proc uses rbx

   local base:GLuint

   glShadeModel(GL_FLAT)

   mov base,glGenLists(128)
   glListBase(base)
   mov ebx,base
   glNewList(&[ebx+'A'], GL_COMPILE)
   drawLetter(&Adata)
   glEndList()
   glNewList(&[ebx+'E'], GL_COMPILE)
   drawLetter(&Edata)
   glEndList()
   glNewList(&[ebx+'P'], GL_COMPILE)
   drawLetter(&Pdata)
   glEndList()
   glNewList(&[ebx+'R'], GL_COMPILE)
   drawLetter(&Rdata)
   glEndList()
   glNewList(&[ebx+'S'], GL_COMPILE)
   drawLetter(&Sdata)
   glEndList()
   glNewList(&[ebx+' '], GL_COMPILE)
   glTranslatef(8.0, 0.0, 0.0)
   glEndList()
   ret

init endp

.data
test1 db "A SPARE SERAPE APPEARS AS",0
test2 db "APES PREPARE RARE PEPPERS",0
.code

printStrokedString proc s:string_t

   glCallLists(strlen(s), GL_BYTE, s)
   ret

printStrokedString endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)
   glColor3f(1.0, 1.0, 1.0)
   glPushMatrix()
   glScalef(2.0, 2.0, 2.0)
   glTranslatef(10.0, 30.0, 0.0)
   printStrokedString(&test1)
   glPopMatrix()
   glPushMatrix()
   glScalef(2.0, 2.0, 2.0);
   glTranslatef(10.0, 13.0, 0.0)
   printStrokedString(&test2)
   glPopMatrix()
   glFlush()
   ret

display endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm3,h
   gluOrtho2D(0.0, xmm1, 0.0, xmm3)
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

    .switch cl
      .case ' '
         glutPostRedisplay()
         .endc
      .case 27
         exit(0)
    .endsw
    ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
   glutInitWindowSize(440, 440)
   glutCreateWindow("stroke")
   init()
   glutReshapeFunc(&reshape)
   glutDisplayFunc(&display)
   glutKeyboardFunc(&keyboard)
   glutMainLoop()
   xor eax,eax
   ret

main endp

    end _tstart
