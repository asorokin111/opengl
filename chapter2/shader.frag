#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;
uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 lightPos;
in vec3 normal;
in vec3 fragPos;

void main()
{
    vec3 ambient = material.ambient * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = (diff * material.diffuse) * lightColor;

    vec3 viewDirection = normalize(-fragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = material.specular * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
