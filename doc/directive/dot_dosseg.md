Asmc Macro Assembler Reference

### .DOSSEG

**.DOSSEG**

Orders the segments according to the MS-DOS segment convention: CODE first, then segments not in DGROUP, and then segments in DGROUP. The segments in DGROUP follow this order: segments not in BSS or STACK, then BSS segments, and finally STACK segments. Primarily used for ensuring CodeView support in MASM stand-alone programs. Same as DOSSEG.

#### See Also

[Directives Reference](readme.md)