Asmc Macro Assembler Reference

## OPTION OFFSET

**OPTION OFFSET**:[GROUP|FLAT|SEGMENT]

Determines the result of OFFSET operator fixups.

SEGMENT sets the defaults for fixups to be segment-relative (compatible with MASM 5.1). GROUP, the default, generates fixups relative to the group (if the label is in a group). FLAT causes fixups to be relative to a flat frame. (The .386 mode must be enabled to use FLAT.)

#### See Also

[Directives Reference](readme.md)