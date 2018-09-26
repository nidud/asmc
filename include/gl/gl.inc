ifndef __gl_h_
ifndef __GL_H__
__gl_h_ equ 1
__GL_H__ equ 1
ifndef _WINDEF_
 include windef.inc
endif
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

GLenum                  typedef dword
GLboolean               typedef byte
GLbitfield              typedef dword
GLbyte                  typedef sbyte
GLshort                 typedef sword
GLint                   typedef sdword
GLsizei                 typedef sdword
GLubyte                 typedef byte
GLushort                typedef word
GLuint                  typedef dword
GLfloat                 typedef real4
GLclampf                typedef real4
GLdouble                typedef real8
GLclampd                typedef real8
GLvoid                  equ <>

GL_VERSION_1_1          equ 1

GL_ACCUM                equ 0x0100
GL_LOAD                 equ 0x0101
GL_RETURN               equ 0x0102
GL_MULT                 equ 0x0103
GL_ADD                  equ 0x0104

GL_NEVER                equ 0x0200
GL_LESS                 equ 0x0201
GL_EQUAL                equ 0x0202
GL_LEQUAL               equ 0x0203
GL_GREATER              equ 0x0204
GL_NOTEQUAL             equ 0x0205
GL_GEQUAL               equ 0x0206
GL_ALWAYS               equ 0x0207

GL_CURRENT_BIT          equ 0x00000001
GL_POINT_BIT            equ 0x00000002
GL_LINE_BIT             equ 0x00000004
GL_POLYGON_BIT          equ 0x00000008
GL_POLYGON_STIPPLE_BIT  equ 0x00000010
GL_PIXEL_MODE_BIT       equ 0x00000020
GL_LIGHTING_BIT         equ 0x00000040
GL_FOG_BIT              equ 0x00000080
GL_DEPTH_BUFFER_BIT     equ 0x00000100
GL_ACCUM_BUFFER_BIT     equ 0x00000200
GL_STENCIL_BUFFER_BIT   equ 0x00000400
GL_VIEWPORT_BIT         equ 0x00000800
GL_TRANSFORM_BIT        equ 0x00001000
GL_ENABLE_BIT           equ 0x00002000
GL_COLOR_BUFFER_BIT     equ 0x00004000
GL_HINT_BIT             equ 0x00008000
GL_EVAL_BIT             equ 0x00010000
GL_LIST_BIT             equ 0x00020000
GL_TEXTURE_BIT          equ 0x00040000
GL_SCISSOR_BIT          equ 0x00080000
GL_ALL_ATTRIB_BITS      equ 0x000fffff

GL_POINTS               equ 0x0000
GL_LINES                equ 0x0001
GL_LINE_LOOP            equ 0x0002
GL_LINE_STRIP           equ 0x0003
GL_TRIANGLES            equ 0x0004
GL_TRIANGLE_STRIP       equ 0x0005
GL_TRIANGLE_FAN         equ 0x0006
GL_QUADS                equ 0x0007
GL_QUAD_STRIP           equ 0x0008
GL_POLYGON              equ 0x0009

GL_ZERO                 equ 0
GL_ONE                  equ 1
GL_SRC_COLOR            equ 0x0300
GL_ONE_MINUS_SRC_COLOR  equ 0x0301
GL_SRC_ALPHA            equ 0x0302
GL_ONE_MINUS_SRC_ALPHA  equ 0x0303
GL_DST_ALPHA            equ 0x0304
GL_ONE_MINUS_DST_ALPHA  equ 0x0305

GL_DST_COLOR            equ 0x0306
GL_ONE_MINUS_DST_COLOR  equ 0x0307
GL_SRC_ALPHA_SATURATE   equ 0x0308

GL_TRUE                 equ 1
GL_FALSE                equ 0

GL_CLIP_PLANE0          equ 0x3000
GL_CLIP_PLANE1          equ 0x3001
GL_CLIP_PLANE2          equ 0x3002
GL_CLIP_PLANE3          equ 0x3003
GL_CLIP_PLANE4          equ 0x3004
GL_CLIP_PLANE5          equ 0x3005

GL_BYTE                 equ 0x1400
GL_UNSIGNED_BYTE        equ 0x1401
GL_SHORT                equ 0x1402
GL_UNSIGNED_SHORT       equ 0x1403
GL_INT                  equ 0x1404
GL_UNSIGNED_INT         equ 0x1405
GL_FLOAT                equ 0x1406
GL_2_BYTES              equ 0x1407
GL_3_BYTES              equ 0x1408
GL_4_BYTES              equ 0x1409
GL_DOUBLE               equ 0x140A

GL_NONE                 equ 0
GL_FRONT_LEFT           equ 0x0400
GL_FRONT_RIGHT          equ 0x0401
GL_BACK_LEFT            equ 0x0402
GL_BACK_RIGHT           equ 0x0403
GL_FRONT                equ 0x0404
GL_BACK                 equ 0x0405
GL_LEFT                 equ 0x0406
GL_RIGHT                equ 0x0407
GL_FRONT_AND_BACK       equ 0x0408
GL_AUX0                 equ 0x0409
GL_AUX1                 equ 0x040A
GL_AUX2                 equ 0x040B
GL_AUX3                 equ 0x040C

GL_NO_ERROR             equ 0
GL_INVALID_ENUM         equ 0x0500
GL_INVALID_VALUE        equ 0x0501
GL_INVALID_OPERATION    equ 0x0502
GL_STACK_OVERFLOW       equ 0x0503
GL_STACK_UNDERFLOW      equ 0x0504
GL_OUT_OF_MEMORY        equ 0x0505

GL_2D                   equ 0x0600
GL_3D                   equ 0x0601
GL_3D_COLOR             equ 0x0602
GL_3D_COLOR_TEXTURE     equ 0x0603
GL_4D_COLOR_TEXTURE     equ 0x0604

GL_PASS_THROUGH_TOKEN   equ 0x0700
GL_POINT_TOKEN          equ 0x0701
GL_LINE_TOKEN           equ 0x0702
GL_POLYGON_TOKEN        equ 0x0703
GL_BITMAP_TOKEN         equ 0x0704
GL_DRAW_PIXEL_TOKEN     equ 0x0705
GL_COPY_PIXEL_TOKEN     equ 0x0706
GL_LINE_RESET_TOKEN     equ 0x0707

GL_EXP                  equ 0x0800
GL_EXP2                 equ 0x0801

GL_CW                   equ 0x0900
GL_CCW                  equ 0x0901

GL_COEFF                equ 0x0A00
GL_ORDER                equ 0x0A01
GL_DOMAIN               equ 0x0A02

