/**
  Twist shader  created by howe
**/
//precision lowp float;
#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

#define PI 3.14159265


uniform float u_progress;        // 0~1
uniform float u_start;

float _atan2(float y,float x)
{
    if (x > 0.0)
    {
        if (y >= 0.0)
        {
            return atan(y/x);
        }else if (y < 0.0)
        {
            return PI * 2.0 - atan( abs(y)/x);
        }
    }else if (x == 0.0)
    {
        
        if (y >= 0.0)
        {
            return PI / 2.0;
        }else if (y < 0.0)
        {
            return PI * 1.5;
        }
    }else
    {
        
        if (y >= 0.0)
        {
            return PI - atan(y/abs(x));
        }else if (y < 0.0)
        {
            return PI + atan( y/x);
        }
    }
    return 0.0;
}

void main()
{
    
    // u_start = 0.2, u_progress = 0.88
    // 0.08
    if (u_progress > 0.99)
    {
        gl_FragColor = v_fragmentColor * texture2D(CC_Texture0,v_texCoord);
        return;
    }
    
    vec2 pp;
    pp.x = v_texCoord.x - 0.5;
    pp.y = v_texCoord.y - 0.5;
    
//    float alpha = 3.1415926 - acos( pp.x/sqrt( pp.x * pp.x + pp.y *pp.y));
    float alpha =2.0 * PI - _atan2( pp.y, pp.x);
    float radius =alpha/(2.0 * PI);
    
    float a = radius - u_start;
    if ( a>= 0.0 && a <= u_progress)
    {
        gl_FragColor = v_fragmentColor * texture2D(CC_Texture0,v_texCoord);
    }else
    {
        float du = u_progress + u_start - 1.0;
        if (radius <= du)
        {
            gl_FragColor = v_fragmentColor * texture2D(CC_Texture0,v_texCoord);
        }else
        {
            discard;
        }
    }
    
}
