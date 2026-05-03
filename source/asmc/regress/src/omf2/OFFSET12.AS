
;--- test for correct fixup creation
;--- for direct addressing without symbol
;--- works since v2.14
;--- v2.15: a change in omffixup.c makes jwasm create
;---        differing fixups. So this test's expected result
;---        has been adjusted.

	.386

_DATA segment dword use32 public 'DATA'
var	dd 12345678h
_DATA ends

DGROUP group _TEXT,_DATA	;_DATA is first segment in group!

_TEXT segment dword use32 public 'CODE'

	mov eax,offset DGROUP:[12h]	; -> 12h, ok
	mov eax,offset  _TEXT:[12h]	; -> 16h, ok
	mov eax,offset  _DATA:[12h]	; -> 12h, ok

;--- register overrides are NOT supposed to create fixups;
;--- at least Masm doesn't.
	assume ds:DGROUP
	mov eax,offset ds:[12h]
	assume ds:_TEXT
	mov eax,offset ds:[12h]	;but: shouldn't this be 16h?
	assume ds:_DATA
	mov eax,offset ds:[12h]

_TEXT ends

	END
