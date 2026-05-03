ifndef __glu_h__
ifndef __GLU_H__
define __glu_h__
define __GLU_H__

include winapifamily.inc
include GL/gl.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.pragma comment(lib, glu32)

ifdef _UNICODE
gluErrorStringWIN macro errCode
	exitm<(gluErrorUnicodeStringEXT(errCode))>
	endm
else
gluErrorStringWIN macro errCode
	exitm<(gluErrorString(errCode))>
	endm
endif

gluErrorString proto WINAPI :GLenum
gluErrorUnicodeStringEXT proto WINAPI :GLenum
gluGetString proto WINAPI :GLenum
gluOrtho2D proto WINAPI :GLdouble, :GLdouble, :GLdouble, :GLdouble
gluPerspective proto WINAPI :GLdouble, :GLdouble, :GLdouble, :GLdouble
gluPickMatrix proto WINAPI :GLdouble, :GLdouble, :GLdouble, :GLdouble, :ptr
gluLookAt proto WINAPI :GLdouble, :GLdouble, :GLdouble, :GLdouble, :GLdouble, :GLdouble, :GLdouble, :GLdouble, :GLdouble
gluProject proto WINAPI :GLdouble, :GLdouble, :GLdouble, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
gluUnProject proto WINAPI :GLdouble, :GLdouble, :GLdouble, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
gluScaleImage proto WINAPI :GLenum, :GLint, :GLint, :GLenum, :ptr, :GLint, :GLint, :GLenum, :ptr
gluBuild1DMipmaps proto WINAPI :GLenum, :GLint, :GLint, :GLenum, :GLenum, :ptr
gluBuild2DMipmaps proto WINAPI :GLenum, :GLint, :GLint, :GLint, :GLenum, :GLenum, :ptr
gluNewQuadric proto WINAPI
gluDeleteQuadric proto WINAPI :ptr
gluQuadricNormals proto WINAPI :ptr, :GLenum
gluQuadricTexture proto WINAPI :ptr, :GLboolean
gluQuadricOrientation proto WINAPI :ptr, :GLenum
gluQuadricDrawStyle proto WINAPI :ptr, :GLenum
gluCylinder proto WINAPI :ptr, :GLdouble, :GLdouble, :GLdouble, :GLint, :GLint
gluDisk proto WINAPI :ptr, :GLdouble, :GLdouble, :GLint, :GLint
gluPartialDisk proto WINAPI :ptr, :GLdouble, :GLdouble, :GLint, :GLint, :GLdouble, :GLdouble
gluSphere proto WINAPI :ptr, :GLdouble, :GLint, :GLint
gluQuadricCallback proto WINAPI :ptr, :GLenum, :ptr
gluNewTess proto WINAPI
gluDeleteTess proto WINAPI :ptr
gluTessBeginPolygon proto WINAPI :ptr, :ptr
gluTessBeginContour proto WINAPI :ptr
gluTessVertex proto WINAPI :ptr, :ptr, :ptr
gluTessEndContour proto WINAPI :ptr
gluTessEndPolygon proto WINAPI :ptr
gluTessProperty proto WINAPI :ptr, :GLenum, :GLdouble
gluTessNormal proto WINAPI :ptr, :GLdouble, :GLdouble, :GLdouble
gluTessCallback proto WINAPI :ptr, :GLenum, :ptr
gluGetTessProperty proto WINAPI :ptr, :GLenum, :ptr
gluNewNurbsRenderer proto WINAPI
gluDeleteNurbsRenderer proto WINAPI :ptr
gluBeginSurface proto WINAPI :ptr
gluBeginCurve proto WINAPI :ptr
gluEndCurve proto WINAPI :ptr
gluEndSurface proto WINAPI :ptr
gluBeginTrim proto WINAPI :ptr
gluEndTrim proto WINAPI :ptr
gluPwlCurve proto WINAPI :ptr, :GLint, :ptr, :GLint, :GLenum
gluNurbsCurve proto WINAPI :ptr, :GLint, :ptr, :GLint, :ptr, :GLint, :GLenum
gluNurbsSurface proto WINAPI :ptr, :GLint, :ptr, :GLint, :ptr, :GLint, :GLint, :ptr, :GLint, :GLint, :GLenum
gluLoadSamplingMatrices proto WINAPI :ptr, :ptr, :ptr, :ptr
gluNurbsProperty proto WINAPI :ptr, :GLenum, :GLfloat
gluGetNurbsProperty proto WINAPI :ptr, :GLenum, :ptr
gluNurbsCallback proto WINAPI :ptr, :GLenum, :ptr

