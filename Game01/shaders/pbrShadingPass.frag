
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

struct GeometricContext {
    vec3 position;
    vec3 normal;
    vec3 viewDir;
};

vec3 diffuseModel(vec3 pos, vec3 norm, vec3 diff){
    vec3 s = normalize(vec3(Light.Position) - pos);
    float sDotN = max(dot(s, norm), 0.0);
    vec3 diffuse = Light.Intensity * diff * sDotN;
    
    return diffuse;
}



void main(){
    vec4 albedoColor = texture(ColorTex, TexCoord);
    vec4 normColor = texture(NormalTex, TexCoord);
    
    vec3 albedo = albedoColor.rgb;
    vec3 norm = normColor.rgb;
    
    vec3 pos = vec3(texture(PositionTex, TexCoord));
    vec3 shadow = vec3(texture(ShadowmapTex, TexCoord));
    float metallic = albedoColor.a;
    float roughness = normColor.a;
    
    GeometricContext geometry;
    geometry.position = pos.rgb;
    geometry.normal = normalize(norm);
    geometry.viewDir = normalize(-1*pos);
    
    
    FragColor = vec4(diffuseModel(pos, norm, albedo), 1.0);
    
//    FragColor = vec4(albedoColor.rgb, 1.0);
//    FragColor = albedoColor;
    
   
//    FragColor = FragColor * vec4(shadow, 1.0);
    //FragColor = vec4(norm, 1.0);
    //    FragColor = vec4(pos, 1.0);
//    FragColor = vec4(albedo, 1.0);
    //        FragColor = vec4 (shadow, 1.0);
    //    FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}

