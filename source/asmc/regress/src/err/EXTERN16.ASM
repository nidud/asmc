
;--- v2.16: externdef symbol must be either undefined, internal or external.
;--- problem here is that "option casemap:none is missing.

	.386
	.model flat

HINSTANCE typedef ptr

externdef hInstance:HINSTANCE

    end
