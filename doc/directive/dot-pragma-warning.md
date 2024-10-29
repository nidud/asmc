Asmc Macro Assembler Reference

## warning pragma

Enables selective modification of the behavior of compiler warning messages.

- .**pragma** warning(disable: _num_)
- .**pragma** warning(push)
- .**pragma** warning(pop)

_disable_

Don't issue the specified warning messages.

_push and pop_

The pragma warning( push ) stores the current warning state for every warning. The pragma warning( pop ) pops the last warning state pushed onto the stack.

```
.pragma warning( push )
.pragma warning( disable : 4005 )
.pragma warning( disable : 4006 )
.pragma warning( disable : 4007 )
...
.pragma warning( pop )
```

#### See Also

[Pragma directive](dot-pragma.md) | [Asmc Warning Messages](../error/warnings.md)
