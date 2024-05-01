Asmc Macro Assembler Reference

## ASSUME

**ASSUME** segregister:name [[, segregister:name]]...

**ASSUME** dataregister:type [[, dataregister:type]]...

**ASSUME** register:ERROR [[, register:ERROR]]...

**ASSUME** [[register:]] NOTHING [[, register:NOTHING]]...


Enables error checking for register values. After an ASSUME is put into effect, the assembler watches for changes to the values of the given registers. ERROR generates an error if the register is used. NOTHING removes register error checking. You can combine different kinds of assumptions in one statement.

#### See Also

[Directives Reference](readme.md)