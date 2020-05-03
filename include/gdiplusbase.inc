ifndef _GDIPLUSBASE_H
_GDIPLUSBASE_H equ <>

.template GdiplusBase
    .operator delete :ptr {
        exitm <GdipFree(_1)>
    }
    .operator new :ptr {
        exitm <GdipAlloc(_1)>
    }
    .ends

.template Stack
    union
      struct
        r_ecx   dd ?
        r_eax   dd ?
        r_ebx   dd ?
        r_edx   dd ?
        r_edi   dd ?
        r_ebp   dd ?
        r_esi   dd ?
        r_esp   dd ?
      ends
      struct
        r_rcx   dq ?
        r_rbx   dq ?
        r_rdi   dq ?
        r_rsi   dq ?
      ends
      u64       qword    4 dup(?)
      u32       dword    8 dup(?)
      u16       word    16 dup(?)
      u8        byte    32 dup(?)
      i64       sqword   4 dup(?)
      i32       sdword   8 dup(?)
      i16       sword   16 dup(?)
      i8        sbyte   32 dup(?)
      float     real4    8 dup(?)
      double    real8    4 dup(?)
      quad      real16   2 dup(?)
      u128      oword    2 dup(?)
    ends
    .ends

endif


