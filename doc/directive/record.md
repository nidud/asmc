Asmc Macro Assembler Reference

## RECORD

recordname **RECORD** fieldname:width [[= expression]] [[, fieldname:width [[= expression]]]]...

Declares a record type consisting of the specified fields. fieldname names the field, width specifies the number of bits, and expression gives its initial value.

The first field in the declaration always goes into the most significant bits of the record. Subsequent fields are placed to the right in the succeeding bits. If the fields do not total exactly 8, 16, or 32 bits as appropriate, the entire record is shifted right, so the last bit of the last field is the lowest bit of the record. Unused bits in the high end of the record are initialized to 0.

### Embedded records

Asmc also allows embedded C-style records in structures in the same way as STRUC and UNION.

```
name STRUC
RECORD [[ name ]]
 fieldname type:width ?
 ...
ENDS
name ENDS
```
Note that the record field names here are not global (Masm design flaw) and there are no packing as the size is predefined similar to C bit-fields, and the first field in the declaration always goes into the least significant bits of the record.

#### See Also

[Directives Reference](readme.md)
