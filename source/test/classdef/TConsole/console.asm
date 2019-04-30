include tdialog.inc

    .data
    console LPTCONSOLE 0

    .code

Install proc private

    tconsole::tconsole( &console )
    ret

Install endp

.pragma(init(Install, 50))

    end
