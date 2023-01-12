#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 transform;
    vec4 ambientLightColor;
    vec3 lightPosition;
    vec4 lightColor;
} ubo;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    vec3 norm = vec3(normalize(push.normalMatrix * vec4(inNormal, 0)));
    vec3 lightDir = normalize(ubo.lightPosition - vec3(push.modelMatrix * vec4(inPosition, 0)));
    float diff = max(dot(norm, lightDir), 0);
    fragColor = (diff * ubo.lightColor) + vec4(inColor, 0);
    fragTexCoord = inTexCoord;

     gl_Position = ubo.transform * vec4(inPosition, 1.0);
}
