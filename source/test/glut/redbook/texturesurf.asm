;
; https://www.opengl.org/archives/resources/code/samples/redbook/texturesurf.c
;
include GL/glut.inc
include math.inc

.data

ctrlpoints GLfloat \ ; [4][4][3] = {
    -1.5, -1.5, 4.0,  -0.5, -1.5, 2.0,
    0.5, -1.5, -1.0, 1.5, -1.5, 2.0,
    -1.5, -0.5, 1.0,  -0.5, -0.5, 3.0,
    0.5, -0.5, 0.0, 1.5, -0.5, -1.0,
    -1.5, 0.5, 4.0,  -0.5, 0.5, 0.0,
    0.5, 0.5, 3.0, 1.5, 0.5, 4.0,
    -1.5, 1.5, -2.0,  -0.5, 1.5, -2.0,
    0.5, 1.5, 0.0, 1.5, 1.5, -1.0

texpts GLfloat \ ;[2][2][2]
    0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0

.code

display proc

   glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glEvalMesh2(GL_FILL, 0, 20, 0, 20);
   glFlush()
   ret

display endp

.data
imageWidth  equ 64
imageHeight equ 64
image GLubyte 3*imageWidth*imageHeight dup(0)

.code

makeImage proc uses rsi rdi

    local ti:double, tj:double
    local r:byte, g:byte, b:byte

    lea rbx,image
    .for (esi = 0: esi < imageWidth: esi++)

        movsd xmm0,2.0*3.14159265
        cvtsi2sd xmm1,esi
        mulsd xmm0,xmm1
        divsd xmm0,64.0
        movsd ti,xmm0

        .for (edi = 0: edi < imageHeight: edi++, rbx+=3)

            movsd xmm0,2.0*3.14159265
            cvtsi2sd xmm1,edi
            mulsd xmm0,xmm1
            divsd xmm0,64.0
            movsd tj,xmm0

            sin(ti)
            addsd xmm0,1.0
            mulsd xmm0,127.0
            cvtsd2si eax,xmm0
            mov r,al

            movsd xmm0,tj
            mulsd xmm0,2.0
            cos(xmm0)
            addsd xmm0,1.0
            mulsd xmm0,127.0
            cvtsd2si eax,xmm0
            mov g,al

            movsd xmm0,tj
            addsd xmm0,ti
            cos(xmm0)
            addsd xmm0,1.0
            mulsd xmm0,127.0
            cvtsd2si eax,xmm0
            mov b,al

            mov [rbx+0],r
            mov [rbx+1],g
            mov [rbx+2],b
        .endf
    .endf
    ret

makeImage endp

init proc

   glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4, &ctrlpoints)
   glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texpts)
   glEnable(GL_MAP2_TEXTURE_COORD_2)
   glEnable(GL_MAP2_VERTEX_3);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   makeImage();
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 8449.0)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0,
                GL_RGB, GL_UNSIGNED_BYTE, &image);
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_DEPTH_TEST);
   glShadeModel (GL_FLAT);
   ret

init endp

reshape proc w:int_t, h:int_t

    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    cvtsi2sd xmm0,w
    cvtsi2sd xmm1,h
    .if w <= h
        divsd xmm1,xmm0
        movsd xmm2,xmm1
        movsd xmm3,xmm1
        mulsd xmm2,-4.0
        mulsd xmm3,4.0
        glOrtho(-4.0, 4.0, xmm2, xmm3, -4.0, 4.0);
    .else
        divsd xmm0,xmm1
        movsd xmm1,xmm0
        mulsd xmm0,-4.0
        mulsd xmm1,4.0
        glOrtho(xmm0, xmm1, -4.0, 4.0, -4.0, 4.0);
    .endif
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(85.0, 1.0, 1.0, 1.0);
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
