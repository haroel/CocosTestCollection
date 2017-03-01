/**
  Twist shader  created by howe
**/
//precision lowp float;
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

varying float v_start;
varying float v_end;

//uniform float u_progress;        // 0~1
uniform mat4 u_rotation;

void main()
{
    gl_Position =  CC_PMatrix * u_rotation * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
//    
//    float _height = 2.0;
//    float scale = 1.0 + _height;
//    
//    v_start = u_progress * scale - _height;
//    v_end   = v_start + _height;
}
