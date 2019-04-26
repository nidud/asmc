Asmc Macro Assembler Reference

## .IF

**.IF** _condition1_<br>
   _statements_<br>
   [[**.ELSEIF** _condition2_<br>
      _statements_]]<br>
   [[**.ELSE**<br>
      _statements_]]<br>
   **.ENDIF**


Generates code that tests _condition1_ (for example, AX > 7) and executes the _statements_ if that condition is true. If a .ELSE follows, its statements are executed if the original condition was false. Note that the conditions are evaluated at run time.

#### See Also

[Directives Reference](readme.md) | [Flag conditions](flags.md) | [Signed compare](signed.md) | [Return code](return.md)