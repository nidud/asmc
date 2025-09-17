Asmc Macro Assembler Reference

## ASSUME

- **ASSUME** segregister:name [[, segregister:name]]...
- **ASSUME** dataregister:type [[, dataregister:type]]...
- **ASSUME** register:ERROR [[, register:ERROR]]...
- **ASSUME** [[register:]] NOTHING [[, register:NOTHING]]...

Enables error checking for register values. After an ASSUME is put into effect, the assembler watches for changes to the values of the given registers. ERROR generates an error if the register is used. NOTHING removes register error checking. You can combine different kinds of assumptions in one statement.

### Asmc Extensions

- **ASSUME** CLASS:[[register]] NOTHING

Enables local access to Class members and methods.

- **ASSUME** USES [[:]] [[register]] NOTHING [[register]]...

Adds USES registers to procedures.

- **ASSUME PROC**:_visibility_

Lets you explicitly set the default visibility as PUBLIC or PRIVATE.

#### See Also

[Segment](segments.md) | [Miscellaneous](miscellaneous.md) | [Directives Reference](readme.md)
