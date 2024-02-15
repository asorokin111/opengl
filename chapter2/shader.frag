#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;
struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight dirLight;
struct PointLight
{
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

vec3 calcDirLight(DirectionalLight light, vec3 normalVec, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normalVec, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(-fragPos);

    vec3 result = calcDirLight(dirLight, norm, viewDir);

    for (int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        result += calcPointLight(pointLights[i], norm, fragPos, viewDir);
    }

    FragColor = vec4(result, 1.0);
}

vec3 calcDirLight(DirectionalLight light, vec3 normalVec, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normalVec);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * texture(material.diffuse, texCoords).rgb;
    vec3 diffuse  = light.diffuse  * diff * texture(material.diffuse, texCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;

    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normalVec, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normalVec, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);
    vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
