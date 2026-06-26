
;--- v2.16: changed error msg ( "symbol redefinition" to "cannot define as public or external" )

	.386
	.MODEL FLAT

XX struct
x db ?
XX ends

extern XX:word

	END

