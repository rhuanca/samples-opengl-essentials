#version 440 core

layout (binding = 0) uniform sampler2D ColorTextureSampler;
uniform vec4 AmbientColor;
uniform vec4 LightColor;

in VS_OUTPUT
{
	vec2 TextureCoordinate;
	vec3 Normal;
	vec3 LightDirection;
} IN;

out vec4 Color;

void main()
{
	vec3 normal = normalize(IN.Normal);
    vec3 lightDirection = normalize(IN.LightDirection);
	float n_dot_l = dot(lightDirection, normal);

	vec4 sampledColor = texture(ColorTextureSampler, IN.TextureCoordinate);
	vec3 ambient = AmbientColor.rgb * sampledColor.rgb;
	vec3 diffuse = clamp(LightColor.rgb * n_dot_l * sampledColor.rgb, 0.0f, 1.0f);	

	Color.rgb = ambient + diffuse;
	Color.a = sampledColor.a;
}