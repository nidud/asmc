ifndef __glu_h__
ifndef __GLU_H__
__glu_h__ equ <>
__GLU_H__ equ <>

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

;void
gluOrtho2D proto WINAPI \
		  left: GLdouble,
		 right: GLdouble,
		bottom: GLdouble,
		   top: GLdouble


;void
gluPerspective proto WINAPI \
		  fovy: GLdouble,
		aspect: GLdouble,
		 zNear: GLdouble,
		  zFar: GLdouble


;void
gluPickMatrix proto WINAPI \
		     x: GLdouble,
		     y: GLdouble,
		 width: GLdouble,
		height: GLdouble,
	      viewport: ptr GLint


;void
gluLookAt proto WINAPI \
		  eyex: GLdouble,
		  eyey: GLdouble,
		  eyez: GLdouble,
	       centerx: GLdouble,
	       centery: GLdouble,
	       centerz: GLdouble,
		   upx: GLdouble,
		   upy: GLdouble,
		   upz: GLdouble


;int
gluProject proto WINAPI \
		  objx: GLdouble,
		  objy: GLdouble,
		  objz: GLdouble,
	   modelMatrix: ptr GLdouble,
	    projMatrix: ptr GLdouble,
	      viewport: ptr GLint,
		  winx: ptr GLdouble,
		  winy: ptr GLdouble,
		  winz: ptr GLdouble

gluUnProject proto WINAPI \
		  winx: GLdouble,
		  winy: GLdouble,
		  winz: GLdouble,
	   modelMatrix: ptr GLdouble,
	    projMatrix: ptr GLdouble,
	      viewport: ptr GLint,
		  objx: ptr GLdouble,
		  objy: ptr GLdouble,
		  objz: ptr GLdouble

gluScaleImage proto WINAPI \
		format: GLenum,
	       widthin: GLint,
	      heightin: GLint,
		typein: GLenum,
		datain: ptr void,
	      widthout: GLint,
	     heightout: GLint,
	       typeout: GLenum,
	       dataout: ptr

gluBuild1DMipmaps proto WINAPI \
		target: GLenum,
	    components: GLint,
		 width: GLint,
		format: GLenum,
		  type: GLenum,
		 _data: ptr

gluBuild2DMipmaps proto WINAPI \
		target: GLenum,
	    components: GLint,
		 width: GLint,
		height: GLint,
		format: GLenum,
		  type: GLenum,
		 _data: ptr

;GLUnurbs		typedef GLUnurbs
;GLUquadric		typedef GLUquadric
;GLUtesselator		typedef GLUtesselator

;GLUnurbsObj		typedef GLUnurbs
;GLUquadricObj		typedef GLUquadric
;GLUtesselatorObj	typedef GLUtesselator
;GLUtriangulatorObj	typedef GLUtesselator


gluNewQuadric proto WINAPI
;void
gluDeleteQuadric proto WINAPI \
		 state: ptr GLUquadric

gluQuadricNormals proto WINAPI \
	    quadObject: ptr GLUquadric,
	       normals: GLenum

gluQuadricTexture proto WINAPI \
	    quadObject: ptr GLUquadric,
	 textureCoords: GLboolean

gluQuadricOrientation proto WINAPI \
	    quadObject: ptr GLUquadric,
	   orientation: GLenum

gluQuadricDrawStyle proto WINAPI \
	    quadObject: ptr GLUquadric,
	     drawStyle: GLenum

gluCylinder proto WINAPI \
		  qobj: ptr GLUquadric,
	    baseRadius: GLdouble,
	     topRadius: GLdouble,
		height: GLdouble,
		slices: GLint,
		stacks: GLint

gluDisk proto WINAPI \
		  qobj: ptr GLUquadric,
	   innerRadius: GLdouble,
	   outerRadius: GLdouble,
		slices: GLint,
		 loops: GLint

gluPartialDisk proto WINAPI \
		  qobj: ptr GLUquadric,
	   innerRadius: GLdouble,
	   outerRadius: GLdouble,
		slices: GLint,
		 loops: GLint,
	    startAngle: GLdouble,
	    sweepAngle: GLdouble

