#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
out vec4 theColor;

uniform float fLoopDuration;
uniform float elapsedTime;

uniform float frustumScale;
uniform float zNear;
uniform float zFar;

void main()
{
	theColor = color;
    float fScale = 3.14159f * 2.0f / fLoopDuration;

	float currentTime = mod(elapsedTime / 1000.0f, fLoopDuration);
	vec4 totalOffset = vec4(
		cos(currentTime * fScale) * 0.5f,
		sin(currentTime * fScale) * 0.5f,
		0, 0
	);
    vec4 cameraPos = position + totalOffset;
	vec4 clipPos;
	clipPos.xy = cameraPos.xy * frustumScale;
	clipPos.z = cameraPos.z * (zNear + zFar) / (zNear - zFar);
	clipPos.z += 2 * zNear * zFar / (zNear - zFar);
	clipPos.w = -cameraPos.z;
	gl_Position = clipPos;
}