#version 130

in float ftime;
//in vec3 fColor;
uniform sampler2D tex0;

out vec4 fragColor;

void main()
{
    //fragColor = vec4( fColor, 1.-ftime );
    fragColor = texture2D(tex0, gl_PointCoord);
}
