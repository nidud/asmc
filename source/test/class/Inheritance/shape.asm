
;; https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm

include iostream

;; Base class

.class Shape

  width   int_t ?
  height  int_t ?

    .operator setWidth :int_t {
        mov [this].Shape.width,_1
        }
    .operator setHeight :int_t {
        mov [this].Shape.height,_1
        }
    .ends

;; Derived class

.class Rectangle : public Shape

    .operator getArea {
        mov eax,[this].Shape.width
        mul [this].Shape.height
        }
    .ends

    .code

main proc

  local Rect:Rectangle

    Rect.setWidth(5)
    Rect.setHeight(7)

    ;; Print the area of the object.

    cout << "Total area: " << ( Rect.getArea() ) << endl

    exit(0)

main endp

    end main
