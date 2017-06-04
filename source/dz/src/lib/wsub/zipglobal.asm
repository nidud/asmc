include zip.inc

	.data

zip_attrib	dd 0
zip_flength	dd 0
zip_local	S_LZIP <0>
zip_central	S_CZIP <0>
zip_endcent	S_ZEND <0,0,0,0,0,0,0,0>

	END
