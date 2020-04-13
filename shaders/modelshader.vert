#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

out vec2 f_uv;
out vec4 f_color;
out vec3 f_norm;


void main() {
  f_uv = uv;
  f_norm = normal;
  f_color = vec4(1,1,1,1);

  gl_Position = pos;
}
