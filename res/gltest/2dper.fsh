/**
  Twist shader  created by howe
**/
//precision lowp float;
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

vec4 AntiAliasPointSampleTexture_Linear(vec2 uv, vec2 texsize)
{
    vec2 w=fwidth(uv);
    return texture2D(CC_Texture0, (floor(uv)+0.5+clamp((fract(uv)-0.5+w)/w,0.,1.)) / texsize, -99999.0);
}

void main()
{
    gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
//    gl_FragColor = v_fragmentColor * AntiAliasPointSampleTexture_Linear( v_texCoord,vec2(195.0/900.0,270.0/640.0));
}
