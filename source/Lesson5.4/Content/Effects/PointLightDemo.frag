#version 440 core

layout (binding = 0) uniform sampler2D ColorTextureSampler;
uniform vec4 AmbientColor;
uniform vec4 LightColor;
uniform vec3 LightPosition;
uniform vec3 CameraPosition;
uniform vec4 SpecularColor;
uniform float SpecularPower;

in VS_OUTPUT
{
	vec2 TextureCoordinate;
	vec3 Normal;
	vec3 WorldPosition;
	float Attenuation;
} IN;

out vec4 Color;

void main()
{	
	vec3 lightDirection = normalize(LightPosition - IN.WorldPosition);
	vec3 viewDirection = normalize(CameraPosition - IN.WorldPosition);

	vec3 normal = normalize(IN.Normal);
	float n_dot_l = dot(normal, lightDirection);
	vec3 halfVector = normalize(lightDirection + viewDirection);
	float n_dot_h = dot(normal, halfVector);

	vec4 sampledColor = texture(ColorTextureSampler, IN.TextureCoordinate);
	vec3 ambient = AmbientColor.rgb * sampledColor.rgb;
	vec3 diffuse = clamp(LightColor.rgb * n_dot_l * sampledColor.rgb, 0.0f, 1.0f) * IN.Attenuation;
	
	// specular = N.H^n with gloss map stored in color texture's alpha channel
	vec3 specular = SpecularColor.rgb * min(pow(clamp(n_dot_h, 0.0f, 1.0f), SpecularPower), sampledColor.w) * IN.Attenuation;

	Color.rgb = ambient + diffuse + specular;
	Color.a = sampledColor.a;
}