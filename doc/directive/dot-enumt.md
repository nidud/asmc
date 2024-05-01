Asmc Macro Assembler Reference

## .ENUMT

**.ENUMT** [[ _name_ ]] [[ : _type_ ]] [[ { ]]

The enumt keyword is similar to [.ENUM](dot_enum.md) but uses _type_ as _size_ multiplier.

For example, in the following enumeration, Sat is 0, Sun is 2, Mon is 4, and so forth.
```
    .enum Day : WORD {Sat, Sun, Mon, Tue, Wed, Thu, Fri}
```

#### See Also

[Directives Reference](readme.md) | [.ENUM](dot_enum.md)
