
#version 400



struct MaterialInfo{
    vec3 Kd;
};
uniform MaterialInfo Material;
uniform sampler2D Texture;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord; //テクスチャ付きオブジェクトのカラーに使う予定

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec3 PositionData;
layout (location = 2) out vec3 NormalData;
layout (location = 3) out vec3 ColorData;
layout (location = 4) out vec3 UnlitColorData;

void main(){
    vec4 col = texture(Texture, TexCoord);
    PositionData = Position;
    NormalData = Normal;
//    ColorData = Material.Kd;
    ColorData = texture(Texture, TexCoord).rgb;
    UnlitColorData = vec3(0.0, 1.0, 1.0);
    FragColor = vec4(ColorData, 1.0);
}

