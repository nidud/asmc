
	.386
	.model flat

EMM59 struct
e59_pgsize  dw ?    ;raw page size in paragraphs
e59_altsets dw ?    ;number of alternate register sets
e59_sizcont dw ?    ;size of mapping context save area in bytes
e59_dmasets dw ?    ;dma register sets
e59_dmaflgs dw ?    ;dma flags
EMM59 ends

	.data

x1   EMM59 <1,2,3,4,5>
x2   EMM59 2 dup (<1,2,3,4,5>)

	.code

    mov ecx, SIZE x1
    mov ecx, LENGTH x1
    mov ecx, SIZE x2
    mov ecx, LENGTH x2

	END
