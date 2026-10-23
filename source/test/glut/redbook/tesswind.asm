;
; https://www.opengl.org/archives/resources/code/samples/redbook/tesswind.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

.data
currentWinding int_t GLU_TESS_WINDING_ODD
currentShape int_t 0
tobj ptr_t 0 ;GLUtesselator *
list GLuint 0

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

makeNewLists proc uses rsi rdi rbx

   .data
   align 8
   rects GLdouble \ ; [12][3] =
       50.0, 50.0, 0.0, 300.0, 50.0, 0.0,
       300.0, 300.0, 0.0, 50.0, 300.0, 0.0,
       100.0, 100.0, 0.0, 250.0, 100.0, 0.0,
       250.0, 250.0, 0.0, 100.0, 250.0, 0.0,
       150.0, 150.0, 0.0, 200.0, 150.0, 0.0,
       200.0, 200.0, 0.0, 150.0, 200.0, 0.0
   spiral GLdouble \ ;[16][3] =
       400.0, 250.0, 0.0, 400.0, 50.0, 0.0,
       50.0, 50.0, 0.0, 50.0, 400.0, 0.0,
       350.0, 400.0, 0.0, 350.0, 100.0, 0.0,
       100.0, 100.0, 0.0, 100.0, 350.0, 0.0,
       300.0, 350.0, 0.0, 300.0, 150.0, 0.0,
       150.0, 150.0, 0.0, 150.0, 300.0, 0.0,
       250.0, 300.0, 0.0, 250.0, 200.0, 0.0,
       200.0, 200.0, 0.0, 200.0, 250.0, 0.0
   quad1 GLdouble \ ;[4][3] =
       50.0, 150.0, 0.0, 350.0, 150.0, 0.0,
       350.0, 200.0, 0.0, 50.0, 200.0, 0.0
   quad2 GLdouble \ ;[4][3] =
       100.0, 100.0, 0.0, 300.0, 100.0, 0.0,
       300.0, 350.0, 0.0, 100.0, 350.0, 0.0
   tri GLdouble \ ;[3][3] =
       200.0, 50.0, 0.0, 250.0, 300.0, 0.0,
       150.0, 300.0, 0.0

   .code

   cvtsi2sd xmm2,currentWinding
   gluTessProperty(tobj, GLU_TESS_WINDING_RULE, xmm2)

   glNewList(list, GL_COMPILE)
      gluTessBeginPolygon(tobj, NULL)
         gluTessBeginContour(tobj);
         .for (ebx = 0: ebx < 4: ebx++)
            lea rcx,rects
            imul eax,ebx,3*8
            gluTessVertex(tobj, &[rcx][rax], &[rcx][rax])
         .endf
         gluTessEndContour(tobj);
         gluTessBeginContour(tobj);
         .for (ebx = 4: ebx < 8: ebx++)
            lea rcx,rects
            imul eax,ebx,3*8
            gluTessVertex(tobj, &[rcx][rax], &[rcx][rax])
         .endf
         gluTessEndContour(tobj);
         gluTessBeginContour(tobj);
         .for (ebx = 8: ebx < 12: ebx++)
            lea rcx,rects
            imul eax,ebx,3*8
            gluTessVertex(tobj, &[rcx][rax], &[rcx][rax])
         .endf
         gluTessEndContour(tobj)
      gluTessEndPolygon(tobj)
   glEndList();

   mov ecx,list
   add ecx,1
   glNewList(ecx, GL_COMPILE);
      gluTessBeginPolygon(tobj, NULL);
         gluTessBeginContour(tobj);
         .for (ebx = 0: ebx < 4: ebx++)
            lea rcx,rects
            imul eax,ebx,3*8
            gluTessVertex(tobj, &[rcx][rax], &[rcx][rax])
         .endf
         gluTessEndContour(tobj);
         gluTessBeginContour(tobj);
         .for (ebx = 7: ebx >= 4: ebx--)
            lea rcx,rects
            imul eax,ebx,3*8
            gluTessVertex(tobj, &[rcx][rax], &[rcx][rax])
         .endf
         gluTessEndContour(tobj);
         gluTessBeginContour(tobj);
         .for (ebx = 11: ebx >= 8: ebx--)
            lea rcx,rects
            imul eax,ebx,3*8
            gluTessVertex(tobj, &[rcx][rax], &[rcx][rax])
         .endf
         gluTessEndContour(tobj);
      gluTessEndPolygon(tobj);
   glEndList();

   mov ecx,list
   add ecx,2
   glNewList(ecx, GL_COMPILE);
      gluTessBeginPolygon(tobj, NULL);
         gluTessBeginContour(tobj);
         .for (ebx = 0: ebx < 16: ebx++)
            lea rcx,spiral
            imul eax,ebx,3*8
            gluTessVertex(tobj, &[rcx][rax], &[rcx][rax])
         .endf
         gluTessEndContour(tobj);
      gluTessEndPolygon(tobj);
   glEndList();

   mov ecx,list
   add ecx,3
   glNewList(ecx, GL_COMPILE);
      gluTessBeginPolygon(tobj, NULL);
         gluTessBeginContour(tobj);
         .for (ebx = 0: ebx < 4: ebx++)
            lea rcx,quad1
            imul eax,ebx,3*8
            gluTessVertex(tobj, &[rcx][rax], &[rcx][rax])
         .endf
         gluTessEndContour(tobj);
         gluTessBeginContour(tobj);
         .for (ebx = 0: ebx < 4: ebx++)
            lea rcx,quad2
            imul eax,ebx,3*8
            gluTessVertex(tobj, &[rcx][rax], &[rcx][rax])
         .endf
         gluTessEndContour(tobj);
         gluTessBeginContour(tobj);
         .for (ebx = 0: ebx < 3: ebx++)
            lea rcx,tri
            imul eax,ebx,3*8
            gluTessVertex(tobj, &[rcx][rax], &[rcx][rax])
         .endf
         gluTessEndContour(tobj);
      gluTessEndPolygon(tobj);
   glEndList();
   ret

