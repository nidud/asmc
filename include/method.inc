ifndef __INC_METHOD
__INC_METHOD equ <>
include malloc.inc
.xlist

    option cstack:on

METHOD macro entry, args:vararg
    local __type, __ptr
ifnb <args>
    __type typedef proto :ptr, &args
else
    __type typedef proto :ptr
endif
    __ptr typedef ptr __type
    entry __ptr ?
    endm

_CLASSDEF macro class, args:vararg
    P&class& typedef ptr class
ifnb <args>
    &class&::&class& proto :P&class&, &args
else
    &class&::&class& proto :P&class&
endif
class struct size_t
    exitm<lpVtbl PVOID ?>
    endm

_CLASSVTBL macro class
    class ends
    exitm<&class&Vtbl struct size_t>
    endm

_CLASSEND macro class
    exitm<&class&Vtbl ends>
    endm

.list
endif
