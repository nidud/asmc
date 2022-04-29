
public Rect

int_t typedef sdword

.class Shape

  width  int_t ?
  height int_t ?

    setWidth  proc :int_t
    setHeight proc :int_t
   .ends

.class Rectangle : public Shape

    getArea proc
   .ends

    .code

Shape::setWidth proc Width:int_t

    mov [this].Shape.width,Width
    ret

Shape::setWidth endp

Shape::setHeight proc Height:int_t

    mov [this].Shape.height,Height
    ret

Shape::setHeight endp

Rectangle::getArea proc

    mov eax,[this].Shape.width
    mul [this].Shape.height
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
