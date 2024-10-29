Asmc Macro Assembler Reference

## list pragma

Starts listing of statements.

- .**pragma** list(push, _b_)
- .**pragma** list(pop)

_push_

Pushes the current [list](dot-list.md) value on the internal stack, and sets the current list value to _b_.

_pop_

Removes the record from the top of the internal stack and sets this as the current list value.

```
some_file.asm - list is 0
...
.pragma list(push, 1) - list is now 1
...
.pragma list(pop) - list is 0 again
...
```
#### See Also

[Pragma directive](dot-pragma.md)
