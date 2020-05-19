;
; https://www.opengl.org/archives/resources/code/samples/redbook/tess.c
;
include GL/glut.inc
include stdio.inc
include tchar.inc

.data
startList GLuint 0

.code

glutExit proc retval:int_t
    exit(retval)
glutExit endp

display proc

   glClear(GL_COLOR_BUFFER_BIT)
   glColor3f(1.0, 1.0, 1.0)
   glCallList(startList)
   mov ecx,startList
   add ecx,1
   glCallList(ecx)
   glFlush()
   ret

display endp

beginCallback proc which:GLenum

   glBegin(which)
   ret

beginCallback endp

errorCallback proc errorCode:GLenum

   local estring:ptr GLubyte

   mov estring,gluErrorString(errorCode)
   fprintf(&stderr, "Tessellation Error: %s\n", estring)
   exit(0)
errorCallback endp

endCallback proc

   glEnd()
   ret

endCallback endp

vertexCallback proc vertex:ptr GLvoid

   mov rcx,vertex

   glColor3dv(&[rcx+3*size_t])
   glVertex3dv(vertex)
   ret

vertexCallback endp

combineCallback proc coords:ptr GLdouble,
                     vertex_data:ptr GLdouble,
                     weight:ptr GLdouble, dataOut:ptr ptr GLdouble

   local vertex:ptr GLdouble
   local i:int_t

   mov vertex,malloc(6 * sizeof(GLdouble))
   mov rdx,rax
   mov rcx,coords
   mov rax,[rcx]
   mov [rdx],rax
   mov rax,[rcx+8]
   mov [rdx+8],rax
   mov rax,[rcx+16]
   mov [rdx+16],rax

    .for (rax = weight, rdx = vertex_data, r8 = vertex,
         ecx = 3: ecx < 7: ecx++)

        movsd xmm0,[rax+0x00]
        movsd xmm1,[rax+0x08]
        movsd xmm2,[rax+0x10]
        movsd xmm3,[rax+0x18]
        mulsd xmm0,[rdx+0x00]
        mulsd xmm1,[rdx+0x08]
        mulsd xmm2,[rdx+0x10]
        mulsd xmm3,[rdx+0x18]
        addsd xmm0,xmm1
        addsd xmm0,xmm2
        addsd xmm0,xmm3
        movsd [r8+rcx*8],xmm0
    .endf
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

   .data
   rect GLdouble 50.0, 50.0, 0.0,
                 200.0, 50.0, 0.0,
                 200.0, 200.0, 0.0,
                 50.0, 200.0, 0.0
   tri GLdouble  75.0, 75.0, 0.0,
                 125.0, 175.0, 0.0,
                 175.0, 75.0, 0.0
   star GLdouble 250.0, 50.0, 0.0, 1.0, 0.0, 1.0,
                 325.0, 200.0, 0.0, 1.0, 1.0, 0.0,
                 400.0, 50.0, 0.0, 0.0, 1.0, 1.0,
                 250.0, 150.0, 0.0, 1.0, 0.0, 0.0,
                 400.0, 150.0, 0.0, 0.0, 1.0, 0.0
   .code

   .new tobj:ptr_t ;GLUtesselator *

   glClearColor(0.0, 0.0, 0.0, 0.0)

   mov startList,glGenLists(2)
   mov tobj,gluNewTess()
   gluTessCallback(tobj, GLU_TESS_VERTEX, &glVertex3dvCallback)
   gluTessCallback(tobj, GLU_TESS_BEGIN, &beginCallback)
   gluTessCallback(tobj, GLU_TESS_END, &endCallback)
   gluTessCallback(tobj, GLU_TESS_ERROR, &errorCallback)

   glNewList(startList, GL_COMPILE)
   glShadeModel(GL_FLAT)
   gluTessBeginPolygon(tobj, NULL)
      gluTessBeginContour(tobj)
         gluTessVertex(tobj, &rect[0*8*3], &rect[0*8*3])
         gluTessVertex(tobj, &rect[1*8*3], &rect[1*8*3])
         gluTessVertex(tobj, &rect[2*8*3], &rect[2*8*3])
         gluTessVertex(tobj, &rect[3*8*3], &rect[3*8*3])
      gluTessEndContour(tobj)
      gluTessBeginContour(tobj)
         gluTessVertex(tobj, &tri[0*8*3], &tri[0*8*3])
         gluTessVertex(tobj, &tri[1*8*3], &tri[1*8*3])
         gluTessVertex(tobj, &tri[2*8*3], &tri[2*8*3])
      gluTessEndContour(tobj)
   gluTessEndPolygon(tobj)
   glEndList()

   gluTessCallback(tobj, GLU_TESS_VERTEX, &vertexCallback)
   gluTessCallback(tobj, GLU_TESS_BEGIN, &beginCallback)
   gluTessCallback(tobj, GLU_TESS_END, &endCallback)
   gluTessCallback(tobj, GLU_TESS_ERROR, &errorCallback)
   gluTessCallback(tobj, GLU_TESS_COMBINE, &combineCallback)

   mov ecx,startList
   add ecx,1
   glNewList(ecx, GL_COMPILE)
   glShadeModel(GL_SMOOTH)
   gluTessProperty(tobj, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_POSITIVE)
   gluTessBeginPolygon(tobj, NULL)
      gluTessBeginContour(tobj)
         gluTessVertex(tobj, &star[0*8*6], &star[0*8*6])
         gluTessVertex(tobj, &star[1*8*6], &star[1*8*6])
         gluTessVertex(tobj, &star[2*8*6], &star[2*8*6])
         gluTessVertex(tobj, &star[3*8*6], &star[3*8*6])
         gluTessVertex(tobj, &star[4*8*6], &star[4*8*6])
      gluTessEndContour(tobj)
   gluTessEndPolygon(tobj)
   glEndList()
   gluDeleteTess(tobj)
   ret

init endp

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

   .if key == 27
        exit(0)
   .endif
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
