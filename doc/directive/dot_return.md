Asmc Macro Assembler Reference

## .RETURN

**.RETURN** [[&][_value_]] [[.IF]]

The return statement terminates the execution of a function and returns control to the calling function. Execution resumes in the calling function at the point immediately following the call. A return statement can also return a value to the calling function.

### Real numbers and XMM vectors

Real number designation defines the size of the actual number and target size is handled later. This means that these are all valid assignments:

```assembly
real4 3C00r
real4 3F800000r
real4 3FF0000000000000r
real4 3FFF8000000000000000r
real4 3FFF0000000000000000000000000000r
```

The .return directive also follows this logic and return a float size based on the length of the number.
```assembly
.return 3C00r
.return 3F800000r
.return 3FF0000000000000r
.return 3FFF8000000000000000r
.return 3FFF0000000000000000000000000000r
```

A zero in front will also work (0FFFF0...). In addition to this a type(...) may be used to size up the returned value:
```assembly
.return real2  ( 1.0 )
.return real4  ( 1.0 )
.return real8  ( 1.0 )
.return real10 ( 1.0 )
.return real16 ( 1.0 )
```

Erroneous numbers are also allowed here:
```assembly
.return real4  ( 1.0 / 0,0 ) ; nan
.return real8  (-1.0 / 0.0 ) ; -nan
```

The first number defines the type so this will return a float (real4):
```assembly
.return 3F800000r * 2.0 / 3.0
```

A vector(16) may return anything that fits into XMM0 from bytes to oword or real2 to real16.
```assembly
.return { 1.0 }
.return { 1.0, 2.0 }
.return { 1.0, 2.0, 3.0, 4.0 }
.return { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }

.return { 1 }
.return { 1, 2 }
.return { 1, 2, 3, 4 }
.return { 1, 2, 3, 4, 5, 6, 7, 8 }
.return { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }
```

#### See Also

[Directives Reference](readme.md)
