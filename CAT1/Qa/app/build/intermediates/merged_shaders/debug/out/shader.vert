#version 450

// Colour passed to the fragment shader
layout(location = 0) out vec3 fragColor;

// Uniform buffer containing an MVP matrix.
// Currently the vulkan backend only sets the rotation matix
// required to handle device rotation.
layout(binding = 0) uniform UniformBufferObject {
    mat4 MVP;
} ubo;

vec2 positions[6] = vec2[](
    vec2(0.5, -0.5),  // bottom right
    vec2(0.5, 0.5),   // top right
    vec2(-0.5, 0.5),  // top left

    vec2(0.5, -0.5),  // bottom right
    vec2(-0.5, 0.5),  // top left
    vec2(-0.5, -0.5)  // bottom left
);

void main() {
    gl_Position = ubo.MVP * vec4(positions[gl_VertexIndex], 0.0, 1.0);
    fragColor = vec3(1.0, 1.0, 0.0); // Yellow color
}