GL_CURRENT_COLOR        equ 0x0B00
GL_CURRENT_INDEX        equ 0x0B01
GL_CURRENT_NORMAL       equ 0x0B02
GL_CURRENT_TEXTURE_COORDS equ 0x0B03
GL_CURRENT_RASTER_COLOR equ 0x0B04
GL_CURRENT_RASTER_INDEX equ 0x0B05
GL_CURRENT_RASTER_TEXTURE_COORDS equ 0x0B06
GL_CURRENT_RASTER_POSITION equ 0x0B07
GL_CURRENT_RASTER_POSITION_VALID equ 0x0B08
GL_CURRENT_RASTER_DISTANCE equ 0x0B09
GL_POINT_SMOOTH         equ 0x0B10
GL_POINT_SIZE           equ 0x0B11
GL_POINT_SIZE_RANGE     equ 0x0B12
GL_POINT_SIZE_GRANULARITY equ 0x0B13
GL_LINE_SMOOTH          equ 0x0B20
GL_LINE_WIDTH           equ 0x0B21
GL_LINE_WIDTH_RANGE     equ 0x0B22
GL_LINE_WIDTH_GRANULARITY equ 0x0B23
GL_LINE_STIPPLE         equ 0x0B24
GL_LINE_STIPPLE_PATTERN equ 0x0B25
GL_LINE_STIPPLE_REPEAT  equ 0x0B26
GL_LIST_MODE            equ 0x0B30
GL_MAX_LIST_NESTING     equ 0x0B31
GL_LIST_BASE            equ 0x0B32
GL_LIST_INDEX           equ 0x0B33
GL_POLYGON_MODE         equ 0x0B40
GL_POLYGON_SMOOTH       equ 0x0B41
GL_POLYGON_STIPPLE      equ 0x0B42
GL_EDGE_FLAG            equ 0x0B43
GL_CULL_FACE            equ 0x0B44
GL_CULL_FACE_MODE       equ 0x0B45
GL_FRONT_FACE           equ 0x0B46
GL_LIGHTING             equ 0x0B50
GL_LIGHT_MODEL_LOCAL_VIEWER equ 0x0B51
GL_LIGHT_MODEL_TWO_SIDE equ 0x0B52
GL_LIGHT_MODEL_AMBIENT  equ 0x0B53
GL_SHADE_MODEL          equ 0x0B54
GL_COLOR_MATERIAL_FACE  equ 0x0B55
GL_COLOR_MATERIAL_PARAMETER equ 0x0B56
GL_COLOR_MATERIAL       equ 0x0B57
GL_FOG                  equ 0x0B60
GL_FOG_INDEX            equ 0x0B61
GL_FOG_DENSITY          equ 0x0B62
GL_FOG_START            equ 0x0B63
GL_FOG_END              equ 0x0B64
GL_FOG_MODE             equ 0x0B65
GL_FOG_COLOR            equ 0x0B66
GL_DEPTH_RANGE          equ 0x0B70
GL_DEPTH_TEST           equ 0x0B71
GL_DEPTH_WRITEMASK      equ 0x0B72
GL_DEPTH_CLEAR_VALUE    equ 0x0B73
GL_DEPTH_FUNC           equ 0x0B74
GL_ACCUM_CLEAR_VALUE    equ 0x0B80
GL_STENCIL_TEST         equ 0x0B90
GL_STENCIL_CLEAR_VALUE  equ 0x0B91
GL_STENCIL_FUNC         equ 0x0B92
GL_STENCIL_VALUE_MASK   equ 0x0B93
GL_STENCIL_FAIL         equ 0x0B94
GL_STENCIL_PASS_DEPTH_FAIL equ 0x0B95
GL_STENCIL_PASS_DEPTH_PASS equ 0x0B96
GL_STENCIL_REF          equ 0x0B97
GL_STENCIL_WRITEMASK    equ 0x0B98
GL_MATRIX_MODE          equ 0x0BA0
GL_NORMALIZE            equ 0x0BA1
GL_VIEWPORT             equ 0x0BA2
GL_MODELVIEW_STACK_DEPTH equ 0x0BA3
GL_PROJECTION_STACK_DEPTH equ 0x0BA4
GL_TEXTURE_STACK_DEPTH  equ 0x0BA5
GL_MODELVIEW_MATRIX     equ 0x0BA6
GL_PROJECTION_MATRIX    equ 0x0BA7
GL_TEXTURE_MATRIX       equ 0x0BA8
GL_ATTRIB_STACK_DEPTH   equ 0x0BB0
GL_CLIENT_ATTRIB_STACK_DEPTH equ 0x0BB1
GL_ALPHA_TEST           equ 0x0BC0
GL_ALPHA_TEST_FUNC      equ 0x0BC1
GL_ALPHA_TEST_REF       equ 0x0BC2
GL_DITHER               equ 0x0BD0
GL_BLEND_DST            equ 0x0BE0
GL_BLEND_SRC            equ 0x0BE1
GL_BLEND                equ 0x0BE2
GL_LOGIC_OP_MODE        equ 0x0BF0
GL_INDEX_LOGIC_OP       equ 0x0BF1
GL_COLOR_LOGIC_OP       equ 0x0BF2
GL_AUX_BUFFERS          equ 0x0C00
GL_DRAW_BUFFER          equ 0x0C01
GL_READ_BUFFER          equ 0x0C02
GL_SCISSOR_BOX          equ 0x0C10
GL_SCISSOR_TEST         equ 0x0C11
GL_INDEX_CLEAR_VALUE    equ 0x0C20
GL_INDEX_WRITEMASK      equ 0x0C21
GL_COLOR_CLEAR_VALUE    equ 0x0C22
GL_COLOR_WRITEMASK      equ 0x0C23
GL_INDEX_MODE           equ 0x0C30
GL_RGBA_MODE            equ 0x0C31
GL_DOUBLEBUFFER         equ 0x0C32
GL_STEREO               equ 0x0C33
GL_RENDER_MODE          equ 0x0C40
GL_PERSPECTIVE_CORRECTION_HINT equ 0x0C50
GL_POINT_SMOOTH_HINT    equ 0x0C51
GL_LINE_SMOOTH_HINT     equ 0x0C52
GL_POLYGON_SMOOTH_HINT  equ 0x0C53
GL_FOG_HINT             equ 0x0C54
GL_TEXTURE_GEN_S        equ 0x0C60
GL_TEXTURE_GEN_T        equ 0x0C61
GL_TEXTURE_GEN_R        equ 0x0C62
GL_TEXTURE_GEN_Q        equ 0x0C63
GL_PIXEL_MAP_I_TO_I     equ 0x0C70
GL_PIXEL_MAP_S_TO_S     equ 0x0C71
GL_PIXEL_MAP_I_TO_R     equ 0x0C72
GL_PIXEL_MAP_I_TO_G     equ 0x0C73
GL_PIXEL_MAP_I_TO_B     equ 0x0C74
GL_PIXEL_MAP_I_TO_A     equ 0x0C75
GL_PIXEL_MAP_R_TO_R     equ 0x0C76
GL_PIXEL_MAP_G_TO_G     equ 0x0C77
GL_PIXEL_MAP_B_TO_B     equ 0x0C78
GL_PIXEL_MAP_A_TO_A     equ 0x0C79
GL_PIXEL_MAP_I_TO_I_SIZE equ 0x0CB0
GL_PIXEL_MAP_S_TO_S_SIZE equ 0x0CB1
GL_PIXEL_MAP_I_TO_R_SIZE equ 0x0CB2
GL_PIXEL_MAP_I_TO_G_SIZE equ 0x0CB3
GL_PIXEL_MAP_I_TO_B_SIZE equ 0x0CB4
GL_PIXEL_MAP_I_TO_A_SIZE equ 0x0CB5
GL_PIXEL_MAP_R_TO_R_SIZE equ 0x0CB6
GL_PIXEL_MAP_G_TO_G_SIZE equ 0x0CB7
GL_PIXEL_MAP_B_TO_B_SIZE equ 0x0CB8
GL_PIXEL_MAP_A_TO_A_SIZE equ 0x0CB9
GL_UNPACK_SWAP_BYTES    equ 0x0CF0
GL_UNPACK_LSB_FIRST     equ 0x0CF1
GL_UNPACK_ROW_LENGTH    equ 0x0CF2
GL_UNPACK_SKIP_ROWS     equ 0x0CF3
GL_UNPACK_SKIP_PIXELS   equ 0x0CF4
GL_UNPACK_ALIGNMENT     equ 0x0CF5
GL_PACK_SWAP_BYTES      equ 0x0D00
GL_PACK_LSB_FIRST       equ 0x0D01
GL_PACK_ROW_LENGTH      equ 0x0D02
GL_PACK_SKIP_ROWS       equ 0x0D03
GL_PACK_SKIP_PIXELS     equ 0x0D04
GL_PACK_ALIGNMENT       equ 0x0D05
GL_MAP_COLOR            equ 0x0D10
GL_MAP_STENCIL          equ 0x0D11
GL_INDEX_SHIFT          equ 0x0D12
GL_INDEX_OFFSET         equ 0x0D13
GL_RED_SCALE            equ 0x0D14
GL_RED_BIAS             equ 0x0D15
GL_ZOOM_X               equ 0x0D16
GL_ZOOM_Y               equ 0x0D17
GL_GREEN_SCALE          equ 0x0D18
GL_GREEN_BIAS           equ 0x0D19
GL_BLUE_SCALE           equ 0x0D1A
GL_BLUE_BIAS            equ 0x0D1B
GL_ALPHA_SCALE          equ 0x0D1C
GL_ALPHA_BIAS           equ 0x0D1D
GL_DEPTH_SCALE          equ 0x0D1E
GL_DEPTH_BIAS           equ 0x0D1F
GL_MAX_EVAL_ORDER       equ 0x0D30
GL_MAX_LIGHTS           equ 0x0D31
GL_MAX_CLIP_PLANES      equ 0x0D32
GL_MAX_TEXTURE_SIZE     equ 0x0D33
GL_MAX_PIXEL_MAP_TABLE  equ 0x0D34
GL_MAX_ATTRIB_STACK_DEPTH equ 0x0D35
GL_MAX_MODELVIEW_STACK_DEPTH equ 0x0D36
GL_MAX_NAME_STACK_DEPTH equ 0x0D37
GL_MAX_PROJECTION_STACK_DEPTH equ 0x0D38
GL_MAX_TEXTURE_STACK_DEPTH equ 0x0D39
GL_MAX_VIEWPORT_DIMS    equ 0x0D3A
GL_MAX_CLIENT_ATTRIB_STACK_DEPTH equ 0x0D3B
GL_SUBPIXEL_BITS        equ 0x0D50
GL_INDEX_BITS           equ 0x0D51
GL_RED_BITS             equ 0x0D52
GL_GREEN_BITS           equ 0x0D53
GL_BLUE_BITS            equ 0x0D54
GL_ALPHA_BITS           equ 0x0D55
GL_DEPTH_BITS           equ 0x0D56
GL_STENCIL_BITS         equ 0x0D57
GL_ACCUM_RED_BITS       equ 0x0D58
GL_ACCUM_GREEN_BITS     equ 0x0D59
GL_ACCUM_BLUE_BITS      equ 0x0D5A
GL_ACCUM_ALPHA_BITS     equ 0x0D5B
GL_NAME_STACK_DEPTH     equ 0x0D70
GL_AUTO_NORMAL          equ 0x0D80
GL_MAP1_COLOR_4         equ 0x0D90
GL_MAP1_INDEX           equ 0x0D91
GL_MAP1_NORMAL          equ 0x0D92
GL_MAP1_TEXTURE_COORD_1 equ 0x0D93
GL_MAP1_TEXTURE_COORD_2 equ 0x0D94
GL_MAP1_TEXTURE_COORD_3 equ 0x0D95
GL_MAP1_TEXTURE_COORD_4 equ 0x0D96
GL_MAP1_VERTEX_3        equ 0x0D97
GL_MAP1_VERTEX_4        equ 0x0D98
GL_MAP2_COLOR_4         equ 0x0DB0
GL_MAP2_INDEX           equ 0x0DB1
GL_MAP2_NORMAL          equ 0x0DB2
GL_MAP2_TEXTURE_COORD_1 equ 0x0DB3
GL_MAP2_TEXTURE_COORD_2 equ 0x0DB4
GL_MAP2_TEXTURE_COORD_3 equ 0x0DB5
GL_MAP2_TEXTURE_COORD_4 equ 0x0DB6
GL_MAP2_VERTEX_3        equ 0x0DB7
GL_MAP2_VERTEX_4        equ 0x0DB8
GL_MAP1_GRID_DOMAIN     equ 0x0DD0
GL_MAP1_GRID_SEGMENTS   equ 0x0DD1
GL_MAP2_GRID_DOMAIN     equ 0x0DD2
GL_MAP2_GRID_SEGMENTS   equ 0x0DD3
GL_TEXTURE_1D           equ 0x0DE0
GL_TEXTURE_2D           equ 0x0DE1
GL_FEEDBACK_BUFFER_POINTER equ 0x0DF0
GL_FEEDBACK_BUFFER_SIZE equ 0x0DF1
GL_FEEDBACK_BUFFER_TYPE equ 0x0DF2
GL_SELECTION_BUFFER_POINTER equ 0x0DF3
GL_SELECTION_BUFFER_SIZE equ 0x0DF4

