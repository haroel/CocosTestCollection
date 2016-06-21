/**
 Twist shader  created by howe
 **/
#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

varying float v_start;
varying float v_end;

uniform sampler2D u_textureTo;   //

void main()
{
    float yfrac = v_texCoord.y;
    
    if (yfrac < v_start)
    {
        gl_FragColor = v_fragmentColor * texture2D(u_textureTo,v_texCoord);
    }
    else if (yfrac > v_end)
    {
        gl_FragColor = v_fragmentColor * texture2D(CC_Texture0,v_texCoord);;
    }
    else
    {
        float angle = (yfrac - v_start) / (v_end - v_start);
        float _width = cos(angle * 3.1416);
        
        if (_width > 0.0)
        {
            float startx = (1.0 - _width) / 2.0;
            float sampleWidth = _width;
            if (v_texCoord.x < startx)
            {
                gl_FragColor = vec4(0,0,0,0);
                
            }else if ( v_texCoord.x < (startx + sampleWidth) )
            {
                float perc = (v_texCoord.x - startx) / sampleWidth;
                gl_FragColor = v_fragmentColor * texture2D(u_textureTo,vec2( perc ,v_texCoord.y));;
            }
            else
            {
                gl_FragColor = vec4(0,0,0,0);
            }
            
        }
        else if (_width < 0.0)
        {
            float startx = (1.0 + _width) / 2.0;
            float sampleWidth = -_width;
            
            if (v_texCoord.x < startx)
            {
                gl_FragColor = v_fragmentColor *vec4(0,0,0,0);
            }
            else if ( v_texCoord.x < (startx + sampleWidth) )
            {
                float perc = (v_texCoord.x - startx) / sampleWidth;
                
                gl_FragColor = v_fragmentColor * texture2D(CC_Texture0,vec2(perc ,v_texCoord.y));;
            }
            else
            {
                gl_FragColor = vec4(0,0,0,0);
            }
        }
    }
}