gluSphere proto WINAPI \
		  qobj: ptr GLUquadric,
		radius: GLdouble,
		slices: GLint,
		stacks: GLint

gluQuadricCallback proto WINAPI \
		  qobj: ptr GLUquadric,
		 which: GLenum,
		    fn: ptr

gluNewTess proto WINAPI

gluDeleteTess proto WINAPI \
		  tess: ptr GLUtesselator


gluTessBeginPolygon proto WINAPI \
		  tess: ptr GLUtesselator,
	  polygon_data: ptr

gluTessBeginContour proto WINAPI \
		  tess: ptr GLUtesselator

gluTessVertex proto WINAPI \
		  tess: ptr GLUtesselator,
		coords: ptr GLdouble,
		 _data: ptr

gluTessEndContour proto WINAPI \
		  tess: ptr GLUtesselator

gluTessEndPolygon proto WINAPI \
		  tess: ptr GLUtesselator

gluTessProperty proto WINAPI \
		  tess: ptr GLUtesselator,
		 which: GLenum,
		 value: GLdouble

gluTessNormal proto WINAPI \
		  tess: ptr GLUtesselator,
		     x: GLdouble,
		     y: GLdouble,
		     z: GLdouble

gluTessCallback proto WINAPI \
		  tess: ptr GLUtesselator,
		 which: GLenum,
		      : ptr

gluGetTessProperty proto WINAPI \
		  tess: ptr GLUtesselator,
		 which: GLenum,
		 value: ptr GLdouble

gluNewNurbsRenderer proto WINAPI

gluDeleteNurbsRenderer proto WINAPI \
		  nobj: ptr GLUnurbs

gluBeginSurface proto WINAPI \
		  nobj: ptr GLUnurbs

gluBeginCurve proto WINAPI \
		  nobj: ptr GLUnurbs

gluEndCurve proto WINAPI \
		  nobj: ptr GLUnurbs

gluEndSurface proto WINAPI \
		  nobj: ptr GLUnurbs

gluBeginTrim proto WINAPI \
		  nobj: ptr GLUnurbs

gluEndTrim proto WINAPI \
		  nobj: ptr GLUnurbs

gluPwlCurve proto WINAPI \
		  nobj: ptr GLUnurbs,
		 count: GLint,
		 array: ptr GLfloat,
		stride: GLint,
		  type: GLenum

gluNurbsCurve proto WINAPI \
		  nobj: ptr GLUnurbs,
		nknots: GLint,
		  knot: ptr GLfloat,
		stride: GLint,
	      ctlarray: ptr GLfloat,
		 order: GLint,
		  type: GLenum

gluNurbsSurface proto WINAPI \
		  nobj: ptr GLUnurbs,
	   sknot_count: GLint,
		 sknot: ptr float,
	   tknot_count: GLint,
		 tknot: ptr GLfloat,
	      s_stride: GLint,
	      t_stride: GLint,
	      ctlarray: ptr GLfloat,
		sorder: GLint,
		torder: GLint,
		  type: GLenum

gluLoadSamplingMatrices proto WINAPI \
		  nobj: ptr GLUnurbs,
	   modelMatrix: ptr GLfloat,
	    projMatrix: ptr GLfloat,
	      viewport: ptr GLint

gluNurbsProperty proto WINAPI \
		  nobj: ptr GLUnurbs,
	      property: GLenum,
		 value: GLfloat

gluGetNurbsProperty proto WINAPI \
		  nobj: ptr GLUnurbs,
	      property: GLenum,
		 value: ptr GLfloat

gluNurbsCallback proto WINAPI \
		  nobj: ptr GLUnurbs,
		 which: GLenum,
		      : ptr


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

;void
gluBeginPolygon proto WINAPI \
		  tess: ptr GLUtesselator


gluNextContour proto WINAPI \
		  tess: ptr GLUtesselator,
		  type: GLenum

gluEndPolygon proto WINAPI \
		  tess: ptr GLUtesselator


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
