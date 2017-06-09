#version 130

uniform mat4 mvp;

uniform int time;

in vec3 position;
in vec3 color;
in float angle;
in float index;

out vec3 fColor;
out float ftime;

//! [0]
void main()
{
    float t = (( ( time + int(4000*index) )%4001)/4000.);
    float tx = t*10.;
    float ty =   (2.*t- 4.*t*t)*10.;
    mat4 rot = mat4(cos(angle), 0., -sin(angle), 0.,
                    0.,         1., 0.,          0.,
                    sin(angle), 0., cos(angle),  0.,
                    0.,         0., 0.,          1.);

    mat4 transl = mat4(1., 0., 0., 0.,
                       0., 1., 0., 0.,
                       0., 0., 1., 0.,
                       tx, ty, 0., 1.);

    // Calculate vertex position in screen space
    gl_Position = mvp * rot * transl * vec4( position, 1.0 );

    fColor = color;
    ftime = t;
}
