Asmc Macro Assembler Reference

### .ENUM

**.ENUM** [[ _name_ ]] [[ : _type_ ]] [[ { ]]

The enum keyword is used to declare an enumeration, a distinct type that consists of a set of named constants called the enumerator list.

By default, the first enumerator has the value 0, and the value of each successive enumerator is increased by 1. For example, in the following enumeration, Sat is 0, Sun is 1, Mon is 2, and so forth.

    .enum Day {Sat, Sun, Mon, Tue, Wed, Thu, Fri}

Enumerators can use initializers to override the default values, as shown in the following example.

    .enum Day {
         Sat=1, Sun, Mon, Tue, Wed, Thu, Fri }

The default underlying type of enumeration elements is int. To declare an enum of another integral type, such as byte, use a colon after the identifier followed by the type, as shown in the following example.

    .enum name : byte {
        ok = 200,
        to_big = 300 ; error A2071: initializer too large for specified size
    }

#### See Also

[Directives Reference](readme.md) | [.ENUMT](dot_enumt.md)
