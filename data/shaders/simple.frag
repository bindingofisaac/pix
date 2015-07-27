#version 330 core

layout (location = 0) out vec4 color;

in DATA{
  vec4 color;
  vec2 uv;
  float tid;
} fs_in;

uniform sampler2D textures[32];

void main(){
    vec4 texColor = fs_in.color;
    vec2 uv = vec2(fs_in.uv.x, 1-fs_in.uv.y);
    if(fs_in.tid > 0.0){
        int tid = int(fs_in.tid-0.5);
        if(tid == 0){
            texColor = texture(textures[0], uv);
        }else if(tid == 1){
            texColor = texture(textures[1], uv);
        }else if(tid == 2){
            texColor = texture(textures[2], uv);
        }
    }
    color = texColor;
}
