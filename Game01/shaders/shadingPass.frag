#version 400

struct LightInfo{
    vec4 Position;
    vec3 Intensity;
};
uniform LightInfo Light;


uniform sampler2D PositionTex, NormalTex, ColorTex, ShadowmapTex;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec3 PositionData;
layout (location = 2) out vec3 NormalData;
layout (location = 3) out vec3 ColorData;
layout (location = 4) out vec3 UnlitColorData;

vec3 diffuseModel(vec3 pos, vec3 norm, vec3 diff){
    vec3 s = normalize(vec3(Light.Position) - pos);
    float sDotN = max(dot(s, norm), 0.0);
    vec3 diffuse = Light.Intensity * diff * sDotN;
    
    return diffuse;
}



void main(){
    vec3 pos = vec3(texture(PositionTex, TexCoord));
    vec3 norm = vec3(texture(NormalTex, TexCoord));
    vec3 diffColor = vec3(texture(ColorTex, TexCoord));
    vec3 shadow = vec3(texture(ShadowmapTex, TexCoord));
    
    FragColor = vec4(diffuseModel(pos, norm, diffColor), 1.0);
    
    FragColor = FragColor * vec4(shadow, 1.0);
    //    FragColor = vec4(norm, 1.0);
    //    FragColor = vec4(pos, 1.0);
    //    FragColor = vec4(diffColor, 1.0);
    FragColor = vec4(shadow, 1.0);
    //    FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}

