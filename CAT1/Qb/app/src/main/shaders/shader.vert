#version 450 // Version declaration specifying the GLSL version used

// Define an output variable for the fragment shader to pass color data to the next stage
layout(location = 0) out vec3 fragColor;

// Define a uniform buffer object (UBO) to store the MVP (Model-View-Projection) matrix
layout(binding = 0) uniform UniformBufferObject {
    mat4 MVP; // MVP matrix
} ubo;

// Define an array of 2D positions for vertices of a shape
vec2 positions[12] = vec2[](
    vec2(-0.5196, 1.0),   // Vertex A
    vec2(-0.866, 0.5),    // Vertex B
    vec2(-0.3464, -0.167),// Vertex C
    vec2(0.3464, -0.167), // Vertex D
    vec2(0.866, 0.5),     // Vertex E
    vec2(0.5196, 1.0),    // Vertex F
    vec2(-0.5196, 1.0),   // Repeat Vertex A to close the shape
    vec2(-0.3464, -0.167),// Repeat Vertex C
    vec2(0.3464, -0.167), // Repeat Vertex D
    vec2(-0.5196, 1.0),   // Repeat Vertex A
    vec2(0.3464, -0.167), // Repeat Vertex D
    vec2(0.5196, 1.0)     // Repeat Vertex F
);

// Define an array of colors corresponding to each vertex
vec3 colors[6] = vec3[](
    vec3(1.0, 0.0, 0.0), // Red (for vertices A, B, C, D, E, F)
    vec3(1.0, 0.0, 0.0),
    vec3(1.0, 0.0, 0.0),
    vec3(1.0, 0.0, 0.0),
    vec3(1.0, 0.0, 0.0),
    vec3(1.0, 0.0, 0.0)
);

void main() {
    // Transform the vertex position using the MVP matrix and set gl_Position
    gl_Position = ubo.MVP * vec4(positions[gl_VertexIndex], 0.0, 1.0);

    // Pass the corresponding color from the colors array to the fragment shader
    fragColor = colors[gl_VertexIndex];
}
