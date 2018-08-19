;
; v2.27.38: .switch [c|pascal] [<args>]
;
    .486
    .model flat
    .code

    option switch: pascal
    .switch c eax
      .case 'A'
      .case 'C'
      .case 'D'
      .case 'E'
      .case 'F'
      .default
    .endsw

    option switch: c
    .switch pascal eax
      .case 'A'
      .case 'C'
      .case 'D'
      .case 'E'
      .case 'F'
      .default
    .endsw

    end

