#version 450 // Version declaration specifying the GLSL version used

// Define an output variable for the fragment shader to pass color data to the next stage
layout(location = 0) out vec3 fragColor;

// Define a uniform buffer object (UBO) to store the MVP (Model-View-Projection) matrix
layout(binding = 0) uniform UniformBufferObject {
    mat4 MVP; // MVP matrix
} ubo;

// Define an array of 2D positions for vertices of a rectangle
vec2 positions[6] = vec2[](
    vec2(0.5, -0.5),  // Bottom right
    vec2(0.5, 0.5),   // Top right
    vec2(-0.5, 0.5),  // Top left
    vec2(0.5, -0.5),  // Bottom right (repeated to close the shape)
    vec2(-0.5, 0.5),  // Top left (repeated to close the shape)
    vec2(-0.5, -0.5)  // Bottom left
);

void main() {
    // Transform the vertex position using the MVP matrix and set gl_Position
    gl_Position = ubo.MVP * vec4(positions[gl_VertexIndex], 0.0, 1.0);

    // Set the fragment color to yellow
    fragColor = vec3(1.0, 1.0, 0.0); // Yellow color
}