GL_TEXTURE_WIDTH        equ 0x1000
GL_TEXTURE_HEIGHT       equ 0x1001
GL_TEXTURE_INTERNAL_FORMAT equ 0x1003
GL_TEXTURE_BORDER_COLOR equ 0x1004
GL_TEXTURE_BORDER       equ 0x1005

GL_DONT_CARE            equ 0x1100
GL_FASTEST              equ 0x1101
GL_NICEST               equ 0x1102

GL_LIGHT0               equ 0x4000
GL_LIGHT1               equ 0x4001
GL_LIGHT2               equ 0x4002
GL_LIGHT3               equ 0x4003
GL_LIGHT4               equ 0x4004
GL_LIGHT5               equ 0x4005
GL_LIGHT6               equ 0x4006
GL_LIGHT7               equ 0x4007

GL_AMBIENT              equ 0x1200
GL_DIFFUSE              equ 0x1201
GL_SPECULAR             equ 0x1202
GL_POSITION             equ 0x1203
GL_SPOT_DIRECTION       equ 0x1204
GL_SPOT_EXPONENT        equ 0x1205
GL_SPOT_CUTOFF          equ 0x1206
GL_CONSTANT_ATTENUATION equ 0x1207
GL_LINEAR_ATTENUATION   equ 0x1208
GL_QUADRATIC_ATTENUATION equ 0x1209

GL_COMPILE              equ 0x1300
GL_COMPILE_AND_EXECUTE  equ 0x1301

GL_CLEAR                equ 0x1500
GL_AND                  equ 0x1501
GL_AND_REVERSE          equ 0x1502
GL_COPY                 equ 0x1503
GL_AND_INVERTED         equ 0x1504
GL_NOOP                 equ 0x1505
GL_XOR                  equ 0x1506
GL_OR                   equ 0x1507
GL_NOR                  equ 0x1508
GL_EQUIV                equ 0x1509
GL_INVERT               equ 0x150A
GL_OR_REVERSE           equ 0x150B
GL_COPY_INVERTED        equ 0x150C
GL_OR_INVERTED          equ 0x150D
GL_NAND                 equ 0x150E
GL_SET                  equ 0x150F

GL_EMISSION             equ 0x1600
GL_SHININESS            equ 0x1601
GL_AMBIENT_AND_DIFFUSE  equ 0x1602
GL_COLOR_INDEXES        equ 0x1603

GL_MODELVIEW            equ 0x1700
GL_PROJECTION           equ 0x1701
GL_TEXTURE              equ 0x1702

GL_COLOR                equ 0x1800
GL_DEPTH                equ 0x1801
GL_STENCIL              equ 0x1802

GL_COLOR_INDEX          equ 0x1900
GL_STENCIL_INDEX        equ 0x1901
GL_DEPTH_COMPONENT      equ 0x1902
GL_RED                  equ 0x1903
GL_GREEN                equ 0x1904
GL_BLUE                 equ 0x1905
GL_ALPHA                equ 0x1906
GL_RGB                  equ 0x1907
GL_RGBA                 equ 0x1908
GL_LUMINANCE            equ 0x1909
GL_LUMINANCE_ALPHA      equ 0x190A

GL_BITMAP               equ 0x1A00

GL_POINT                equ 0x1B00
GL_LINE                 equ 0x1B01
GL_FILL                 equ 0x1B02

GL_RENDER               equ 0x1C00
GL_FEEDBACK             equ 0x1C01
GL_SELECT               equ 0x1C02

GL_FLAT                 equ 0x1D00
GL_SMOOTH               equ 0x1D01

GL_KEEP                 equ 0x1E00
GL_REPLACE              equ 0x1E01
GL_INCR                 equ 0x1E02
GL_DECR                 equ 0x1E03

GL_VENDOR               equ 0x1F00
GL_RENDERER             equ 0x1F01
GL_VERSION              equ 0x1F02
GL_EXTENSIONS           equ 0x1F03

GL_S                    equ 0x2000
GL_T                    equ 0x2001
GL_R                    equ 0x2002
GL_Q                    equ 0x2003

GL_MODULATE             equ 0x2100
GL_DECAL                equ 0x2101

GL_TEXTURE_ENV_MODE     equ 0x2200
GL_TEXTURE_ENV_COLOR    equ 0x2201

GL_TEXTURE_ENV          equ 0x2300

GL_EYE_LINEAR           equ 0x2400
GL_OBJECT_LINEAR        equ 0x2401
GL_SPHERE_MAP           equ 0x2402

GL_TEXTURE_GEN_MODE     equ 0x2500
GL_OBJECT_PLANE         equ 0x2501
GL_EYE_PLANE            equ 0x2502

GL_NEAREST              equ 0x2600
GL_LINEAR               equ 0x2601

GL_NEAREST_MIPMAP_NEAREST equ 0x2700
GL_LINEAR_MIPMAP_NEAREST equ 0x2701
GL_NEAREST_MIPMAP_LINEAR equ 0x2702
GL_LINEAR_MIPMAP_LINEAR equ 0x2703

GL_TEXTURE_MAG_FILTER   equ 0x2800
GL_TEXTURE_MIN_FILTER   equ 0x2801
GL_TEXTURE_WRAP_S       equ 0x2802
GL_TEXTURE_WRAP_T       equ 0x2803

GL_CLAMP                equ 0x2900
GL_REPEAT               equ 0x2901

GL_CLIENT_PIXEL_STORE_BIT equ 0x00000001
GL_CLIENT_VERTEX_ARRAY_BIT equ 0x00000002
GL_CLIENT_ALL_ATTRIB_BITS equ 0xffffffff

GL_POLYGON_OFFSET_FACTOR equ 0x8038
GL_POLYGON_OFFSET_UNITS equ 0x2A00
GL_POLYGON_OFFSET_POINT equ 0x2A01
GL_POLYGON_OFFSET_LINE  equ 0x2A02
GL_POLYGON_OFFSET_FILL  equ 0x8037

