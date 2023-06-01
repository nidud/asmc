
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

    ldr rcx,this
    ldr edx,Width
    mov [rcx].Shape.width,edx
    ret

Shape::setWidth endp

Shape::setHeight proc Height:int_t

    ldr rcx,this
    ldr edx,Height
    mov [rcx].Shape.height,edx
    ret

Shape::setHeight endp

Rectangle::getArea proc

    ldr rcx,this
    mov eax,[rcx].Shape.width
    mul [rcx].Shape.height
    ret

Rectangle::getArea endp

    .data

    vt RectangleVtbl { { Shape_setWidth, Shape_setHeight }, Rectangle_getArea }
    rc Rectangle { { vt, 0, 0 } }
    Rect ptr Rectangle rc

    end
