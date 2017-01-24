include ini.inc

	.code

main	proc c

	.assert iniopen("src/crlf.ini")
	.assert !inientry("1","00")
	.assert !inientry("1","11")
	.assert inientry("1","0")
	.assert inientry("1","1")
	.assert !inientry("1","xx")
	.assert inientry("1","x")
	.assert !inientry("1","2")
	.assert inientryid("1",0)
	.assert inientryid("1",1)
	.assert !inientryid("1",2)
	.assert !inientry("Section","entry")
	.assert inientry("Section","1")
	.assert inientry("Section","0")
	.assert !inientry("Section","Null")
	.assert !iniclose()

	.assert iniopen("src/lf.ini")
	.assert !inientry("1","00")
	.assert !inientry("1","11")
	.assert inientry("1","0")
	.assert inientry("1","1")
	.assert !inientry("1","xx")
	.assert inientry("1","x")
	.assert !inientry("1","2")
	.assert inientryid("1",0)
	.assert inientryid("1",1)
	.assert !inientryid("1",2)
	.assert !inientry("Section","entry")
	.assert inientry("Section","1")
	.assert inientry("Section","0")
	.assert !inientry("Section","Null")
	.assert !iniclose()

	ret
main	endp

	end
