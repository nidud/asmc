Asmc Macro Assembler Reference

### OPTION [NO]READONLY

**OPTION [NO]READONLY**

Default settings: option has no effect.

Enables checking for instructions that modify code segments, thereby guaranteeing that read-only code segments are not modified. Same as the /p command-line option of MASM 5.1, except that it affects only segments with at least one assembly instruction, not all segments. The argument is useful for protected mode programs, where code segments must remain read-only.

#### See Also

[Directives Reference](readme.md)