GL_ALPHA4               equ 0x803B
GL_ALPHA8               equ 0x803C
GL_ALPHA12              equ 0x803D
GL_ALPHA16              equ 0x803E
GL_LUMINANCE4           equ 0x803F
GL_LUMINANCE8           equ 0x8040
GL_LUMINANCE12          equ 0x8041
GL_LUMINANCE16          equ 0x8042
GL_LUMINANCE4_ALPHA4    equ 0x8043
GL_LUMINANCE6_ALPHA2    equ 0x8044
GL_LUMINANCE8_ALPHA8    equ 0x8045
GL_LUMINANCE12_ALPHA4   equ 0x8046
GL_LUMINANCE12_ALPHA12  equ 0x8047
GL_LUMINANCE16_ALPHA16  equ 0x8048
GL_INTENSITY            equ 0x8049
GL_INTENSITY4           equ 0x804A
GL_INTENSITY8           equ 0x804B
GL_INTENSITY12          equ 0x804C
GL_INTENSITY16          equ 0x804D
GL_R3_G3_B2             equ 0x2A10
GL_RGB4                 equ 0x804F
GL_RGB5                 equ 0x8050
GL_RGB8                 equ 0x8051
GL_RGB10                equ 0x8052
GL_RGB12                equ 0x8053
GL_RGB16                equ 0x8054
GL_RGBA2                equ 0x8055
GL_RGBA4                equ 0x8056
GL_RGB5_A1              equ 0x8057
GL_RGBA8                equ 0x8058
GL_RGB10_A2             equ 0x8059
GL_RGBA12               equ 0x805A
GL_RGBA16               equ 0x805B
GL_TEXTURE_RED_SIZE     equ 0x805C
GL_TEXTURE_GREEN_SIZE   equ 0x805D
GL_TEXTURE_BLUE_SIZE    equ 0x805E
GL_TEXTURE_ALPHA_SIZE   equ 0x805F
GL_TEXTURE_LUMINANCE_SIZE equ 0x8060
GL_TEXTURE_INTENSITY_SIZE equ 0x8061
GL_PROXY_TEXTURE_1D     equ 0x8063
GL_PROXY_TEXTURE_2D     equ 0x8064

GL_TEXTURE_PRIORITY     equ 0x8066
GL_TEXTURE_RESIDENT     equ 0x8067
GL_TEXTURE_BINDING_1D   equ 0x8068
GL_TEXTURE_BINDING_2D   equ 0x8069

GL_VERTEX_ARRAY         equ 0x8074
GL_NORMAL_ARRAY         equ 0x8075
GL_COLOR_ARRAY          equ 0x8076
GL_INDEX_ARRAY          equ 0x8077
GL_TEXTURE_COORD_ARRAY  equ 0x8078
GL_EDGE_FLAG_ARRAY      equ 0x8079
GL_VERTEX_ARRAY_SIZE    equ 0x807A
GL_VERTEX_ARRAY_TYPE    equ 0x807B
GL_VERTEX_ARRAY_STRIDE  equ 0x807C
GL_NORMAL_ARRAY_TYPE    equ 0x807E
GL_NORMAL_ARRAY_STRIDE  equ 0x807F
GL_COLOR_ARRAY_SIZE     equ 0x8081
GL_COLOR_ARRAY_TYPE     equ 0x8082
GL_COLOR_ARRAY_STRIDE   equ 0x8083
GL_INDEX_ARRAY_TYPE     equ 0x8085
GL_INDEX_ARRAY_STRIDE   equ 0x8086
GL_TEXTURE_COORD_ARRAY_SIZE equ 0x8088
GL_TEXTURE_COORD_ARRAY_TYPE equ 0x8089
GL_TEXTURE_COORD_ARRAY_STRIDE equ 0x808A
GL_EDGE_FLAG_ARRAY_STRIDE equ 0x808C
GL_VERTEX_ARRAY_POINTER equ 0x808E
GL_NORMAL_ARRAY_POINTER equ 0x808F
GL_COLOR_ARRAY_POINTER  equ 0x8090
GL_INDEX_ARRAY_POINTER  equ 0x8091
GL_TEXTURE_COORD_ARRAY_POINTER equ 0x8092
GL_EDGE_FLAG_ARRAY_POINTER equ 0x8093
GL_V2F                  equ 0x2A20
GL_V3F                  equ 0x2A21
GL_C4UB_V2F             equ 0x2A22
GL_C4UB_V3F             equ 0x2A23
GL_C3F_V3F              equ 0x2A24
GL_N3F_V3F              equ 0x2A25
GL_C4F_N3F_V3F          equ 0x2A26
GL_T2F_V3F              equ 0x2A27
GL_T4F_V4F              equ 0x2A28
GL_T2F_C4UB_V3F         equ 0x2A29
GL_T2F_C3F_V3F          equ 0x2A2A
GL_T2F_N3F_V3F          equ 0x2A2B
GL_T2F_C4F_N3F_V3F      equ 0x2A2C
GL_T4F_C4F_N3F_V4F      equ 0x2A2D

GL_EXT_vertex_array     equ 1
GL_EXT_bgra             equ 1
GL_EXT_paletted_texture equ 1
GL_WIN_swap_hint        equ 1
GL_WIN_draw_range_elements equ 1

GL_VERTEX_ARRAY_EXT     equ 0x8074
GL_NORMAL_ARRAY_EXT     equ 0x8075
GL_COLOR_ARRAY_EXT      equ 0x8076
GL_INDEX_ARRAY_EXT      equ 0x8077
GL_TEXTURE_COORD_ARRAY_EXT equ 0x8078
GL_EDGE_FLAG_ARRAY_EXT  equ 0x8079
GL_VERTEX_ARRAY_SIZE_EXT equ 0x807A
GL_VERTEX_ARRAY_TYPE_EXT equ 0x807B
GL_VERTEX_ARRAY_STRIDE_EXT equ 0x807C
GL_VERTEX_ARRAY_COUNT_EXT equ 0x807D
GL_NORMAL_ARRAY_TYPE_EXT equ 0x807E
GL_NORMAL_ARRAY_STRIDE_EXT equ 0x807F
GL_NORMAL_ARRAY_COUNT_EXT equ 0x8080
GL_COLOR_ARRAY_SIZE_EXT equ 0x8081
GL_COLOR_ARRAY_TYPE_EXT equ 0x8082
GL_COLOR_ARRAY_STRIDE_EXT equ 0x8083
GL_COLOR_ARRAY_COUNT_EXT equ 0x8084
GL_INDEX_ARRAY_TYPE_EXT equ 0x8085
GL_INDEX_ARRAY_STRIDE_EXT equ 0x8086
GL_INDEX_ARRAY_COUNT_EXT equ 0x8087
GL_TEXTURE_COORD_ARRAY_SIZE_EXT equ 0x8088
GL_TEXTURE_COORD_ARRAY_TYPE_EXT equ 0x8089
GL_TEXTURE_COORD_ARRAY_STRIDE_EXT equ 0x808A
GL_TEXTURE_COORD_ARRAY_COUNT_EXT equ 0x808B
GL_EDGE_FLAG_ARRAY_STRIDE_EXT equ 0x808C
GL_EDGE_FLAG_ARRAY_COUNT_EXT equ 0x808D
GL_VERTEX_ARRAY_POINTER_EXT equ 0x808E
GL_NORMAL_ARRAY_POINTER_EXT equ 0x808F
GL_COLOR_ARRAY_POINTER_EXT equ 0x8090
GL_INDEX_ARRAY_POINTER_EXT equ 0x8091
GL_TEXTURE_COORD_ARRAY_POINTER_EXT equ 0x8092
GL_EDGE_FLAG_ARRAY_POINTER_EXT equ 0x8093
GL_DOUBLE_EXT           equ GL_DOUBLE

GL_BGR_EXT              equ 0x80E0
GL_BGRA_EXT             equ 0x80E1

GL_COLOR_TABLE_FORMAT_EXT equ 0x80D8
GL_COLOR_TABLE_WIDTH_EXT equ 0x80D9
GL_COLOR_TABLE_RED_SIZE_EXT equ 0x80DA
GL_COLOR_TABLE_GREEN_SIZE_EXT equ 0x80DB
GL_COLOR_TABLE_BLUE_SIZE_EXT equ 0x80DC
GL_COLOR_TABLE_ALPHA_SIZE_EXT equ 0x80DD
GL_COLOR_TABLE_LUMINANCE_SIZE_EXT equ 0x80DE
GL_COLOR_TABLE_INTENSITY_SIZE_EXT equ 0x80DF

GL_COLOR_INDEX1_EXT     equ 0x80E2
GL_COLOR_INDEX2_EXT     equ 0x80E3
GL_COLOR_INDEX4_EXT     equ 0x80E4
GL_COLOR_INDEX8_EXT     equ 0x80E5
GL_COLOR_INDEX12_EXT    equ 0x80E6
GL_COLOR_INDEX16_EXT    equ 0x80E7

GL_MAX_ELEMENTS_VERTICES_WIN equ 0x80E8
GL_MAX_ELEMENTS_INDICES_WIN equ 0x80E9

GL_PHONG_WIN            equ 0x80EA
GL_PHONG_HINT_WIN       equ 0x80EB

GL_FOG_SPECULAR_TEXTURE_WIN equ 0x80EC

GL_LOGIC_OP             equ GL_INDEX_LOGIC_OP
GL_TEXTURE_COMPONENTS   equ GL_TEXTURE_INTERNAL_FORMAT

;WINGDIAPI
glAccum proto WINAPI \
                    op: GLenum,
                 value: GLfloat

glAlphaFunc proto WINAPI \
                  func: GLenum,
                   ref: GLclampf

glAreTexturesResident proto WINAPI \
                     n: GLsizei,
              textures: ptr GLuint,
            residences: ptr GLboolean

