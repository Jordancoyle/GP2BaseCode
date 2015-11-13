
in vec2 vertexPosition
out vec2 textureCoords

void Main(){
textureCoords = (vertexPosition + 1.0) / 2.0;
vec4 glPosition(vertexPosition.x, vertexPosition.y, 0.0, 1.0);
}
