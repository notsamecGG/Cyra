// Author:
// Title:

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float line(float val, float center, float edge)
{
    return step(center - edge, val) - step(center + edge, val);
}

float rect(vec2 st, vec2 center, vec2 size)
{
    vec2 result = step(center - size, st) - step(center + size, st);

    return result.x * result.y;
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution;
	
    float width = 0.01;
    
    float lineH = line(st.y, 0.804, width);
    lineH += line(st.y, 0.180, width);
    lineH += line(st.y, 0.600, width);

    float lineV = line(st.x, 0.188, width);    
    lineV += line(st.x, 0.380, width);    
    lineV += line(st.x, 0.836, width);

    float blankRect = rect(st, vec2(0.), vec2(0.370,0.590));
	float redRect = rect(st, vec2(-0.010,0.980), vec2(0.380,0.550));	
    float yelRect = rect(st, vec2(1.,1.), vec2(0.170,0.400));
    float bluRect = rect(st, vec2(1.,0.), vec2(0.690,0.180));

    vec3 color = vec3(1.);
    color -= redRect * (1. - vec3(1., 0., 0.));
    color -= yelRect * (1. - vec3(1., 1., 0.));
    color -= bluRect * (1. - vec3(0., 0., 1.));
    
    // lines
    color -= lineH;
    color -= lineV;
    
    color = vec3(clamp(color, 0.0, 1.0));
    
    // rects
    color += blankRect;

    gl_FragColor = vec4(color, 1.0);

}