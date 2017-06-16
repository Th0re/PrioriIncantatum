#version 130

uniform mat4 mvp;

in vec3 pos;

out float ftime;

//! [0]
void main()
{
    //float t = (( ( time + int(lifespan*index) )%(int(lifespan)))/lifespan);

    //vec3 speed = (baseSpeed - vec3(.0, 9.81*weight*t, .0))*t;

    // Calculate vertex position in screen space
    gl_Position = mvp * vec4(pos, 1.0 );


}
