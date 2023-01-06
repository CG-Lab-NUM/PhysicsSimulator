#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out float fragLightIntensity;

const vec3 DIRECTION_TO_LIGHT = normalize(vec3(1.0, -3.0, -1.0));

void main() {
    gl_Position = ubo.proj * ubo.view * push.modelMatrix * vec4(inPosition, 1.0);

    vec3 normalWorldSpace = normalize(mat3(ubo.model) * inNormal);
    float lightIntensity = dot(normalWorldSpace, DIRECTION_TO_LIGHT);

    fragColor = inColor * lightIntensity;
    fragTexCoord = inTexCoord * lightIntensity;
    fragLightIntensity = lightIntensity;
}