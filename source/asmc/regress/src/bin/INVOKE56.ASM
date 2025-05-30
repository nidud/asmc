
;--- 2.18: wrong value pushed for the first argument (0) 

	.model small, stdcall

PlotLine proto :word, :word, :word, :word

	.code

main proc

	invoke PlotLine, 0, 0, 0, 0		;ok
	invoke PlotLine, 0, 199, 319, 0	;bad
	ret
main endp

PlotLine Proc x1:word, y1:word, x2:word, y2:word
	ret
PlotLine endp

	end main
