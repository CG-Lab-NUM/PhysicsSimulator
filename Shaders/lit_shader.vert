#version 450

struct PointLight {
    vec4 position;
    vec4 color;
};

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 transform;
    vec4 ambientLightColor;
    PointLight pointLights[10];
    int numLights;
} ubo;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
    mat4 lightMatrix;
} push;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    if(inColor.w > -1) {
        vec3 norm = normalize(mat3(push.modelMatrix) * inNormal);
        vec3 totalLights = vec3(0);
        for(int i = 0; i < ubo.numLights; i++) {
            PointLight light = ubo.pointLights[i];
            if(light.position.w > 0) {
                float diff = max(dot(norm, -light.position.xyz), 0.1);
                totalLights += diff * light.color.xyz * light.color.w;
            } else {
                vec3 lightDir = normalize(light.position.xyz - vec3(push.modelMatrix * vec4(inPosition, 1)));
                float diff = max(dot(norm, lightDir), 0.1);
                totalLights += diff * light.color.xyz * light.color.w;
            }
        }
        fragColor = vec4(totalLights * inColor.xyz, inColor.w);
    } else {
        fragColor = vec4(inColor.rgb, 1);
    }
    fragTexCoord = inTexCoord;
    gl_Position = ubo.transform * vec4(inPosition, 1.0);
}
