
; v2.22 -pe dllimport:<dll> external proto <no args> error
;
;  A2014: cannot define as public or external : <name>
;
;   call <name> - error -
;
;	invoke handle import prefix: __imp_<name>
;	invoke <name> - no error -
;

	option	dllimport:<kernel32>

	GetCurrentProcess proto
	ExitProcess	  proto :dword

	option	dllimport:NONE

	.code
start:
	; call GetCurrentProcess ; fail..
	;
	; Use invoke if extern import: __imp_<name>
	;
	GetCurrentProcess()
	dec	eax
	ExitProcess(eax)

	end	start
