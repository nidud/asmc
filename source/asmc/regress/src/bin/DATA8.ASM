ifdef __ASMC__
option masm:on
endif

;--- Masm v8-v10 create invalid code with -omf
;--- case v4 works since jwasm v2.09.

_DATA segment

v1	db "abc","x"
	dw SIZE v1, LENGTH v1, sizeof v1, lengthof v1 ;expected: 1,1,4,4

v2	db 3 dup ('a'),"x"
	dw SIZE v2, LENGTH v2, sizeof v2, lengthof v2 ;expected: 3,3,4,4

v3	db 3 dup ('ab'),"x"
	dw SIZE v3, LENGTH v3, sizeof v3, lengthof v3 ;expected: 3,3,7,7

v4	db 3 dup (3 dup ('a')),"x"
	dw SIZE v4, LENGTH v4, sizeof v4, lengthof v4 ;expected: 3,3,10,10

_DATA ends

	end
