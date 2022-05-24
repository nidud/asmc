ifndef __GRAPHENE_GOBJECT_H__
define __GRAPHENE_GOBJECT_H__

include glib-object.inc
include graphene/graphene.inc

define GRAPHENE_TYPE_POINT             <graphene_point_get_type ()>

graphene_point_get_type proto

define GRAPHENE_TYPE_POINT3D           <graphene_point3d_get_type ()>

graphene_point3d_get_type proto

define GRAPHENE_TYPE_SIZE              <graphene_size_get_type ()>

graphene_size_get_type proto

define GRAPHENE_TYPE_RECT              <graphene_rect_get_type ()>

graphene_rect_get_type proto

define GRAPHENE_TYPE_VEC2              <graphene_vec2_get_type ()>

graphene_vec2_get_type proto

define GRAPHENE_TYPE_VEC3              <graphene_vec3_get_type ()>

graphene_vec3_get_type proto

define GRAPHENE_TYPE_VEC4              <graphene_vec4_get_type ()>

graphene_vec4_get_type proto

define GRAPHENE_TYPE_QUAD              <graphene_quad_get_type ()>

graphene_quad_get_type proto

define GRAPHENE_TYPE_QUATERNION        <graphene_quaternion_get_type ()>

graphene_quaternion_get_type proto

define GRAPHENE_TYPE_MATRIX            <graphene_matrix_get_type ()>

graphene_matrix_get_type proto

define GRAPHENE_TYPE_PLANE             <graphene_plane_get_type ()>

graphene_plane_get_type proto

define GRAPHENE_TYPE_FRUSTUM           <graphene_frustum_get_type ()>

graphene_frustum_get_type proto

define GRAPHENE_TYPE_SPHERE            <graphene_sphere_get_type ()>

graphene_sphere_get_type proto

define GRAPHENE_TYPE_BOX               <graphene_box_get_type ()>

graphene_box_get_type proto

define GRAPHENE_TYPE_TRIANGLE          <graphene_triangle_get_type ()>

graphene_triangle_get_type proto

define GRAPHENE_TYPE_EULER             <graphene_euler_get_type ()>

graphene_euler_get_type proto

define GRAPHENE_TYPE_RAY               <graphene_ray_get_type ()>

graphene_ray_get_type proto

endif