glArrayElement proto WINAPI \
                     i: GLint

glBegin proto WINAPI \
                  mode: GLenum

glBindTexture proto WINAPI \
                target: GLenum,
               texture: GLuint

glBitmap proto WINAPI \
                _width: GLsizei,
                height: GLsizei,
                 xorig: GLfloat,
                 yorig: GLfloat,
                 xmove: GLfloat,
                 ymove: GLfloat,
                bitmap: ptr GLubyte

glBlendFunc proto WINAPI \
               sfactor: GLenum,
               dfactor: GLenum

glCallList proto WINAPI \
                  list: GLuint

glCallLists proto WINAPI \
                     n: GLsizei,
                 _type: GLenum,
                 lists: ptr GLvoid

glClear proto WINAPI \
                 _mask: GLbitfield

glClearAccum proto WINAPI \
                   red: GLfloat,
                 green: GLfloat,
                  blue: GLfloat,
                 alpha: GLfloat

glClearColor proto WINAPI \
                   red: GLclampf,
                 green: GLclampf,
                  blue: GLclampf,
                 alpha: GLclampf

glClearDepth proto WINAPI \
                 depth: GLclampd

glClearIndex proto WINAPI \
                    _c: GLfloat

glClearStencil proto WINAPI \
                     s: GLint

glClipPlane proto WINAPI \
                 plane: GLenum,
              equation: ptr GLdouble

glColor3b proto WINAPI \
                   red: GLbyte,
                 green: GLbyte,
                  blue: GLbyte

glColor3bv proto WINAPI \
                     v: ptr GLbyte

glColor3d proto WINAPI \
                   red: GLdouble,
                 green: GLdouble,
                  blue: GLdouble

glColor3dv proto WINAPI \
                     v: ptr GLdouble

glColor3f proto WINAPI \
                   red: GLfloat,
                 green: GLfloat,
                  blue: GLfloat

glColor3fv proto WINAPI \
                     v: ptr GLfloat

glColor3i proto WINAPI \
                   red: GLint,
                 green: GLint,
                  blue: GLint

glColor3iv proto WINAPI \
                     v: ptr GLint

glColor3s proto WINAPI \
                   red: GLshort,
                 green: GLshort,
                  blue: GLshort

glColor3sv proto WINAPI \
                     v: ptr GLshort

glColor3ub proto WINAPI \
                   red: GLubyte,
                 green: GLubyte,
                  blue: GLubyte

glColor3ubv proto WINAPI \
                     v: ptr GLubyte

glColor3ui proto WINAPI \
                   red: GLuint,
                 green: GLuint,
                  blue: GLuint

glColor3uiv proto WINAPI \
                     v: ptr GLuint

glColor3us proto WINAPI \
                   red: GLushort,
                 green: GLushort,
                  blue: GLushort

glColor3usv proto WINAPI \
                     v: ptr GLushort

glColor4b proto WINAPI \
                   red: GLbyte,
                 green: GLbyte,
                  blue: GLbyte,
                 alpha: GLbyte

glColor4bv proto WINAPI \
                     v: ptr GLbyte

glColor4d proto WINAPI \
                   red: GLdouble,
                 green: GLdouble,
                  blue: GLdouble,
                 alpha: GLdouble

glColor4dv proto WINAPI \
                     v: ptr GLdouble

glColor4f proto WINAPI \
                   red: GLfloat,
                 green: GLfloat,
                  blue: GLfloat,
                 alpha: GLfloat

glColor4fv proto WINAPI \
                     v: ptr GLfloat

glColor4i proto WINAPI \
                   red: GLint,
                 green: GLint,
                  blue: GLint,
                 alpha: GLint

glColor4iv proto WINAPI \
                     v: ptr GLint

glColor4s proto WINAPI \
                   red: GLshort,
                 green: GLshort,
                  blue: GLshort,
                 alpha: GLshort

glColor4sv proto WINAPI \
                     v: ptr GLshort

glColor4ub proto WINAPI \
                   red: GLubyte,
                 green: GLubyte,
                  blue: GLubyte,
                 alpha: GLubyte

glColor4ubv proto WINAPI \
                     v: ptr GLubyte

glColor4ui proto WINAPI \
                   red: GLuint,
                 green: GLuint,
                  blue: GLuint,
                 alpha: GLuint

glColor4uiv proto WINAPI \
                     v: ptr GLuint

glColor4us proto WINAPI \
                   red: GLushort,
                 green: GLushort,
                  blue: GLushort,
                 alpha: GLushort

glColor4usv proto WINAPI \
                     v: ptr GLushort

glColorMask proto WINAPI \
                   red: GLboolean,
                 green: GLboolean,
                  blue: GLboolean,
                 alpha: GLboolean

glColorMaterial proto WINAPI \
                  face: GLenum,
                  mode: GLenum

glColorPointer proto WINAPI \
                 _size: GLint,
                 _type: GLenum,
                stride: GLsizei,
               pointer: ptr GLvoid

glCopyPixels proto WINAPI \
                     x: GLint,
                     y: GLint,
                _width: GLsizei,
                height: GLsizei,
                 _type: GLenum

glCopyTexImage1D proto WINAPI \
                target: GLenum,
                 level: GLint,
        internalFormat: GLenum,
                     x: GLint,
                     y: GLint,
                _width: GLsizei,
                border: GLint

glCopyTexImage2D proto WINAPI \
                target: GLenum,
                 level: GLint,
        internalFormat: GLenum,
                     x: GLint,
                     y: GLint,
                _width: GLsizei,
                height: GLsizei,
                border: GLint

glCopyTexSubImage1D proto WINAPI \
                target: GLenum,
                 level: GLint,
               xoffset: GLint,
                     x: GLint,
                     y: GLint,
                _width: GLsizei

glCopyTexSubImage2D proto WINAPI \
                target: GLenum,
                 level: GLint,
               xoffset: GLint,
               yoffset: GLint,
                     x: GLint,
                     y: GLint,
                _width: GLsizei,
                height: GLsizei

glCullFace proto WINAPI \
                 _mode: GLenum

glDeleteLists proto WINAPI \
                 _list: GLuint,
                 range: GLsizei

glDeleteTextures proto WINAPI \
                     n: GLsizei,
              textures: ptr GLuint

glDepthFunc proto WINAPI \
                  func: GLenum

glDepthMask proto WINAPI \
                  flag: GLboolean

glDepthRange proto WINAPI \
                 zNear: GLclampd,
                  zFar: GLclampd

glDisable proto WINAPI \
                   cap: GLenum

glDisableClientState proto WINAPI \
                 array: GLenum

glDrawArrays proto WINAPI \
                  mode: GLenum,
                 first: GLint,
                 count: GLsizei

glDrawBuffer proto WINAPI \
                  mode: GLenum

glDrawElements proto WINAPI \
                  mode: GLenum,
                 count: GLsizei,
                 _type: GLenum,
               indices: ptr GLvoid

glDrawPixels proto WINAPI \
                _width: GLsizei,
                height: GLsizei,
                format: GLenum,
                 _type: GLenum,
                pixels: ptr GLvoid

glEdgeFlag proto WINAPI \
                  flag: GLboolean

glEdgeFlagPointer proto WINAPI \
                stride: GLsizei,
               pointer: ptr GLvoid

glEdgeFlagv proto WINAPI \
                  flag: ptr GLboolean

glEnable proto WINAPI \
                   cap: GLenum

glEnableClientState proto WINAPI \
                 array: GLenum

glEnd proto WINAPI
glEndList proto WINAPI
glEvalCoord1d proto WINAPI \
                     u: GLdouble

glEvalCoord1dv proto WINAPI \
                     u: ptr GLdouble

glEvalCoord1f proto WINAPI \
                     u: GLfloat

glEvalCoord1fv proto WINAPI \
                     u: ptr GLfloat

glEvalCoord2d proto WINAPI \
                     u: GLdouble,
                     v: GLdouble

glEvalCoord2dv proto WINAPI \
                     u: ptr GLdouble

glEvalCoord2f proto WINAPI \
                     u: GLfloat,
                     v: GLfloat

glEvalCoord2fv proto WINAPI \
                     u: ptr GLfloat

glEvalMesh1 proto WINAPI \
                  mode: GLenum,
                    i1: GLint,
                    i2: GLint

glEvalMesh2 proto WINAPI \
                  mode: GLenum,
                    i1: GLint,
                    i2: GLint,
                    j1: GLint,
                    j2: GLint

glEvalPoint1 proto WINAPI \
                     i: GLint

glEvalPoint2 proto WINAPI \
                     i: GLint,
                     j: GLint

glFeedbackBuffer proto WINAPI \
                 _size: GLsizei,
                 _type: GLenum,
                buffer: ptr GLfloat

glFinish proto WINAPI
glFlush proto WINAPI
glFogf proto WINAPI \
                 pname: GLenum,
                 param: GLfloat

