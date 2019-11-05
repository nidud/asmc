;
; https://github.com/RednibCoding/glut_startingpoint
;

include gl/glut.inc

.code

renderScene proc

    glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)

    glBegin(GL_TRIANGLES)
    glVertex3f(-0.5, -0.5, 0.0)
    glVertex3f(0.5, 0.0, 0.0)
    glVertex3f(0.0, 0.5, 0.0)
    glEnd()

    glutSwapBuffers()
    ret

renderScene endp

main proc argc:int_t, argv:array_t

    ;; init GLUT and create Window
    glutInit(&argc, argv)

    glutInitDisplayMode(GLUT_DEPTH or GLUT_DOUBLE or GLUT_RGBA)
    glutInitWindowPosition(100, 100)
    glutInitWindowSize(320, 320)

    glutCreateWindow("Simple GLUT")

    ;; register callbacks
    glutDisplayFunc(&renderScene)

    ;; enter GLUT event processing cycle
    glutMainLoop()

    mov eax,1
    ret

main endp

    end
