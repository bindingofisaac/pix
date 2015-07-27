#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA{
    vec2 position;
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
        if      ( tid == 0)  { texColor = texture ( textures[0], uv);  }
        else if ( tid == 1)  { texColor = texture ( textures[1], uv);  }
        else if ( tid == 2)  { texColor = texture ( textures[2], uv);  }
        else if ( tid == 3)  { texColor = texture ( textures[3], uv);  }
        else if ( tid == 4)  { texColor = texture ( textures[4], uv);  }
        else if ( tid == 5)  { texColor = texture ( textures[5], uv);  }
        else if ( tid == 6)  { texColor = texture ( textures[6], uv);  }
        else if ( tid == 7)  { texColor = texture ( textures[7], uv);  }
        else if ( tid == 8)  { texColor = texture ( textures[8], uv);  }
        else if ( tid == 9)  { texColor = texture ( textures[9], uv);  }
        else if ( tid == 10) { texColor = texture ( textures[10], uv); }
        else if ( tid == 11) { texColor = texture ( textures[11], uv); }
        else if ( tid == 12) { texColor = texture ( textures[12], uv); }
        else if ( tid == 13) { texColor = texture ( textures[13], uv); }
        else if ( tid == 14) { texColor = texture ( textures[14], uv); }
        else if ( tid == 15) { texColor = texture ( textures[15], uv); }
    }
    float intensity = 1.0/length(fs_in.position.xy - light_pos);
    //float intensity = length(fs_in.position.xy - light_pos)/20.0;
    color = mix(texColor , vec4(intensity), 0.1) * intensity;
}