CALLBACK(GLUquadricErrorProc, :GLenum)

CALLBACK(GLUtessBeginProc, :GLenum)
CALLBACK(GLUtessEdgeFlagProc, :GLboolean)
CALLBACK(GLUtessVertexProc, :ptr)
CALLBACK(GLUtessEndProc)
CALLBACK(GLUtessErrorProc, :GLenum)
CALLBACK(GLUtessCombineProc, :ptr GLdouble, :ptr, :ptr GLfloat, :ptr)
CALLBACK(GLUtessBeginDataProc, :GLenum, :ptr)
CALLBACK(GLUtessEdgeFlagDataProc, :GLboolean, :ptr)
CALLBACK(GLUtessVertexDataProc, :ptr, :ptr)
CALLBACK(GLUtessEndDataProc, :ptr)
CALLBACK(GLUtessErrorDataProc, :GLenum, :ptr)
CALLBACK(GLUtessCombineDataProc, :ptr GLdouble, :ptr, :ptr GLfloat, :ptr, :ptr)

CALLBACK(GLUnurbsErrorProc, :GLenum)

GLU_VERSION_1_1		equ 1
GLU_VERSION_1_2		equ 1

GLU_INVALID_ENUM	equ 100900
GLU_INVALID_VALUE	equ 100901
GLU_OUT_OF_MEMORY	equ 100902
GLU_INCOMPATIBLE_GL_VERSION equ 100903

GLU_VERSION		equ 100800
GLU_EXTENSIONS		equ 100801

GLU_TRUE		equ GL_TRUE
GLU_FALSE		equ GL_FALSE

GLU_SMOOTH		equ 100000
GLU_FLAT		equ 100001
GLU_NONE		equ 100002

GLU_POINT		equ 100010
GLU_LINE		equ 100011
GLU_FILL		equ 100012
GLU_SILHOUETTE		equ 100013

GLU_OUTSIDE		equ 100020
GLU_INSIDE		equ 100021

GLU_TESS_MAX_COORD	equ 1.0e150

GLU_TESS_WINDING_RULE	equ 100140
GLU_TESS_BOUNDARY_ONLY	equ 100141
GLU_TESS_TOLERANCE	equ 100142

GLU_TESS_WINDING_ODD	equ 100130
GLU_TESS_WINDING_NONZERO equ 100131
GLU_TESS_WINDING_POSITIVE equ 100132
GLU_TESS_WINDING_NEGATIVE equ 100133
GLU_TESS_WINDING_ABS_GEQ_TWO equ 100134

GLU_TESS_BEGIN		equ 100100
GLU_TESS_VERTEX		equ 100101
GLU_TESS_END		equ 100102
GLU_TESS_ERROR		equ 100103
GLU_TESS_EDGE_FLAG	equ 100104
GLU_TESS_COMBINE	equ 100105
GLU_TESS_BEGIN_DATA	equ 100106
GLU_TESS_VERTEX_DATA	equ 100107
GLU_TESS_END_DATA	equ 100108
GLU_TESS_ERROR_DATA	equ 100109
GLU_TESS_EDGE_FLAG_DATA equ 100110
GLU_TESS_COMBINE_DATA	equ 100111

GLU_TESS_ERROR1		equ 100151
GLU_TESS_ERROR2		equ 100152
GLU_TESS_ERROR3		equ 100153
GLU_TESS_ERROR4		equ 100154
GLU_TESS_ERROR5		equ 100155
GLU_TESS_ERROR6		equ 100156
GLU_TESS_ERROR7		equ 100157
GLU_TESS_ERROR8		equ 100158

