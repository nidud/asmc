; WIN64SEH.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; some structures for Win64 SEH
;

; .pdata items

.template IMAGE_RUNTIME_FUNCTION_ENTRY

    BeginAddress    dd ?
    EndAddress      dd ?
    UnwindData      dd ? ; RVA of UNWIND_INFO
   .ends

; .xdata items

.enum {
    UWOP_PUSH_NONVOL     = 0, ; .PUSHREG    - push nonvolative gpr
    UWOP_ALLOC_LARGE     = 1, ; .ALLOCSTACK - alloc large-sized area on stack
    UWOP_ALLOC_SMALL     = 2, ; .ALLOCSTACK - alloc small-sized area (8-128) on stack
    UWOP_SET_FPREG       = 3, ; .SETFRAME   - set frame pointer
    UWOP_SAVE_NONVOL     = 4, ; .SAVEREG    - save nonvolative gpr using MOV instead of PUSH
    UWOP_SAVE_NONVOL_FAR = 5, ; .SAVEREG    - save nonvolative gpr using MOV instead of PUSH
    UWOP_SAVE_XMM        = 6, ;
    UWOP_SAVE_XMM_FAR    = 7, ;
    UWOP_SAVE_XMM128     = 8, ; .SAVEXMM128 - save all 128bits of nonvolative XMM register on stack
    UWOP_SAVE_XMM128_FAR = 9, ; .SAVEXMM128 - save all 128bits of nonvolative XMM register on stack
    UWOP_PUSH_MACHFRAME  = 10 ; .PUSHFRAME  - push a machine frame ( SS, RSP, EFL, CS, RIP [ERRCODE] )
    }

.template UNWIND_CODE
    union
     struct
      CodeOffset    db ?    ; offset within prolog
      unwind        db ?
     ends
     FrameOffset    dw ?
    ends
   .inline UnwindOp fastcall {
        mov al,[this].UNWIND_CODE.unwind
        and eax,0x0F
        }
   .inline OpInfo fastcall {
        movzx eax,[this].UNWIND_CODE.unwind
        shr eax,4
        }
   .ends


.enum {
    UNW_FLAG_NHANDLER = 0,
    UNW_FLAG_EHANDLER = 1, ;; function to examine exceptions
    UNW_FLAG_UHANDLER = 2, ;; function to unwind an exception
    UNW_FLAG_FHANDLER = 3, ;; inofficial, is E+U
    UNW_FLAG_CHAININFO = 4
    }

.template UNWIND_INFO

    version         db ?
    SizeOfProlog    db ?    ; size of prolog in bytes
    CountOfCodes    db ?    ; number of UNWIND_CODE entries
    register        db ?
if 0
    UnwindCode      UNWIND_CODE 1 dup(<>) ; unwind codes array
    union
     ExceptionHandler dd ?  ; if UNW_FLAG_EHANDLER or UNW_FLAG_UHANDLER is set: RVA of language specific handler
     FunctionEntry  dd ?    ; if UNW_FLAG_CHAININFO is set: see IMAGE_RUNTIME_FUNCTION_ENTRY
    ends
    ExceptionData   dd 1 dup(?)
endif

   .inline Version fastcall {
        mov al,[this].UNWIND_INFO.version
        and eax,0x03        ; is 1
        }
   .inline Flags fastcall {
        movzx eax,[this].UNWIND_INFO.version
        shr eax,2           ; see UNW_FLAG_ values
        }
   .inline FrameRegister fastcall {
        mov al,[this].UNWIND_INFO.register
        and eax,0x0F        ; if nonzero, function uses a frame pointer
        }
   .inline FrameOffset fastcall {
        movzx eax,[this].UNWIND_INFO.register
        shr eax,4           ; offset frame reg from RSP * 16
        }
   .ends

define UNW_VERSION 1

