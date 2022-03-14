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

float circle(vec2 st, vec2 center, float radius)
{
    return 1. - step(radius, distance(st, center));
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution;
	
    float circ1 = circle(st, vec2(0.380,0.620), 0.356);
    float circ2 = circle(st, vec2(0.800,0.180), 0.124);
    
	vec3 color = circ1 * vec3(1., 0., 1.) + circ2 * vec3(0., 1., 0.);

    gl_FragColor = vec4(color, 1.0);

}