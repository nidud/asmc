foostr TEXTEQU <xyz>
foo SIZESTR foostr
foo = foo - 100		; <--- does set asym.value3264 to -1
foo SIZESTR foostr	; <-- CreateVariable() does not zero asym.value3264, if equate already exist.
_TEXT segment
	dq foo
_TEXT ends
    END

