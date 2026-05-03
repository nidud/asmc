Asmc Macro Assembler Reference

## cref pragma

Enables listing of symbols in the symbol portion of the symbol table and browser file.

- .**pragma** cref(push, _b_)
- .**pragma** cref(pop)

_push_

Pushes the current [cref](dot-cref.md) value on the internal stack, and sets the current cref value to _b_.

_pop_

Removes the record from the top of the internal stack and sets this as the current cref value.

```
some_file.asm - cref is 0
...
.pragma cref(push, 1) - cref is now 1
...
.pragma cref(pop) - cref is 0 again
...
```
#### See Also

[Pragma directive](dot-pragma.md)
