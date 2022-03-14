// Author:
// Title:

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution;
	
    vec2 toCenter = vec2(0.5) - st;
    float angle = atan(toCenter.x, toCenter.y);
    float radius = length(toCenter) * 2.;
    
	vec3 color = hsb2rgb(vec3(angle/(2.*3.14) + 0.5 , radius, 1.));
	color *= step(0.5, 1. - length(toCenter));
    
    gl_FragColor = vec4(color, 1.0);

}