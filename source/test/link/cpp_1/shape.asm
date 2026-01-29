
int_t typedef sdword

.class Shape

    width       int_t ?
    height      int_t ?

    setWidth    proc :int_t
    setHeight   proc :int_t
   .ends

.class Rectangle : public Shape

    getArea     proc
   .ends

   .data
    vtable RectangleVtbl { { Shape_setWidth, Shape_setHeight }, Rectangle_getArea }
    rect   Rectangle { { vtable, 0, 0 } }
    Rect   ptr Rectangle rect

    public Rect

   .code

Shape::setWidth proc Width:int_t
    mov [rcx].Shape.width,edx
    ret
Shape::setWidth endp

Shape::setHeight proc Height:int_t
    mov [rcx].Shape.height,edx
    ret
Shape::setHeight endp

Rectangle::getArea proc
    mov eax,[rcx].Shape.width
    mul [rcx].Shape.height
    ret
Rectangle::getArea endp

    end
