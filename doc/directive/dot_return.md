Asmc Macro Assembler Reference

## .RETURN

**.RETURN** [[&][_value_]] [[.IF]]

The return statement terminates the execution of a function and returns control to the calling function. Execution resumes in the calling function at the point immediately following the call. A return statement can also return a value to the calling function.

### Real numbers and XMM vectors

Real number designation defines the size of the actual number and target size is handled later. This means that these are all valid assignments:


```assembly

    .return 3C00r
    .return 3F800000r
    .return 3FF0000000000000r
    .return 3FFF8000000000000000r
    .return 3FFF0000000000000000000000000000r
```
#### See Also

[Directives Reference](readme.md)
