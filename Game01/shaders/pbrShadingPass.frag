
#version 400

// defines
#define PI 3.14159265359
#define PI2 6.28318530718
#define RECIPROCAL_PI 0.31830988618
#define RECIPROCAL_PI2 0.15915494
#define LOG2 1.442695
#define EPSILON 1e-6


struct LightInfo{
    vec4 Position;
    vec3 Intensity;
};
uniform LightInfo Light;


uniform sampler2D PositionTex, NormalTex, ColorTex, ShadowmapTex;
uniform sampler2D TestTex;




in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 FboColor;

struct GeometricContext {
    vec3 position;
    vec3 normal;
    vec3 viewDir;
};

//lights
struct IncidentLight {
    vec3 direction;
    vec3 color;
    bool visible;
};

struct DirectionalLight{
    vec3 direction;
    vec3 color;
};

struct PointLight{
    vec3 position;
    vec3 color;
    float distance;
    float decay;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    vec3 color;
    float distance;
    float decay;
    float coneCos;
    float penumbraCos;
};

//material
struct Material {
    vec3 diffuseColor;
    vec3 specularColor;
    float specularRoughness;
};

#define LIGHT_MAX 4
uniform DirectionalLight DirectionalLights[LIGHT_MAX];
uniform PointLight PointLights[LIGHT_MAX];
uniform SpotLight SpotLights[LIGHT_MAX];
uniform int numDirectionalLights;
uniform int numPointLights;
uniform int numSpotLights;


//x 0-1
float saturate(float x){
    return clamp(x,0.0,1.0);
}

bool testLightInRange(const in float lightDistance, const in float cutoffDistance){
    return any(bvec2(cutoffDistance == 0.0, lightDistance < cutoffDistance));
}

//decay
float punctualLightIntensityToIrradianceFactor(const in float lightDistance, const in float cutoffDistance, const in float decayExponent) {
    if (decayExponent > 0.0) {
        return pow(saturate(-lightDistance/ cutoffDistance + 1.0), decayExponent);
    }
    return 1.0;
}

void getDirectionalDirectLightIrradiance(const in DirectionalLight directionalLight, const in GeometricContext geometry, out IncidentLight directLight){
    directLight.color = directionalLight.color;
    directLight.direction = directionalLight.direction;
    directLight.visible = true;
}

void getPointDirectLightIrradiance(const in PointLight pointLight, const in GeometricContext geometry, out IncidentLight directLight){
    vec3 L = pointLight.position - geometry.position;
    directLight.direction = normalize(L);
    float lightDistance = length(L);
    
    if(testLightInRange(lightDistance, pointLight.distance)){
        directLight.color = pointLight.color;
        directLight.color *= punctualLightIntensityToIrradianceFactor(lightDistance, pointLight.distance, pointLight.decay);
        directLight.visible = true;
        
    }else{
        directLight.color = vec3(0.0);
        directLight.visible = false;
    }
}

void getSpotDirectLightIrradiance(const in SpotLight spotLight, const GeometricContext geometry, out IncidentLight directLight){
    vec3 L = spotLight.position - geometry.position;
    directLight.direction = normalize(L);
    
    
    float lightDistance = length(L);
    
    float angleCos = dot(directLight.direction, spotLight.direction);

    if(all(bvec2(angleCos > spotLight.coneCos, testLightInRange(lightDistance, spotLight.distance)))){
        float spotEffect = smoothstep(spotLight.coneCos, spotLight.penumbraCos, angleCos);
        directLight.color = spotLight.color;
        directLight.color *= spotEffect * punctualLightIntensityToIrradianceFactor(lightDistance, spotLight.distance, spotLight.decay);
        directLight.visible = true;
    }else{
        directLight.color = vec3(0.0);
        directLight.visible = false;
    }
}

vec3 DiffuseBRDF(vec3 diffuseColor){
    return diffuseColor/PI;
}

vec3 F_Schlick(vec3 specularColor, vec3 H, vec3 V){
    return (specularColor + (1.0-specularColor) * pow(1.0 - saturate(dot(V, H)), 5.0));
}

float D_GGX(float a, float dotNH){
    float a2 = a*a;
    float dotNH2 = dotNH*dotNH;
    float d = dotNH2 * (a2 - 1.0) + 1.0;
    return a2 / (PI * d * d);
}

float G_Smith_Schlick_GGX(float a, float dotNV, float dotNL){
    float k = a*a*0.5 + EPSILON;
    float gl = dotNL / (dotNL * (1.0-k)+k);
    float gv = dotNV / (dotNV * (1.0-k)+k);
    return gl*gv;
}