makeNewLists endp

display proc

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glPushMatrix();
   glCallList(list);
   glTranslatef(0.0, 500.0, 0.0);
   mov ecx,list
   add ecx,1
   glCallList(ecx)
   glTranslatef(500.0, -500.0, 0.0);
   mov ecx,list
   add ecx,2
   glCallList(ecx)
   glTranslatef(0.0, 500.0, 0.0);
   mov ecx,list
   add ecx,3
   glCallList(ecx)
   glPopMatrix();
   glFlush();
   ret

display endp

beginCallback proc which:GLenum

   glBegin(which);
   ret

beginCallback endp

errorCallback proc errorCode:GLenum

   local estring:ptr_t ;GLubyte *

   mov estring,gluErrorString(errorCode)
   fprintf(stderr, "Tessellation Error: %s\n", estring)
   exit(0);
errorCallback endp

endCallback proc

   glEnd()
   ret

endCallback endp

combineCallback proc coords:ptr GLdouble, data:ptr GLdouble,
                     weight:ptr GLdouble, dataOut:ptr ptr GLdouble

    local vertex:ptr GLdouble
    mov vertex,malloc(3 * sizeof(GLdouble))

    mov rdx,rax
    mov rcx,coords
    mov rax,[rcx]
    mov [rdx],rax
    mov rax,[rcx+8]
    mov [rdx+8],rax
    mov rax,[rcx+16]
    mov [rdx+16],rax

    mov rcx,dataOut
    mov rax,vertex
    mov [rcx],rax
    ret

combineCallback endp

glVertex3dvCallback proc v:ptr GLdouble

    glVertex3dv(v)
    ret

glVertex3dvCallback endp

init proc

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);

   mov tobj,gluNewTess()
   gluTessCallback(tobj, GLU_TESS_VERTEX, &glVertex3dvCallback);
   gluTessCallback(tobj, GLU_TESS_BEGIN, &beginCallback);
   gluTessCallback(tobj, GLU_TESS_END, &endCallback);
   gluTessCallback(tobj, GLU_TESS_ERROR, &errorCallback);
   gluTessCallback(tobj, GLU_TESS_COMBINE, &combineCallback);

   mov list,glGenLists(4);
   makeNewLists();
   ret

init endp

reshape proc w:int_t, h:int_t

   glViewport(0, 0, w, h)
   glMatrixMode(GL_PROJECTION)
   glLoadIdentity()
   cvtsi2sd xmm1,w
   cvtsi2sd xmm3,h

   .if w <= h
      divsd xmm3,xmm1
      mulsd xmm3,1000.0
      gluOrtho2D(0.0, 1000.0, 0.0, xmm3)
   .else
      divsd xmm1,xmm3
      mulsd xmm1,1000.0
      gluOrtho2D(0.0, xmm1, 0.0, 1000.0)
   .endif
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   ret

reshape endp

keyboard proc key:byte, x:int_t, y:int_t

   .switch cl
      .case 'w'
      .case 'W'
         .if (currentWinding == GLU_TESS_WINDING_ODD)
            mov currentWinding,GLU_TESS_WINDING_NONZERO
         .elseif (currentWinding == GLU_TESS_WINDING_NONZERO)
            mov currentWinding,GLU_TESS_WINDING_POSITIVE;
         .elseif (currentWinding == GLU_TESS_WINDING_POSITIVE)
            mov currentWinding,GLU_TESS_WINDING_NEGATIVE;
         .elseif (currentWinding == GLU_TESS_WINDING_NEGATIVE)
            mov currentWinding,GLU_TESS_WINDING_ABS_GEQ_TWO;
         .elseif (currentWinding == GLU_TESS_WINDING_ABS_GEQ_TWO)
            mov currentWinding,GLU_TESS_WINDING_ODD;
         .endif
         makeNewLists();
         glutPostRedisplay();
         .endc
      .case 27:
         exit(0);
         .endc
   .endsw
   ret

keyboard endp

main proc argc:int_t, argv:array_t

   glutInit(&argc, argv)
   glutInitDisplayMode(GLUT_SINGLE or GLUT_RGB)
   glutInitWindowSize(500, 500)
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
