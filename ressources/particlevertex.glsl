#version 130

uniform mat4 mvp;

uniform int time;

uniform vec3 position;
in vec3 baseSpeed;
in float index;
in float weight;
in float lifespan;

out float ftime;

//! [0]
void main()
{
    float t = (( ( time + int(lifespan*index) )%(int(lifespan+1)))/lifespan);

    vec3 speed = (baseSpeed - vec3(.0, 9.81*weight*t, .0))*t;

    // Calculate vertex position in screen space
    gl_Position = mvp * vec4(position + speed, 1.0 );

    ftime = t;
}
