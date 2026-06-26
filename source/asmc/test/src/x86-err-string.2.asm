
	.286
	.model small
	.stack 1024

	.code

;--- second operand must be ES
	cmps byte ptr [di],cs:[si]
	cmps byte ptr [di],ds:[si]
	cmps byte ptr [di],ss:[si]
	cmps byte ptr ds:[di],cs:[si]
	cmps byte ptr ds:[di],ds:[si]
	cmps byte ptr ds:[di],ss:[si]
	cmps byte ptr es:[di],cs:[si]
	cmps byte ptr es:[di],ds:[si]
	cmps byte ptr es:[di],ss:[si]

;--- these are ok
	cmps byte ptr [di],es:[si]
	cmps byte ptr ds:[di],es:[si]
	cmps byte ptr es:[di],es:[si]

	end
