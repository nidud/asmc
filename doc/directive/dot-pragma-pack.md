Asmc Macro Assembler Reference

## pack pragma

Specifies the [packing alignment](option-fieldalign.md) for structure, union, and class members.

- .**pragma** pack(push, _n_)
- .**pragma** pack(pop)

_push_

Pushes the current packing alignment value on the internal stack, and sets the current packing alignment value to _n_.

_pop_

Removes the record from the top of the internal stack and sets this as the current packing alignment value.

```
some_file.asm - packing is 8
...
.pragma pack(push, 1) - packing is now 1
...
.pragma pack(pop) - packing is 8 again
...
```
#### See Also

[Pragma directive](dot-pragma.md)
