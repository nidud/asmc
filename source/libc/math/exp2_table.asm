; EXP2_TABLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

public  exp2_table

        .data

exp2_table label double
        dq 0xbfe000000005f3f1, 0x3fe6a09e667c50df
        dq 0xbfdf800000504e67, 0x3fe6c01274f81141
        dq 0xbfdf000000413114, 0x3fe6dfb23c54f3bf
        dq 0xbfde800000026750, 0x3fe6ff7df950fb41
        dq 0xbfde00000001f188, 0x3fe71f75e8ebe2db
        dq 0xbfdd800000060771, 0x3fe73f9a48a3fcd4
        dq 0xbfdd000000027151, 0x3fe75feb5641c97b
        dq 0xbfdc800000133b3c, 0x3fe780694fd97820
        dq 0xbfdc000000006742, 0x3fe7a11473eae71a
        dq 0xbfdb8000000026c4, 0x3fe7c1ed0130b739
        dq 0xbfdb00000010b0f8, 0x3fe7e2f336cafcf6
        dq 0xbfda800000006fca, 0x3fe80427543dfcfe
        dq 0xbfda0000000a60b7, 0x3fe82589994a174b
        dq 0xbfd98000000f3180, 0x3fe8471a461fc8fa
        dq 0xbfd9000000065897, 0x3fe868d99b42e570
        dq 0xbfd8800000057289, 0x3fe88ac7d988f3ee
        dq 0xbfd800000005c28b, 0x3fe8ace5422916cb
        dq 0xbfd780000060838c, 0x3fe8cf32169b55bb
        dq 0xbfd7000000160f6a, 0x3fe8f1ae990f8189
        dq 0xbfd6800000015814, 0x3fe9145b0b91a250
        dq 0xbfd600000005b1dc, 0x3fe93737b0cc37c2
        dq 0xbfd58000000ced09, 0x3fe95a44cbc4c577
        dq 0xbfd500000004055e, 0x3fe97d829fdd3222
        dq 0xbfd4800000044514, 0x3fe9a0f170c8d852
        dq 0xbfd400000062eb27, 0x3fe9c49182885576
        dq 0xbfd380000025f5a3, 0x3fe9e86319d87c72
        dq 0xbfd300000026d9fb, 0x3fea0c667b52ef7a
        dq 0xbfd28000000ef1d6, 0x3fea309bec45f003
        dq 0xbfd200000028a35e, 0x3fea5503b2328e73
        dq 0xbfd18000003892f0, 0x3fea799e13207a90
        dq 0xbfd100000036ebd4, 0x3fea9e6b556a2865
        dq 0xbfd08000001df4d6, 0x3feac36bbfcb4499
        dq 0xbfd00000007109bc, 0x3feae89f9939e248
        dq 0xbfcf0000000d0ce0, 0x3feb0e07298bccef
        dq 0xbfce000000038571, 0x3feb33a2b84e9132
        dq 0xbfcd0000003291c8, 0x3feb59728ddddbeb
        dq 0xbfcc00000009a474, 0x3feb7f76f2f9eeb5
        dq 0xbfcb000000041435, 0x3feba5b030a069f4
        dq 0xbfca0000001c5bde, 0x3febcc1e90477d01
        dq 0xbfc90000000fd3f7, 0x3febf2c25bd4b8c9
        dq 0xbfc800000042ee2b, 0x3fec199bdd7b2358
        dq 0xbfc700000012ef60, 0x3fec40ab5ffceadc
        dq 0xbfc600000017f9f5, 0x3fec67f12e542120
        dq 0xbfc50000001c6b03, 0x3fec8f6d9402828e
        dq 0xbfc40000004dc028, 0x3fecb720dce37952
        dq 0xbfc300000002c957, 0x3fecdf0b555d5473
        dq 0xbfc20000000307a2, 0x3fed072d4a070f8f
        dq 0xbfc100000008225f, 0x3fed2f87080c40d5
        dq 0xbfc00000000d35cc, 0x3fed5818dcf98b25
        dq 0xbfbe00000000a23c, 0x3fed80e316c976a2
        dq 0xbfbc0000001a43df, 0x3feda9e603d9167a
        dq 0xbfba0000000a59b6, 0x3fedd321f300de67
        dq 0xbfb800000004084f, 0x3fedfc97337b478e
        dq 0xbfb60000000cc2e4, 0x3fee264614f49679
        dq 0xbfb40000002a7000, 0x3fee502ee787c449
        dq 0xbfb20000001b557e, 0x3fee7a51fbc50b11
        dq 0xbfb0000000067db9, 0x3feea4afa2a406fa
        dq 0xbfac0000004cac7c, 0x3feecf482d8b353b
        dq 0xbfa80000002255b2, 0x3feefa1bee5fe98b
        dq 0xbfa40000000fbb0b, 0x3fef252b376b10cb
        dq 0xbfa000000013426b, 0x3fef50765b6d743c
        dq 0xbf980000001b1b4b, 0x3fef7bfdad9c2a30
        dq 0xbf90000000108597, 0x3fefa7c1819e3637
        dq 0xbf800000001446bb, 0x3fefd3c22b8f3a07
        dq 0x0000000000000000, 0x3ff0000000000000
        dq 0x3f80000000046787, 0x3ff0163da9fb3959
        dq 0x3f90000000413bdf, 0x3ff02c9a3e783737
        dq 0x3f9800000009e3ad, 0x3ff04315e86e9b63
        dq 0x3fa00000000c4c0e, 0x3ff059b0d315cb23
        dq 0x3fa40000001dce0d, 0x3ff0706b29dea0ad
        dq 0x3fa80000002def51, 0x3ff087451876a2e9
        dq 0x3fac000000110f6a, 0x3ff09e3ecac755c5
        dq 0x3fb0000000042de0, 0x3ff0b5586cf9b976
        dq 0x3fb20000000af8a9, 0x3ff0cc922b72c7b8
        dq 0x3fb40000000120ca, 0x3ff0e3ec32d3ded7
        dq 0x3fb600000008f69e, 0x3ff0fb66afff3c9d
        dq 0x3fb8000000305124, 0x3ff11301d0149725
        dq 0x3fba0000000021c9, 0x3ff12abdc06c335e
        dq 0x3fbc0000000b765e, 0x3ff1429aaea9b702
        dq 0x3fbe0000000561d9, 0x3ff15a98c8a5cf0f
        dq 0x3fc00000000d9993, 0x3ff172b83c7e9a70
        dq 0x3fc10000001aa7db, 0x3ff18af9388f162b
        dq 0x3fc2000000023143, 0x3ff1a35beb700111
        dq 0x3fc300000035902b, 0x3ff1bbe0840981a5
        dq 0x3fc40000000c261e, 0x3ff1d4873169e5f6
        dq 0x3fc50000000f8bff, 0x3ff1ed5022fe5b7c
        dq 0x3fc600000019e18b, 0x3ff2063b88651387
        dq 0x3fc700000010f9d2, 0x3ff21f49917f8711
        dq 0x3fc800000021f3d9, 0x3ff2387a6e78bbd5
        dq 0x3fc900000007aca6, 0x3ff251ce4fb36926
        dq 0x3fca0000000834d3, 0x3ff26b4565e34e68
        dq 0x3fcb0000000f383c, 0x3ff284dfe1f6ea3c
        dq 0x3fcc000000295470, 0x3ff29e9df52409b2
        dq 0x3fcd000000aa2014, 0x3ff2b87fd0ec18b9
        dq 0x3fce00000089ee06, 0x3ff2d285a6f21217
        dq 0x3fcf00000011e56f, 0x3ff2ecafa94004d8
        dq 0x3fd00000002450b9, 0x3ff306fe0a3932e5
        dq 0x3fd0800000018109, 0x3ff32170fc4d27f8
        dq 0x3fd10000000f3232, 0x3ff33c08b2674165
        dq 0x3fd18000000237f0, 0x3ff356c55f9316e5
        dq 0x3fd20000000199c8, 0x3ff371a7373b0016
        dq 0x3fd28000000b48f9, 0x3ff38cae6d083c14
        dq 0x3fd30000004c6957, 0x3ff3a7db34f5e42c
        dq 0x3fd38000004e208e, 0x3ff3c32dc32461b8
        dq 0x3fd4000000013df2, 0x3ff3dea64c12788e
        dq 0x3fd480000015af05, 0x3ff3fa4504b13129
        dq 0x3fd500000009a838, 0x3ff4160a21f947f9
        dq 0x3fd5800000234f8c, 0x3ff431f5d95861bd
        dq 0x3fd600000003a7aa, 0x3ff44e08606256f0
        dq 0x3fd68000000e661d, 0x3ff46a41ed202f5b
        dq 0x3fd700000047e5a0, 0x3ff486a2b5d13877
        dq 0x3fd780000013fc02, 0x3ff4a32af0dc4b5b
        dq 0x3fd800000018514b, 0x3ff4bfdad53ba122
        dq 0x3fd88000004b65dc, 0x3ff4dcb29a0ee638
        dq 0x3fd90000002a7909, 0x3ff4f9b276a6d2b4
        dq 0x3fd98000000e9ddf, 0x3ff516daa2d2bcec
        dq 0x3fda0000001165b7, 0x3ff5342b56a14e49
        dq 0x3fda800000347522, 0x3ff551a4ca69aec0
        dq 0x3fdb000000163445, 0x3ff56f4736ba4f70
        dq 0x3fdb800000173fe4, 0x3ff58d12d49d3534
        dq 0x3fdc0000000bbaca, 0x3ff5ab07dd4b14d7
        dq 0x3fdc80000016a2c1, 0x3ff5c9268a5e9dfb
        dq 0x3fdd0000004564c2, 0x3ff5e76f15bd979e
        dq 0x3fdd8000001d2bb6, 0x3ff605e1b97dd138
        dq 0x3fde000000122703, 0x3ff6247eb03eafef
        dq 0x3fde8000001fd876, 0x3ff6434634d470cf
        dq 0x3fdf0000004a6dab, 0x3ff6623882672d39
        dq 0x3fdf80000033c91f, 0x3ff68155d45948c1
        dq 0x3fe000000006d6f2, 0x3ff6a09e668295fd

        end
