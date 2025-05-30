
;--- regression in v2.13
;--- an error may have been emitted if a segment was first added
;--- to a group and then defined.
;--- the reason was that when the segment was added to the group,
;--- it got the default offset size, which may not have been the
;--- intended size.

    .386

GROUP16 group _TEXT16

_TEXT16 segment use16 para public 'CODE'
	db -1
_TEXT16 ends

    end
