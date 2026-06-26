;
; v2.39: .case ( level )
;
    .486
    .model flat
    .code

    .switch pascal eax
    .case 'A'
        .endc( 0 )
    .case 'B'
        .switch eax
        .case 'A'
            .switch eax
            .case 'A'
                .endc( 0 )
            .case 'B'
                .endc( 1 )
            .case 'C'
                .endc( 2 )
            .endsw
            .endc( 0 )
        .case 'B'
            .endc( 1 )
        .endsw
    .endsw

    end

