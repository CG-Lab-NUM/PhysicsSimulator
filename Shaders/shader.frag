#version 450
#extension GL_KHR_vulkan_glsl: enable
layout(set = 1, binding = 0) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragLightDirection;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 texColor = texture(texSampler, fragTexCoord).rgb;
    outColor = vec4(fragColor * texColor, 1.0);
    //outColor = texture(texSampler, fragTexCoord);
}