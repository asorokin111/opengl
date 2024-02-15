#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;
struct Light
{
    float cutoff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
uniform Light light;
uniform vec3 objectColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

void main()
{
    vec3 lightDirection = normalize(-fragPos);
    float theta = dot(lightDirection, vec3(0, 0, 1));

    if (theta > light.cutoff)
    {
        float lightDist = length(-fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * lightDist + light.quadratic * lightDist * lightDist);

        vec3 ambient = texture(material.diffuse, texCoords).rgb * light.ambient;

        vec3 norm = normalize(normal);
        float diff = max(dot(norm, lightDirection), 0.0);
        vec3 diffuse = diff * texture(material.diffuse, texCoords).rgb * light.diffuse;

        vec3 viewDirection = lightDirection;
        vec3 reflectDirection = reflect(-lightDirection, norm);
        float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
        vec3 specular = texture(material.specular, texCoords).rgb * spec * light.specular;

        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        vec3 result = (ambient + diffuse + specular) * objectColor;
        FragColor = vec4(result, 1.0);
    }
    else
    {
        FragColor = vec4(light.ambient * texture(material.diffuse, texCoords).rgb, 1.0);
    }
}
