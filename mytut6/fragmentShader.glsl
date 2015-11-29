#version 330

out vec4 outputColor;
uniform float fLoopDuration;
uniform float elapsedTime;

const vec4 firstColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 secondColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);

void main()
{
    float currTime = mod(elapsedTime / 1000.0f, fLoopDuration);
    float currLerp = currTime / fLoopDuration;
    
    outputColor = mix(firstColor, secondColor, currLerp);
}