include stdio.inc

.pragma comment(linker,"/defaultlib:msvcrt.lib")

.class Shape
    width       int_t ?
    height      int_t ?
    setWidth    proc :int_t
    setHeight   proc :int_t
   .ends

.class Rectangle : public Shape
    getArea     proc
   .ends

extern Rect:ptr Rectangle

   .code

main proc

   Rect.setWidth(5)
   Rect.setHeight(7)

   printf("Total area: %d\n",  Rect.getArea() )
  .return 0

main endp

    end

