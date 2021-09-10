
public Rect

.class Shape

  width  dd ?
  height dd ?

    setWidth  proc :dword
    setHeight proc :dword
    .ends

.class Rectangle : public Shape

    getArea proc

    .ends

    .code

Shape::setWidth proc Width:dword

    mov [rcx].Shape.width,edx
    ret

Shape::setWidth endp

Shape::setHeight proc Height:dword

    mov [rcx].Shape.height,edx
    ret

Shape::setHeight endp

Rectangle::getArea proc

    mov eax,[rcx].Shape.width
    mul [rcx].Shape.height
    ret

Rectangle::getArea endp

    .data

    rc_vtable RectangleVtbl {
            { Shape_setWidth, Shape_setHeight }, Rectangle_getArea
        }
    rectangle Rectangle {
            { rc_vtable, 0, 0 }
        }
    Rect ptr Rectangle rectangle

    end
