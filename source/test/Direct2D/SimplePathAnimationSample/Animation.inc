
include math.inc

;/******************************************************************
;*                                                                 *
;* Base Animation Class                                            *
;*                                                                 *
;******************************************************************/

.template Animation

    m_Duration  float ?
    m_Start     float ?
    m_End       float ?

    .operator Animation :float, :float, :float {
        movss [rcx].Animation.m_Start,xmm1
        movss [rcx].Animation.m_End,xmm2
        movss [rcx].Animation.m_Duration,xmm3
        mov rax,rcx
        }

    .operator SetStart :float {
        movss [rcx].Animation.m_Start,xmm1
        }

    .operator GetStart {
        movss xmm0,[rcx].Animation.m_Start
        }

    .operator SetEnd :float {
        movss [rcx].Animation.m_End,xmm1
        }

    .operator GetEnd {
        movss xmm0,[rcx].Animation.m_End
        }

    .operator SetDuration :float {
        xorps xmm0,xmm0
        maxss xmm0,xmm1
        movss [rcx].Animation.m_Duration,xmm0
        }

    .operator GetDuration {
        movss xmm0,[rcx].Animation.m_Duration
        }

    .operator GetValue :float, :abs=<LinearAnimation> {
        xorps xmm0,xmm0
        maxss xmm1,xmm0
        minss xmm1,[rcx].Animation.m_Duration
        [rcx]._2.ComputeValue(xmm1)
        }
    .ends

;/******************************************************************
;*                                                                 *
;* Linearly Interpolate Between Start and End                      *
;*                                                                 *
;******************************************************************/

.template LinearAnimation : public Animation

    .operator LinearAnimation :abs=<0.0>, :abs=<0.0>, :abs=<0.0> {
        [rcx].Animation.Animation(_1, _2, _3)
        }

    .operator ComputeValue :float {
        divss xmm1,[rcx].LinearAnimation.m_Duration
        movss xmm0,[rcx].LinearAnimation.m_End
        subss xmm0,[rcx].LinearAnimation.m_Start
        mulss xmm0,xmm1
        addss xmm0,[rcx].LinearAnimation.m_Start
        }
    .ends

;/******************************************************************
;*                                                                 *
;*                                                                 *
;*                                                                 *
;******************************************************************/

.template EaseInExponentialAnimation : public Animation

    .operator EaseInExponentialAnimation :abs=<0.0>, :abs=<0.0>, :abs=<0.0> {
        [rcx].Animation.Animation(_1, _2, _3)
        }

    .operator ComputeValue :float {
      local T
       .new T:ptr
        mov      T,rcx
        divss    xmm1,[rcx].LinearAnimation.m_Duration
        subss    xmm1,1.0
        mulss    xmm1,10.0
        cvtss2sd xmm1,xmm1
        pow(2.0, xmm1)
        cvtsd2si xmm0,xmm0
        mov      rcx,T
        movss    xmm1,[rcx].LinearAnimation.m_End
        subss    xmm1,[rcx].LinearAnimation.m_Start
        mulss    xmm0,xmm1
        addss    xmm0,[rcx].LinearAnimation.m_Start
        }
    .ends

;/******************************************************************
;*                                                                 *
;*                                                                 *
;*                                                                 *
;******************************************************************/

.template EaseOutExponentialAnimation : public Animation

    .operator EaseOutExponentialAnimation :abs=<0.0>, :abs=<0.0>, :abs=<0.0> {
        [rcx].Animation.Animation(_1, _2, _3)
        }

    .operator ComputeValue :float {
      local T
       .new T:ptr
        mov      T,rcx
        mulss    xmm1,-10.0
        divss    xmm1,[rcx].LinearAnimation.m_Duration
        addss    xmm1,1.0
        cvtss2sd xmm1,xmm1
        pow(2.0, xmm1)
        movsd    xmm1,-0.0
        xorpd    xmm0,xmm1
        cvtsd2si xmm0,xmm0
        mov      rcx,T
        movss    xmm1,[rcx].LinearAnimation.m_End
        subss    xmm1,[rcx].LinearAnimation.m_Start
        mulss    xmm0,xmm1
        addss    xmm0,[rcx].LinearAnimation.m_Start
        }
    .ends

;/******************************************************************
;*                                                                 *
;*                                                                 *
;*                                                                 *
;******************************************************************/

.template EaseInOutExponentialAnimation : public Animation

    .operator EaseInOutExponentialAnimation :abs=<0.0>, :abs=<0.0>, :abs=<0.0> {
        [rcx].Animation.Animation(_1, _2, _3)
        }

    .operator ComputeValue :float {

      local T
       .new T:ptr
        mov T,rcx

        ;; compute the current time relative to the midpoint

        movss  xmm0,[rcx].LinearAnimation.m_Duration
        divss  xmm0,2.0
        divss  xmm1,xmm0
        comiss xmm1,1.0
        subss  xmm1,1.0

        ;; if we haven't reached the midpoint, we want to do the ease-in portion

        .ifna

            mulss    xmm1,10.0
            cvtss2sd xmm1,xmm1
            pow(2.0, xmm1)
            cvtsd2ss xmm0,xmm0

        .else

            ;; otherwise, do the ease-out portion

            mulss    xmm1,-10.0
            cvtss2sd xmm1,xmm1
            pow(2.0, xmm1)
            cvtsd2ss xmm0,xmm0
            movss    xmm1,-0.0
            xorps    xmm0,xmm1
            addss    xmm0,2.0
        .endif

        mov      rcx,T
        movss    xmm1,[rcx].LinearAnimation.m_End
        subss    xmm1,[rcx].LinearAnimation.m_Start
        divss    xmm1,2.0
        mulss    xmm0,xmm1
        addss    xmm0,[rcx].LinearAnimation.m_Start
        }
    .ends

