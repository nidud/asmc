
;--- extracted from pe2.asm (the warning that's generated is new in v2.15)
;--- -pe format test
;--- linker info section .drectve should create a warning for option -pe
;--- v2.19: option -pe now scans .drectve; if the linker cmd is known,
;---        no warning is emitted.

	.386
	.model flat, stdcall	;-pe requires a .model flat directive

;--- linker info - expected to generate a warning if jwasm version is < 2.19.
	option dotname
.drectve segment info
;	db "-subsystem:console "   ; this is now a known linker directive for -pe
	db "-unknown_linker_cmd"   ; this is supposed to create a warning for versions >= 2.19
.drectve ends

	.code
start:
	ret
end start
