#version 450
#extension GL_KHR_vulkan_glsl: enable
layout(set = 1, binding = 0) uniform sampler2D texSampler;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in float fragTextured;

layout(location = 0) out vec4 outColor;


void main() {
    //if(fragTextured == 0) {
    //    vec3 texColor = texture(texSampler, fragTexCoord).rgb;
    //    vec3 tempColor = fragColor.rgb;
    //    outColor = vec4(tempColor * texColor, fragColor.a);
    //} else {
        outColor = fragColor;
    //}
}