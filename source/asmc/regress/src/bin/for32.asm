; v2.22 - .FOR[S] [<initialization>] : [<condition>] : [<increment/decrement>]

	.386
	.model	flat, c
	.code

	.FOR::
	.ENDF
	.FOR(::)
	.ENDF
	.FOR(cl=2::)
	.ENDF
	.FOR(:cl:)
	.ENDF
	.FOR(::cl--)
	.ENDF
	.FOR(cl=2:cl:)
	.ENDF
	.FOR(cl=2::cl--)
	.ENDF
	.FOR(cl=2:cl:cl--)
	.ENDF
	.FOR(cl=2,bl=al:cl<0:--cl,bl+=4)
	.ENDF
	.FOR::
	 .FOR::
	  .FOR::
	   .FOR::
		.CONTINUE(3)
		.CONTINUE(03)
		.BREAK(3)
	   .ENDF
	  .ENDF
	 .ENDF
	.ENDF

proto_t typedef proto :ptr, :ptr
proto_p typedef ptr proto_t

	foo	proto_p 0
		;
		; <initialization>
		;
	.FOR	edx = foo(1,2),
		ecx = foo(1,3),
		ebx = foo(1,4) ::
	.ENDF
		;
		; <condition>
		;
	.FOR	: edx > foo(1,2),
		  ecx > foo(1,3),
		  ebx > foo(1,4) :
	.ENDF

	END
