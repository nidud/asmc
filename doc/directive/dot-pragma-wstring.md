Asmc Macro Assembler Reference

## wstring pragma

Toggles ASCII/Unicode string creation of "quoted strings".

- .**pragma** wstring(push, _b_)
- .**pragma** wstring(pop)

_push_

Pushes the current [wstring](option-wstring.md) value on the internal stack, and sets the current wstring value to _b_.

_pop_

Removes the record from the top of the internal stack and sets this as the current wstring value.

```
some_file.asm - wstring is 1
...
.pragma wstring(push, 0) - wstring is now 0
...
.pragma wstring(pop) - wstring is 1 again
...
```
#### See Also

[Pragma directive](dot-pragma.md)
