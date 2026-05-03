ifndef _ADODEF_H_
define _ADODEF_H_
.pragma list(push, 0)

ADO_MAJOR		equ 6
ADOR_MAJOR		equ 2
ADOX_MAJOR		equ 6
ADOMD_MAJOR		equ 6
JRO_MAJOR		equ 2

ADO_MINOR		equ 0
ADOR_MINOR		equ 8
ADOX_MINOR		equ 0
ADOMD_MINOR		equ 0
JRO_MINOR		equ 6

;ADO_VERSION		 equ ADO_MAJOR##.##ADO_MINOR
;ADOR_VERSION		 equ ADOR_MAJOR##.##ADOR_MINOR
;ADOX_VERSION		 equ ADOX_MAJOR##.##ADOX_MINOR
;ADOMD_VERSION		 equ ADOMD_MAJOR##.##ADOMD_MINOR
;JRO_VERSION		 equ JRO_MAJOR##.##JRO_MINOR

ADO_HELPFILE		equ <"ado270.chm">
ADOX_HELPFILE		equ <"ado270.chm">
ADOMD_HELPFILE		equ <"ado270.chm">
JRO_HELPFILE		equ <"msjro.chm">

ADO_LIBRARYNAME		equ <"Microsoft ActiveX Data Objects 6.0 Library">
ADOR_LIBRARYNAME	equ <"Microsoft ActiveX Data Objects Recordset 2.8 Library">
ADOX_LIBRARYNAME	equ <"Microsoft ADO Ext. 6.0 for DDL and Security">
ADOMD_LIBRARYNAME	equ <"Microsoft ActiveX Data Objects (Multi-dimensional) 6.0 Library">
JRO_LIBRARYNAME		equ <"Microsoft Jet and Replication Objects 2.6 Library">

;ADOMD_TYPELIB_UUID	 equ uuid(22813728-8BD3-11D0-B4EF-00A0C9138CA4)
;JRO_TYPELIB_UUID	 equ uuid(AC3B8B4C-B6CA-11d1-9F31-00C04FC29D52)

.pragma list(pop)
endif

