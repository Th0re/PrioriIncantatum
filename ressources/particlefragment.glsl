#version 130

//in float ftime;
in vec4 fColor;
uniform sampler2D tex0;

out vec4 fragColor;

void main()
{
    fragColor = texture2D(tex0, gl_PointCoord)*vec4(1.,1.,1.,fColor.w)*fColor;
}
