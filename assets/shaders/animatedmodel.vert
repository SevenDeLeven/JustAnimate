#version 330 core

in vec3 pos;
in vec2 uv;
in vec3 normal;

out vec2 f_uv;
out vec4 f_color;
out vec3 f_norm;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

void main() {
  f_uv = uv;
  f_norm = normal;
  f_color = vec4(1,0,1,1);
  gl_Position = projectionMatrix * viewMatrix * transformMatrix * vec4(pos,1.0);
}
