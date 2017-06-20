#version 130


in vec3 pos;
in vec4 color;
in float pointSize;

out float ftime;
out vec4 fColor;
//! [0]
void main()
{
    //float t = (( ( time + int(lifespan*index) )%(int(lifespan)))/lifespan);

    //vec3 speed = (baseSpeed - vec3(.0, 9.81*weight*t, .0))*t;

    // Calculate vertex position in screen space
    gl_Position = vec4(pos, 1.0);
    fColor = color;
    gl_PointSize = pointSize;

}
