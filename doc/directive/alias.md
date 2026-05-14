Asmc Macro Assembler Reference

## ALIAS

**ALIAS** &lt;alias&gt; = &lt;actual-name&gt;

The ALIAS directive creates an alternate name for a function. This lets you create multiple names for a function, or create libraries that allow the linker to map an old function to a new function.

Since ELF files don't support aliases, the ALIAS directive creates a duplicate public symbol for _actual-name_ if _actual-name_ is a public symbol.

#### See Also

[Miscellaneous](miscellaneous.md) | [Directives Reference](readme.md)
