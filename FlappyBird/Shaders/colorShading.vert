#version 450

// Taken as input from C++ code
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

// Output variables
out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 fragmentUV;

uniform mat4 orthoProjectionMatrix;

void main() {
	// Set x,y coordinates
	gl_Position.xy = (orthoProjectionMatrix * vec4(vertexPosition, 0.0, 1.0)).xy;
	
	// Set z to 0 since we're 2D
	gl_Position.z = 0.0;
	
	// Indicate that the coordinates are normalized
	gl_Position.w = 1.0;
	
	fragmentColor = vertexColor;
	
	fragmentPosition = vertexPosition;
	
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}