Asmc Macro Assembler Reference

# About Asmc

Asmc is technically a slow-burning design project to make a functional programming language out of assembly. It started as a modified version of JWasm in 2011 with some simple but specific goals:

- Remove the necessity of labels.
- Merge macro and function calls.
- Enable data declaration where you need it.

The first issue is solved by improving and adding HLL extensions, the second by removing the INVOKE keyword so a function(with brackets) is handled as a macro. The last part is solved by extending the LOCAL functionality beyond the prologue and call it .NEW.
```
.new buffer[_MAX_PATH]:char_t
.return( strcmp( rbx, strcat( strcat( strcpy( &buffer, rax ), "\\" ), rsi ) ) )
```

This approach enables implementing new features without breaking any compatibility with Masm. There is however a clear break in regards to the naming convention where, I guess in assemblers in general, the most commonly used names used as identifiers [ends up as directives](../command/option-zne.md). As the stated goal here is an attempt to create a _functional programming language_ some of these keywords was renamed or removed.

#### See Also

[Asmc Reference](../readme.md) | [Instruction Format](../directive/instruction-format.md)

