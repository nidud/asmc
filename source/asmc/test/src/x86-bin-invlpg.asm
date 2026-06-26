
;--- this works (again) in v2.14
;--- didn't work in v1.96-v2.13

	.286
	.model small

	.code

	.486
	assume ds:FLAT
	invlpg ds:[400000h]

	end
