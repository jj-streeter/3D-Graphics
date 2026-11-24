#ifndef OBJ_PARSER_HPP
#define OBJ_PARSER_HPP

#include <string>
#include <vector>

struct FaceVertex
{
    int vertexIndex;
    int uvIndex;
    int normalIndex;
};

struct Mesh
{
    std::vector<std::vector<float>> vertices;
    std::vector<std::vector<float>> uvs;
    std::vector<std::vector<float>> normals;
    std::vector<std::vector<FaceVertex>> faces;
};

Mesh parseObj(const std::string& fileName);

#endif