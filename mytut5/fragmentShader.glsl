#version 330

out vec4 color;

void main()
{
	float lerpValue = gl_FragCoord.y / 500.0f;
	color = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);
}