glFogfv proto WINAPI \
                 pname: GLenum,
                params: ptr GLfloat

glFogi proto WINAPI \
                 pname: GLenum,
                 param: GLint

glFogiv proto WINAPI \
                 pname: GLenum,
                params: ptr GLint

glFrontFace proto WINAPI \
                  mode: GLenum

glFrustum proto WINAPI \
                  left: GLdouble,
                 right: GLdouble,
                bottom: GLdouble,
                   top: GLdouble,
                 zNear: GLdouble,
                  zFar: GLdouble

glGenLists proto WINAPI \
                 range: GLsizei

glGenTextures proto WINAPI \
                     n: GLsizei,
              textures: ptr GLuint

glGetBooleanv proto WINAPI \
                 pname: GLenum,
                params: ptr GLboolean

glGetClipPlane proto WINAPI \
                 plane: GLenum,
              equation: ptr GLdouble

glGetDoublev proto WINAPI \
                 pname: GLenum,
                params: ptr GLdouble

glGetError proto WINAPI
glGetFloatv proto WINAPI \
                 pname: GLenum,
                params: ptr GLfloat

glGetIntegerv proto WINAPI \
                 pname: GLenum,
                params: ptr GLint

glGetLightfv proto WINAPI \
                 light: GLenum,
                 pname: GLenum,
                params: ptr GLfloat

glGetLightiv proto WINAPI \
                 light: GLenum,
                 pname: GLenum,
                params: ptr GLint

glGetMapdv proto WINAPI \
                target: GLenum,
                 query: GLenum,
                     v: ptr GLdouble

glGetMapfv proto WINAPI \
                target: GLenum,
                 query: GLenum,
                     v: ptr GLfloat

glGetMapiv proto WINAPI \
                target: GLenum,
                 query: GLenum,
                     v: ptr GLint

glGetMaterialfv proto WINAPI \
                  face: GLenum,
                 pname: GLenum,
                params: ptr GLfloat

glGetMaterialiv proto WINAPI \
                  face: GLenum,
                 pname: GLenum,
                params: ptr GLint

glGetPixelMapfv proto WINAPI \
                   map: GLenum,
                values: ptr GLfloat

glGetPixelMapuiv proto WINAPI \
                   map: GLenum,
                values: ptr GLuint

glGetPixelMapusv proto WINAPI \
                   map: GLenum,
                values: ptr GLushort

glGetPointerv proto WINAPI \
                 pname: GLenum,
                params: ptr GLvoid

glGetPolygonStipple proto WINAPI \
                 _mask: ptr GLubyte

glGetString proto WINAPI \
                 _name: GLenum

glGetTexEnvfv proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                params: ptr GLfloat

glGetTexEnviv proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                params: ptr GLint

glGetTexGendv proto WINAPI \
                 coord: GLenum,
                 pname: GLenum,
                params: ptr GLdouble

glGetTexGenfv proto WINAPI \
                 coord: GLenum,
                 pname: GLenum,
                params: ptr GLfloat

glGetTexGeniv proto WINAPI \
                 coord: GLenum,
                 pname: GLenum,
                params: ptr GLint

glGetTexImage proto WINAPI \
                target: GLenum,
                 level: GLint,
                format: GLenum,
                 _type: GLenum,
                pixels: ptr GLvoid

glGetTexLevelParameterfv proto WINAPI \
                target: GLenum,
                 level: GLint,
                 pname: GLenum,
                params: ptr GLfloat

glGetTexLevelParameteriv proto WINAPI \
                target: GLenum,
                 level: GLint,
                 pname: GLenum,
                params: ptr GLint

glGetTexParameterfv proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                params: ptr GLfloat

glGetTexParameteriv proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                params: ptr GLint

glHint proto WINAPI \
                target: GLenum,
                  mode: GLenum

glIndexMask proto WINAPI \
                 _mask: GLuint

glIndexPointer proto WINAPI \
                 _type: GLenum,
                stride: GLsizei,
               pointer: ptr GLvoid

;WINGDIAPI
glIndexd proto WINAPI \
                    _c: GLdouble

glIndexdv proto WINAPI \
                    _c: ptr GLdouble

glIndexf proto WINAPI \
                    _c: GLfloat

glIndexfv proto WINAPI \
                    _c: ptr GLfloat

glIndexi proto WINAPI \
                    _c: GLint

glIndexiv proto WINAPI \
                    _c: ptr GLint

glIndexs proto WINAPI \
                    _c: GLshort

glIndexsv proto WINAPI \
                    _c: ptr GLshort

glIndexub proto WINAPI \
                    _c: GLubyte

glIndexubv proto WINAPI \
                    _c: ptr GLubyte

glInitNames proto WINAPI
glInterleavedArrays proto WINAPI \
                format: GLenum,
                stride: GLsizei,
               pointer: ptr GLvoid

glIsEnabled proto WINAPI \
                   cap: GLenum

glIsList proto WINAPI \
                  list: GLuint

glIsTexture proto WINAPI \
               texture: GLuint

glLightModelf proto WINAPI \
                 pname: GLenum,
                 param: GLfloat

glLightModelfv proto WINAPI \
                 pname: GLenum,
                params: ptr GLfloat

glLightModeli proto WINAPI \
                 pname: GLenum,
                 param: GLint

glLightModeliv proto WINAPI \
                 pname: GLenum,
                params: ptr GLint

glLightf proto WINAPI \
                 light: GLenum,
                 pname: GLenum,
                 param: GLfloat

glLightfv proto WINAPI \
                 light: GLenum,
                 pname: GLenum,
                params: ptr GLfloat

glLighti proto WINAPI \
                 light: GLenum,
                 pname: GLenum,
                 param: GLint

glLightiv proto WINAPI \
                 light: GLenum,
                 pname: GLenum,
                params: ptr GLint

glLineStipple proto WINAPI \
                factor: GLint,
               pattern: GLushort

glLineWidth proto WINAPI \
                _width: GLfloat

glListBase proto WINAPI \
                  base: GLuint

glLoadIdentity proto WINAPI
glLoadMatrixd proto WINAPI \
                     m: ptr GLdouble

glLoadMatrixf proto WINAPI \
                     m: ptr GLfloat

glLoadName proto WINAPI \
                 _name: GLuint

glLogicOp proto WINAPI \
                opcode: GLenum

glMap1d proto WINAPI \
                target: GLenum,
                    u1: GLdouble,
                    u2: GLdouble,
                stride: GLint,
                 order: GLint,
                points: ptr GLdouble

glMap1f proto WINAPI \
                target: GLenum,
                    u1: GLfloat,
                    u2: GLfloat,
                stride: GLint,
                 order: GLint,
                points: ptr GLfloat

glMap2d proto WINAPI \
                target: GLenum,
                    u1: GLdouble,
                    u2: GLdouble,
               ustride: GLint,
                uorder: GLint,
                    v1: GLdouble,
                    v2: GLdouble,
               vstride: GLint,
                vorder: GLint,
                points: ptr GLdouble

glMap2f proto WINAPI \
                target: GLenum,
                    u1: GLfloat,
                    u2: GLfloat,
               ustride: GLint,
                uorder: GLint,
                    v1: GLfloat,
                    v2: GLfloat,
               vstride: GLint,
                vorder: GLint,
                points: ptr GLfloat

glMapGrid1d proto WINAPI \
                    un: GLint,
                    u1: GLdouble,
                    u2: GLdouble

glMapGrid1f proto WINAPI \
                    un: GLint,
                    u1: GLfloat,
                    u2: GLfloat

glMapGrid2d proto WINAPI \
                    un: GLint,
                    u1: GLdouble,
                    u2: GLdouble,
                    vn: GLint,
                    v1: GLdouble,
                    v2: GLdouble

glMapGrid2f proto WINAPI \
                    un: GLint,
                    u1: GLfloat,
                    u2: GLfloat,
                    vn: GLint,
                    v1: GLfloat,
                    v2: GLfloat

glMaterialf proto WINAPI \
                  face: GLenum,
                 pname: GLenum,
                 param: GLfloat

glMaterialfv proto WINAPI \
                  face: GLenum,
                 pname: GLenum,
                params: ptr GLfloat

glMateriali proto WINAPI \
                  face: GLenum,
                 pname: GLenum,
                 param: GLint

glMaterialiv proto WINAPI \
                  face: GLenum,
                 pname: GLenum,
                params: ptr GLint

glMatrixMode proto WINAPI \
                  mode: GLenum

glMultMatrixd proto WINAPI \
                     m: ptr GLdouble

glMultMatrixf proto WINAPI \
                     m: ptr GLfloat

glNewList proto WINAPI \
                  list: GLuint,
                  mode: GLenum

glNormal3b proto WINAPI \
                    nx: GLbyte,
                    ny: GLbyte,
                    nz: GLbyte

glNormal3bv proto WINAPI \
                     v: ptr GLbyte

glNormal3d proto WINAPI \
                    nx: GLdouble,
                    ny: GLdouble,
                    nz: GLdouble

