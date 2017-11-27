include consx.inc

    .code

CFError proc section, entry

    ermsg("Bad or missing Entry in .INI file",
	  "Section: [%s]\nEntry: [%s]", section, entry)
    ret

CFError endp

    END
