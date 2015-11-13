out vec4 FragColor;
in vec2 tectureCoords;
uniform sampler2D texture0;

void main(){
FragColor = texture(texture0, tectureCoords);
}