glNormal3dv proto WINAPI \
                     v: ptr GLdouble

glNormal3f proto WINAPI \
                    nx: GLfloat,
                    ny: GLfloat,
                    nz: GLfloat

glNormal3fv proto WINAPI \
                     v: ptr GLfloat

glNormal3i proto WINAPI \
                    nx: GLint,
                    ny: GLint,
                    nz: GLint

glNormal3iv proto WINAPI \
                     v: ptr GLint

glNormal3s proto WINAPI \
                    nx: GLshort,
                    ny: GLshort,
                    nz: GLshort

glNormal3sv proto WINAPI \
                     v: ptr GLshort

glNormalPointer proto WINAPI \
                 _type: GLenum,
                stride: GLsizei,
               pointer: ptr GLvoid

glOrtho proto WINAPI \
                  left: GLdouble,
                 right: GLdouble,
                bottom: GLdouble,
                   top: GLdouble,
                 zNear: GLdouble,
                  zFar: GLdouble

glPassThrough proto WINAPI \
                 token: GLfloat

glPixelMapfv proto WINAPI \
                   map: GLenum,
               mapsize: GLsizei,
                values: ptr GLfloat

glPixelMapuiv proto WINAPI \
                   map: GLenum,
               mapsize: GLsizei,
                values: ptr GLuint

glPixelMapusv proto WINAPI \
                   map: GLenum,
               mapsize: GLsizei,
                values: ptr GLushort

glPixelStoref proto WINAPI \
                 pname: GLenum,
                 param: GLfloat

glPixelStorei proto WINAPI \
                 pname: GLenum,
                 param: GLint

glPixelTransferf proto WINAPI \
                 pname: GLenum,
                 param: GLfloat

glPixelTransferi proto WINAPI \
                 pname: GLenum,
                 param: GLint

glPixelZoom proto WINAPI \
               xfactor: GLfloat,
               yfactor: GLfloat

glPointSize proto WINAPI \
                 _size: GLfloat

glPolygonMode proto WINAPI \
                  face: GLenum,
                  mode: GLenum

glPolygonOffset proto WINAPI \
                factor: GLfloat,
                 units: GLfloat

glPolygonStipple proto WINAPI \
                 _mask: ptr GLubyte

glPopAttrib proto WINAPI
glPopClientAttrib proto WINAPI
glPopMatrix proto WINAPI
glPopName proto WINAPI
glPrioritizeTextures proto WINAPI \
                     n: GLsizei,
              textures: ptr GLuint,
            priorities: ptr GLclampf

glPushAttrib proto WINAPI \
                 _mask: GLbitfield

glPushClientAttrib proto WINAPI \
                 _mask: GLbitfield

glPushMatrix proto WINAPI
glPushName proto WINAPI \
                 _name: GLuint

glRasterPos2d proto WINAPI \
                     x: GLdouble,
                     y: GLdouble

glRasterPos2dv proto WINAPI \
                     v: ptr GLdouble

glRasterPos2f proto WINAPI \
                     x: GLfloat,
                     y: GLfloat

glRasterPos2fv proto WINAPI \
                     v: ptr GLfloat

glRasterPos2i proto WINAPI \
                     x: GLint,
                     y: GLint

glRasterPos2iv proto WINAPI \
                     v: ptr GLint

glRasterPos2s proto WINAPI \
                     x: GLshort,
                     y: GLshort

glRasterPos2sv proto WINAPI \
                     v: ptr GLshort

glRasterPos3d proto WINAPI \
                     x: GLdouble,
                     y: GLdouble,
                     z: GLdouble

glRasterPos3dv proto WINAPI \
                     v: ptr GLdouble

glRasterPos3f proto WINAPI \
                     x: GLfloat,
                     y: GLfloat,
                     z: GLfloat

glRasterPos3fv proto WINAPI \
                     v: ptr GLfloat

glRasterPos3i proto WINAPI \
                     x: GLint,
                     y: GLint,
                     z: GLint

glRasterPos3iv proto WINAPI \
                     v: ptr GLint

glRasterPos3s proto WINAPI \
                     x: GLshort,
                     y: GLshort,
                     z: GLshort

glRasterPos3sv proto WINAPI \
                     v: ptr GLshort

glRasterPos4d proto WINAPI \
                     x: GLdouble,
                     y: GLdouble,
                     z: GLdouble,
                     w: GLdouble

glRasterPos4dv proto WINAPI \
                     v: ptr GLdouble

glRasterPos4f proto WINAPI \
                     x: GLfloat,
                     y: GLfloat,
                     z: GLfloat,
                     w: GLfloat

glRasterPos4fv proto WINAPI \
                     v: ptr GLfloat

glRasterPos4i proto WINAPI \
                     x: GLint,
                     y: GLint,
                     z: GLint,
                     w: GLint

glRasterPos4iv proto WINAPI \
                     v: ptr GLint

glRasterPos4s proto WINAPI \
                     x: GLshort,
                     y: GLshort,
                     z: GLshort,
                     w: GLshort

glRasterPos4sv proto WINAPI \
                     v: ptr GLshort

glReadBuffer proto WINAPI \
                  mode: GLenum

glReadPixels proto WINAPI \
                     x: GLint,
                     y: GLint,
                _width: GLsizei,
                height: GLsizei,
                format: GLenum,
                 _type: GLenum,
                pixels: ptr GLvoid

glRectd proto WINAPI \
                    x1: GLdouble,
                    y1: GLdouble,
                    x2: GLdouble,
                    y2: GLdouble

glRectdv proto WINAPI \
                    v1: ptr GLdouble,
                    v2: ptr GLdouble

glRectf proto WINAPI \
                    x1: GLfloat,
                    y1: GLfloat,
                    x2: GLfloat,
                    y2: GLfloat

glRectfv proto WINAPI \
                    v1: ptr GLfloat,
                    v2: ptr GLfloat

glRecti proto WINAPI \
                    x1: GLint,
                    y1: GLint,
                    x2: GLint,
                    y2: GLint

glRectiv proto WINAPI \
                    v1: ptr GLint,
                    v2: ptr GLint

glRects proto WINAPI \
                    x1: GLshort,
                    y1: GLshort,
                    x2: GLshort,
                    y2: GLshort

glRectsv proto WINAPI \
                    v1: ptr GLshort,
                    v2: ptr GLshort

glRenderMode proto WINAPI \
                  mode: GLenum

glRotated proto WINAPI \
                 angle: GLdouble,
                     x: GLdouble,
                     y: GLdouble,
                     z: GLdouble

glRotatef proto WINAPI \
                 angle: GLfloat,
                     x: GLfloat,
                     y: GLfloat,
                     z: GLfloat

glScaled proto WINAPI \
                     x: GLdouble,
                     y: GLdouble,
                     z: GLdouble

glScalef proto WINAPI \
                     x: GLfloat,
                     y: GLfloat,
                     z: GLfloat

glScissor proto WINAPI \
                     x: GLint,
                     y: GLint,
                _width: GLsizei,
                height: GLsizei

glSelectBuffer proto WINAPI \
                 _size: GLsizei,
                buffer: ptr GLuint

glShadeModel proto WINAPI \
                  mode: GLenum

glStencilFunc proto WINAPI \
                  func: GLenum,
                   ref: GLint,
                 _mask: GLuint

glStencilMask proto WINAPI \
                 _mask: GLuint

glStencilOp proto WINAPI \
                  fail: GLenum,
                 zfail: GLenum,
                 zpass: GLenum

glTexCoord1d proto WINAPI \
                     s: GLdouble

glTexCoord1dv proto WINAPI \
                     v: ptr GLdouble

glTexCoord1f proto WINAPI \
                     s: GLfloat

glTexCoord1fv proto WINAPI \
                     v: ptr GLfloat

glTexCoord1i proto WINAPI \
                     s: GLint

glTexCoord1iv proto WINAPI \
                     v: ptr GLint

glTexCoord1s proto WINAPI \
                     s: GLshort

glTexCoord1sv proto WINAPI \
                     v: ptr GLshort

glTexCoord2d proto WINAPI \
                     s: GLdouble,
                     t: GLdouble

glTexCoord2dv proto WINAPI \
                     v: ptr GLdouble

glTexCoord2f proto WINAPI \
                     s: GLfloat,
                     t: GLfloat

glTexCoord2fv proto WINAPI \
                     v: ptr GLfloat

glTexCoord2i proto WINAPI \
                     s: GLint,
                     t: GLint

glTexCoord2iv proto WINAPI \
                     v: ptr GLint

glTexCoord2s proto WINAPI \
                     s: GLshort,
                     t: GLshort

glTexCoord2sv proto WINAPI \
                     v: ptr GLshort

glTexCoord3d proto WINAPI \
                     s: GLdouble,
                     t: GLdouble,
                     r: GLdouble

glTexCoord3dv proto WINAPI \
                     v: ptr GLdouble