GLU_TESS_MISSING_BEGIN_POLYGON equ GLU_TESS_ERROR1
GLU_TESS_MISSING_BEGIN_CONTOUR equ GLU_TESS_ERROR2
GLU_TESS_MISSING_END_POLYGON equ GLU_TESS_ERROR3
GLU_TESS_MISSING_END_CONTOUR equ GLU_TESS_ERROR4
GLU_TESS_COORD_TOO_LARGE equ GLU_TESS_ERROR5
GLU_TESS_NEED_COMBINE_CALLBACK equ GLU_TESS_ERROR6

GLU_AUTO_LOAD_MATRIX	equ 100200
GLU_CULLING		equ 100201
GLU_SAMPLING_TOLERANCE	equ 100203
GLU_DISPLAY_MODE	equ 100204
GLU_PARAMETRIC_TOLERANCE equ 100202
GLU_SAMPLING_METHOD	equ 100205
GLU_U_STEP		equ 100206
GLU_V_STEP		equ 100207

GLU_PATH_LENGTH		equ 100215
GLU_PARAMETRIC_ERROR	equ 100216
GLU_DOMAIN_DISTANCE	equ 100217

GLU_MAP1_TRIM_2		equ 100210
GLU_MAP1_TRIM_3		equ 100211

GLU_OUTLINE_POLYGON	equ 100240
GLU_OUTLINE_PATCH	equ 100241

GLU_NURBS_ERROR1	equ 100251
GLU_NURBS_ERROR2	equ 100252
GLU_NURBS_ERROR3	equ 100253
GLU_NURBS_ERROR4	equ 100254
GLU_NURBS_ERROR5	equ 100255
GLU_NURBS_ERROR6	equ 100256
GLU_NURBS_ERROR7	equ 100257
GLU_NURBS_ERROR8	equ 100258
GLU_NURBS_ERROR9	equ 100259
GLU_NURBS_ERROR10	equ 100260
GLU_NURBS_ERROR11	equ 100261
GLU_NURBS_ERROR12	equ 100262
GLU_NURBS_ERROR13	equ 100263
GLU_NURBS_ERROR14	equ 100264
GLU_NURBS_ERROR15	equ 100265
GLU_NURBS_ERROR16	equ 100266
GLU_NURBS_ERROR17	equ 100267
GLU_NURBS_ERROR18	equ 100268
GLU_NURBS_ERROR19	equ 100269
GLU_NURBS_ERROR20	equ 100270
GLU_NURBS_ERROR21	equ 100271
GLU_NURBS_ERROR22	equ 100272
GLU_NURBS_ERROR23	equ 100273
GLU_NURBS_ERROR24	equ 100274
GLU_NURBS_ERROR25	equ 100275
GLU_NURBS_ERROR26	equ 100276
GLU_NURBS_ERROR27	equ 100277
GLU_NURBS_ERROR28	equ 100278
GLU_NURBS_ERROR29	equ 100279
GLU_NURBS_ERROR30	equ 100280
GLU_NURBS_ERROR31	equ 100281
GLU_NURBS_ERROR32	equ 100282
GLU_NURBS_ERROR33	equ 100283
GLU_NURBS_ERROR34	equ 100284
GLU_NURBS_ERROR35	equ 100285
GLU_NURBS_ERROR36	equ 100286
GLU_NURBS_ERROR37	equ 100287

gluBeginPolygon proto WINAPI :ptr
gluNextContour proto WINAPI :ptr, :GLenum
gluEndPolygon proto WINAPI :ptr

GLU_CW			equ 100120
GLU_CCW			equ 100121
GLU_INTERIOR		equ 100122
GLU_EXTERIOR		equ 100123
GLU_UNKNOWN		equ 100124

GLU_BEGIN		equ GLU_TESS_BEGIN
GLU_VERTEX		equ GLU_TESS_VERTEX
GLU_END			equ GLU_TESS_END
GLU_ERROR		equ GLU_TESS_ERROR
GLU_EDGE_FLAG		equ GLU_TESS_EDGE_FLAG

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; __GLU_H__
endif ;; __glu_h__
