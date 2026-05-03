
    ; 2.31.45 - fixed bug in macro local counter
    ;
    ; x maxro
    ;  local y
    ;   .new y:x --> creates a new instance for each call
    ;

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    option casemap:none, win64:auto

.template RECT

    left    sdword ?
    top     sdword ?
    right   sdword ?
    bottom  sdword ?

    .inline RECT :vararg {
        ifidn typeid(this),<RECT>
            this.mem_RECT(_1)
        else
            [rcx].RECT.typeid(this)(_1)
        endif
        }

    .inline mem_RECT :abs, :abs, :abs, :abs, :vararg {
        ifnb <_1>
            mov this.left,    _1
        endif
        ifnb <_2>
            mov this.top,     _2
        endif
        ifnb <_3>
            mov this.right,   _3
        endif
        ifnb <_4>
            mov this.bottom,  _4
        endif
        }

    .inline ptrRECT :abs, :abs, :abs, :abs {
        ifnb <_1>
            mov [this].RECT.left,    _1
        endif
        ifnb <_2>
            mov [this].RECT.top,     _2
        endif
        ifnb <_3>
            mov [this].RECT.right,   _3
        endif
        ifnb <_4>
            mov [this].RECT.bottom,  _4
        endif
        }

    .inline imm :vararg {
      local rc
       .new rc:RECT
        rc.mem_RECT(_1)
        lea rax,rc
        }

    .inline Init :abs, :abs, :abs, :abs {
        ifnb <_1>
            mov [this].RECT.left,    _1
        endif
        ifnb <_2>
            mov [this].RECT.top,     _2
        endif
        ifnb <_3>
            mov [this].RECT.right,   _3
        endif
        ifnb <_4>
            mov [this].RECT.bottom,  _4
        endif
        }
    .inline Clear {
        xor eax,eax
        mov [this],rax
        mov [this+8],rax
        }
    .ends

    .code

foo proc p:ptr RECT
    ret
foo endp

main proc

    RECT()
    RECT(1, 2, 3)

    foo( RECT(100, 200) )

    RECT() : left(0), top(0), right(0), bottom(0)

   .new RECT()       : right(1)
   .new S:RECT()     : right(2)
   .new D:ptr RECT() : right(3)

    D.Clear()
    D.Init(1, 2)

    ret

main endp

    end