glTexCoord3f proto WINAPI \
                     s: GLfloat,
                     t: GLfloat,
                     r: GLfloat

glTexCoord3fv proto WINAPI \
                     v: ptr GLfloat

glTexCoord3i proto WINAPI \
                     s: GLint,
                     t: GLint,
                     r: GLint

glTexCoord3iv proto WINAPI \
                     v: ptr GLint

glTexCoord3s proto WINAPI \
                     s: GLshort,
                     t: GLshort,
                     r: GLshort

glTexCoord3sv proto WINAPI \
                     v: ptr GLshort

glTexCoord4d proto WINAPI \
                     s: GLdouble,
                     t: GLdouble,
                     r: GLdouble,
                     q: GLdouble

glTexCoord4dv proto WINAPI \
                     v: ptr GLdouble

glTexCoord4f proto WINAPI \
                     s: GLfloat,
                     t: GLfloat,
                     r: GLfloat,
                     q: GLfloat

glTexCoord4fv proto WINAPI \
                     v: ptr GLfloat

glTexCoord4i proto WINAPI \
                     s: GLint,
                     t: GLint,
                     r: GLint,
                     q: GLint

glTexCoord4iv proto WINAPI \
                     v: ptr GLint

glTexCoord4s proto WINAPI \
                     s: GLshort,
                     t: GLshort,
                     r: GLshort,
                     q: GLshort

glTexCoord4sv proto WINAPI \
                     v: ptr GLshort

glTexCoordPointer proto WINAPI \
                 _size: GLint,
                 _type: GLenum,
                stride: GLsizei,
               pointer: ptr GLvoid

glTexEnvf proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                 param: GLfloat

glTexEnvfv proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                params: ptr GLfloat

glTexEnvi proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                 param: GLint

glTexEnviv proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                params: ptr GLint

glTexGend proto WINAPI \
                 coord: GLenum,
                 pname: GLenum,
                 param: GLdouble

glTexGendv proto WINAPI \
                 coord: GLenum,
                 pname: GLenum,
                params: ptr GLdouble

glTexGenf proto WINAPI \
                 coord: GLenum,
                 pname: GLenum,
                 param: GLfloat

glTexGenfv proto WINAPI \
                 coord: GLenum,
                 pname: GLenum,
                params: ptr GLfloat

glTexGeni proto WINAPI \
                 coord: GLenum,
                 pname: GLenum,
                 param: GLint

glTexGeniv proto WINAPI \
                 coord: GLenum,
                 pname: GLenum,
                params: ptr GLint

glTexImage1D proto WINAPI \
                target: GLenum,
                 level: GLint,
        internalformat: GLint,
                _width: GLsizei,
                border: GLint,
                format: GLenum,
                 _type: GLenum,
                pixels: ptr GLvoid

glTexImage2D proto WINAPI \
                target: GLenum,
                 level: GLint,
        internalformat: GLint,
                _width: GLsizei,
                height: GLsizei,
                border: GLint,
                format: GLenum,
                 _type: GLenum,
                pixels: ptr GLvoid

glTexParameterf proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                 param: GLfloat

glTexParameterfv proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                params: ptr GLfloat

glTexParameteri proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                 param: GLint

glTexParameteriv proto WINAPI \
                target: GLenum,
                 pname: GLenum,
                params: ptr GLint

glTexSubImage1D proto WINAPI \
                target: GLenum,
                 level: GLint,
               xoffset: GLint,
                _width: GLsizei,
                format: GLenum,
                 _type: GLenum,
                pixels: ptr GLvoid

glTexSubImage2D proto WINAPI \
                target: GLenum,
                 level: GLint,
               xoffset: GLint,
               yoffset: GLint,
                _width: GLsizei,
                height: GLsizei,
                format: GLenum,
                 _type: GLenum,
                pixels: ptr GLvoid

glTranslated proto WINAPI \
                     x: GLdouble,
                     y: GLdouble,
                     z: GLdouble

glTranslatef proto WINAPI \
                     x: GLfloat,
                     y: GLfloat,
                     z: GLfloat

glVertex2d proto WINAPI \
                     x: GLdouble,
                     y: GLdouble

glVertex2dv proto WINAPI \
                     v: ptr GLdouble

glVertex2f proto WINAPI \
                     x: GLfloat,
                     y: GLfloat

glVertex2fv proto WINAPI \
                     v: ptr GLfloat

glVertex2i proto WINAPI \
                     x: GLint,
                     y: GLint

glVertex2iv proto WINAPI \
                     v: ptr GLint

glVertex2s proto WINAPI \
                     x: GLshort,
                     y: GLshort

glVertex2sv proto WINAPI \
                     v: ptr GLshort

glVertex3d proto WINAPI \
                     x: GLdouble,
                     y: GLdouble,
                     z: GLdouble

glVertex3dv proto WINAPI \
                     v: ptr GLdouble

glVertex3f proto WINAPI \
                     x: GLfloat,
                     y: GLfloat,
                     z: GLfloat

glVertex3fv proto WINAPI \
                     v: ptr GLfloat

glVertex3i proto WINAPI \
                     x: GLint,
                     y: GLint,
                     z: GLint

glVertex3iv proto WINAPI \
                     v: ptr GLint

glVertex3s proto WINAPI \
                     x: GLshort,
                     y: GLshort,
                     z: GLshort

glVertex3sv proto WINAPI \
                     v: ptr GLshort

glVertex4d proto WINAPI \
                     x: GLdouble,
                     y: GLdouble,
                     z: GLdouble,
                     w: GLdouble

glVertex4dv proto WINAPI \
                     v: ptr GLdouble

glVertex4f proto WINAPI \
                     x: GLfloat,
                     y: GLfloat,
                     z: GLfloat,
                     w: GLfloat

glVertex4fv proto WINAPI \
                     v: ptr GLfloat

glVertex4i proto WINAPI \
                     x: GLint,
                     y: GLint,
                     z: GLint,
                     w: GLint

glVertex4iv proto WINAPI \
                     v: ptr GLint

glVertex4s proto WINAPI \
                     x: GLshort,
                     y: GLshort,
                     z: GLshort,
                     w: GLshort

glVertex4sv proto WINAPI \
                     v: ptr GLshort

glVertexPointer proto WINAPI \
                 _size: GLint,
                 _type: GLenum,
                stride: GLsizei,
               pointer: ptr GLvoid

glViewport proto WINAPI \
                     x: GLint,
                     y: GLint,
                _width: GLsizei,
                height: GLsizei



CALLBACK(PFNGLARRAYELEMENTEXTPROC, :GLint)
CALLBACK(PFNGLDRAWARRAYSEXTPROC, :GLenum, :GLint, :GLsizei)
CALLBACK(PFNGLVERTEXPOINTEREXTPROC, :GLint, :GLenum, :GLsizei, :GLsizei, :ptr GLvoid)
CALLBACK(PFNGLNORMALPOINTEREXTPROC, :GLenum, :GLsizei, :GLsizei, :ptr GLvoid)
CALLBACK(PFNGLCOLORPOINTEREXTPROC, :GLint, :GLenum, :GLsizei, :GLsizei, :ptr GLvoid)
CALLBACK(PFNGLINDEXPOINTEREXTPROC, :GLenum, :GLsizei, :GLsizei, :ptr GLvoid)
CALLBACK(PFNGLTEXCOORDPOINTEREXTPROC, :GLint, :GLenum, :GLsizei, :GLsizei, :ptr GLvoid)
CALLBACK(PFNGLEDGEFLAGPOINTEREXTPROC, :GLsizei, :GLsizei, :ptr GLboolean)
CALLBACK(PFNGLGETPOINTERVEXTPROC, :GLenum, :ptr GLvoid)
CALLBACK(PFNGLARRAYELEMENTARRAYEXTPROC, :GLenum, :GLsizei, :ptr GLvoid)

CALLBACK(PFNGLDRAWRANGEELEMENTSWINPROC, :GLenum, :GLuint, :GLuint, :GLsizei, :GLenum, :ptr GLvoid)

CALLBACK(PFNGLADDSWAPHINTRECTWINPROC, :GLint, :GLint, :GLsizei, :GLsizei)

CALLBACK(PFNGLCOLORTABLEEXTPROC, :GLenum, :GLenum, :GLsizei, :GLenum, :GLenum, :ptr GLvoid)
CALLBACK(PFNGLCOLORSUBTABLEEXTPROC, :GLenum, :GLsizei, :GLsizei, :GLenum, :GLenum, :ptr GLvoid)
CALLBACK(PFNGLGETCOLORTABLEEXTPROC, :GLenum, :GLenum, :GLenum, :ptr GLvoid)
CALLBACK(PFNGLGETCOLORTABLEPARAMETERIVEXTPROC, :GLenum, :GLenum, :ptr GLint)
CALLBACK(PFNGLGETCOLORTABLEPARAMETERFVEXTPROC, :GLenum, :GLenum, :ptr GLfloat)

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; __GL_H__
endif ;; __gl_h_
