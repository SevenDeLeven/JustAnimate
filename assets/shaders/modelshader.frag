#version 330 core

in vec2 f_uv;
in vec3 f_norm;
in vec4 f_color;

out vec4 out_color;

void main() {
  out_color = f_color;
}
