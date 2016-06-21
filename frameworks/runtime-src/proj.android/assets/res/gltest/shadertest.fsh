/**
  Twist shader  created by howe
**/
precision lowp float;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
    vec4 color = texture2D(CC_Texture0,v_texCoord);
    color.a = 0.01;
    gl_FragColor = color;
//    gl_FragColor.a = 0.1;
    //vec4 color = v_fragmentColor;
//    color.a = 0.0;
    //gl_FragColor = vec4(0.0,1.0,1.0,0.1);

//    gl_FragColor = color;
}
