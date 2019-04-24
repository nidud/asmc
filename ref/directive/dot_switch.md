Asmc Macro Assembler Reference

## .SWITCH

**.SWITCH** [NOTEST] [C|PASCAL] [_expression_]

The switch comes in three main variants: a structured switch, as in Pascal, which takes exactly one branch, an unstructured switch, as in C, which functions as a type of goto, and a control table switch with the added possibility of testing for combinations of input values, using boolean style AND/OR conditions, and potentially calling subroutines instead of just a single set of values.

The control table switch is declared with no arguments and each .CASE directive does all the testing.

    .switch
      .case strchr( esi, '<' )
      .case strchr( esi, '>' )
	    jmp around
      ...
    .endsw

The unstructured switch works as a regular C switch (default) where each .CASE directive is just a label.

    .switch eax
      .case 0: .repeat : movsb
      .case 7: movsb
      .case 6: movsb
      .case 5: movsb
      .case 4: movsb
      .case 3: movsb
      .case 2: movsb
      .case 1: movsb : .untilcxz
    .endsw

The structured switch works as a regular Pascal switch where each .CASE directive is a closed branch.

    .switch eax
      .case 1: printf("Gold medal")
      .case 2: printf("Silver medal")
      .case 3: printf("Bronze medal")
      .default
	  printf("Better luck next time")
    .endsw

The **NOTEST** option skips the range-test in the jump code.

#### See Also

[Directives Reference](readme.md) | [OPTION SWITCH](opt_switch.md) | [.CASE](dot_case.md) | [.ENDC](dot_endc.md) | [.ENDSW](dot_endsw.md)
