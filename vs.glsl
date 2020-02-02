// This is Vertex Shader

#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 transform; 
uniform mat4 projectionTransform;

void main()
{
	FragPos = vec3(transform * vec4(vPos, 1.0));
	gl_Position =   projectionTransform * transform * vec4(vPos, 1.0);

	Normal = normalize(mat3(transpose(inverse(transform))) * vNormal);
}
