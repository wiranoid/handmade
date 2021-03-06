layout(location = 0) in vec3 in_Position;

out VS_OUT
{
    vec3 NearPlanePosition;
    vec3 FarPlanePosition;
    vec3 VertexPosition;
} vs_out;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
    vs_out.NearPlanePosition = UnprojectPoint(vec3(in_Position.xy, -1.f), u_View, u_Projection);
    vs_out.FarPlanePosition = UnprojectPoint(vec3(in_Position.xy, 1.f), u_View, u_Projection);
    vs_out.VertexPosition = in_Position;

    gl_Position = vec4(in_Position, 1.f);
}