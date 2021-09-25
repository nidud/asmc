Asmc Macro Assembler Reference

### .NAMESPACE

**.NAMESPACE** _name_

Declares a namespace.

This includes directives .ENUM, EQU, DEFINE, .CLASS, .COMDEF, .TEMPLATE, and data identifiers.

Example:

```assembly
include iostream

.data

.namespace box1
    box_side int_t 4
   .endn

.namespace box2
    box_side int_t 12
   .endn

.code

main proc

   .new box_side:int_t = 42

    cout << box1::box_side << endl  ; Outputs 4.
    cout << box2::box_side << endl  ; Outputs 12.
    cout << box_side << endl        ; Outputs 42.
    ret

main endp
```

#### See Also

[Directives Reference](readme.md) | [.ENDN](dot_endn.md)

