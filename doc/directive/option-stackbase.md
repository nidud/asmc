Asmc Macro Assembler Reference

## OPTION STACKBASE

**OPTION STACKBASE**:_register_

Allows to change the way how stack variables - defined by the PROC and LOCAL directives - are accessed.

_register_ will be the index register that is used for accessing the stack variables. The "natural" register for accessing these variables is the [E|R]BP register ( the "frame pointer"). With OPTION STACKBASE one might set any index register as frame pointer.

OPTION STACKBASE will additionally define assembly-time variable @StackBase. The assembler will add the value of this variable to the effective address of stack variables. @StackBase can be modified just like any userdefined variable - however, it is initialized to zero by the PROC directive. The purpose for the introduction of @StackBase is to make it feasible to use the "volatile" stack-pointer (ESP/RSP) register as base for accessing stack variables.

Finally, OPTION STACKBASE will define another assembly-time variable: @ProcStatus. This variable is read-only and will allow to query information about the current procedure's status. The information that is returned by @ProcStatus is:

```
 Bit  Meaning if bit is 1

 0    inside prologue of current procedure.
 1    inside epilogue of current procedure.
 2    "frame-pointer omission" is on for procedure
 7    prologue of current procedure isn't created yet
```

#### See Also

[Option](option.md) | [Directives Reference](readme.md)
