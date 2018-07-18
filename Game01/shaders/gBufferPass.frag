
#version 400



uniform sampler2D Texture;
uniform float Metallic;
uniform float Roughness;



in vec3 Position;
in vec3 Normal;
in vec2 TexCoord; //テクスチャ付きオブジェクトのカラーに使う予定

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec3 PositionData;
layout (location = 2) out vec4 NormalData;
layout (location = 3) out vec4 ColorData;
layout (location = 4) out vec3 UnlitColorData;

void main(){
    vec4 albedo = texture(Texture, TexCoord);
    
    PositionData = Position;
    NormalData = vec4(Normal, Roughness);
    ColorData = vec4(albedo.rgb, Metallic);
    UnlitColorData = vec3(0.0, 1.0, 1.0);
    FragColor = ColorData;
//    FragColor = vec4(Metallic, Metallic, Metallic, 0.0);
}

