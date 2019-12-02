Asmc Macro Assembler Reference

## @CStr

**@CStr**( _string_ | _index_ )


Macro function that creates a string in the .DATA or .CONST segment. The macro accepts C-escape characters in the string. Strings are added to a stack and reused if duplicated strings are found. The macro returns _string label_.


**Example**

    C equ @CStr

    lea rax, C( "Create \"C\" string: %d\n" )
    lea rcx, C( "%d\n" )
    lea rdx, C( "\n" )

      * .data
      *  DS0000 sbyte "Create ",'"',"C",'"'," string: %d",10,0
      * .code
      *  lea rax, DS0000
      *  lea rcx, DS0000[23]
      *  lea rdx, DS0000[25]


**@CStr**( _index_ ) returns current string label minus _index_.


    lea rax, C("A") ; DS0900
    lea rbx, C("B") ; DS0901
    lea rcx, C("C") ; DS0902

    lea rcx, C(0)   ; DS0902
    lea rbx, C(1)   ; DS0901
    lea rax, C(2)   ; DS0900

#### See Also

[Symbols Reference](readme.md)