vec3 SpecularBRDF(const in IncidentLight directLight, const in GeometricContext geometry, vec3 specularColor, float roughnessFactor){
    vec3 N = geometry.normal;
    vec3 V = geometry.viewDir;
    vec3 L = directLight.direction;
    
    float dotNL = saturate(dot(N,L));
    float dotNV = saturate(dot(N,V));
    vec3 H = normalize(L+V);
    float dotNH = saturate(dot(N,H));
    float dotVH = saturate(dot(V,H));
    float dotLV = saturate(dot(L,V));
    float a = roughnessFactor * roughnessFactor;
    
    float D = D_GGX(a, dotNH);
    float G = G_Smith_Schlick_GGX(a, dotNV, dotNL);
    vec3 F = F_Schlick(specularColor, V, H);
    return (F*(G*D))/(4.0*dotNL*dotNV+EPSILON);
}


struct ReflectedLight{
    vec3 directDiffuse;
    vec3 directSpecular;
    vec3 indirectDiffuse;
    vec3 indirectSpecular;
};

void RE_Direct(const in IncidentLight directLight, const in GeometricContext geometry, const in Material material, inout ReflectedLight reflectedLight) {
    
    float dotNL = saturate(dot(geometry.normal, directLight.direction));
    vec3 irradiance = dotNL * directLight.color;
    
    // punctual light
    irradiance *= PI;
    
    reflectedLight.directDiffuse += irradiance * DiffuseBRDF(material.diffuseColor);
    reflectedLight.directSpecular += irradiance * SpecularBRDF(directLight, geometry, material.specularColor, material.specularRoughness);
}

vec3 diffuseModel(vec3 pos, vec3 norm, vec3 diff){
    vec3 s = normalize(vec3(Light.Position) - pos);
    float sDotN = max(dot(s, norm), 0.0);
    vec3 diffuse = Light.Intensity * diff * sDotN;
    
    return diffuse;
}



void main(){
    vec4 albedoColor = texture(ColorTex, TexCoord);
    vec4 normColor = texture(NormalTex, TexCoord);
    vec3 shadow = vec3(texture(ShadowmapTex, TexCoord));
    
    vec3 albedo = albedoColor.rgb;
    albedo *= shadow;
    vec3 norm = normColor.rgb;
    
    vec3 pos = vec3(texture(PositionTex, TexCoord));
    
    float metallic = albedoColor.a;
    float roughness = normColor.a;
    
    GeometricContext geometry;
    geometry.position = pos.rgb;
    geometry.normal = normalize(norm);
    geometry.viewDir = normalize(-1*pos);
    
    Material material;
    material.diffuseColor = mix(albedo, vec3(0.0), metallic);
    material.specularColor = mix(vec3(0.04), albedo, metallic);
    material.specularRoughness = roughness;
    
    ReflectedLight reflectedLight = ReflectedLight(vec3(0.0), vec3(0.0), vec3(0.0), vec3(0.0));
    vec3 emissive = vec3(0.0);
    float opacity = 1.0;
    
    IncidentLight directLight;
    
    FragColor = vec4(vec3(0.0), 1.0);
    
    for(int i=0; i<LIGHT_MAX; i++){
        if(i>=numPointLights) break;
        
        getPointDirectLightIrradiance(PointLights[i], geometry, directLight);
        
        if(directLight.visible){
            RE_Direct(directLight, geometry, material, reflectedLight);
        }
    }

    for(int i=0; i<LIGHT_MAX; i++){
        if(i >= numSpotLights) break;
        getSpotDirectLightIrradiance(SpotLights[i], geometry, directLight);
        
        if(directLight.visible){
            RE_Direct(directLight, geometry, material, reflectedLight);
        }
    }

    for(int i=0; i<LIGHT_MAX; i++){
        if(i >= numDirectionalLights) break;
        getDirectionalDirectLightIrradiance(DirectionalLights[i], geometry, directLight);
        RE_Direct(directLight, geometry, material, reflectedLight);
    }
    
    vec3 outgoingLight = emissive + reflectedLight.directDiffuse + reflectedLight.directSpecular + reflectedLight.indirectDiffuse + reflectedLight.indirectSpecular;
    FragColor =  vec4(outgoingLight, 1.0f);
	FboColor = FragColor;
//    FragColor.rgb = geometry.normal;
    
//    FragColor = vec4(diffuseModel(pos, norm, albedo), 1.0);
//    FragColor = FragColor * vec4(shadow, 1.0);
    

}

