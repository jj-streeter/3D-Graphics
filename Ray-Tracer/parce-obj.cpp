#include <iostream>
#include "file_util.h"

using namespace std;

struct FaceVertex
{
    int vertexIndex;
    int uvIndex;
    int normalIndex;
};

struct Mesh
{
    vector<vector<float>> vertices;
    vector<vector<float>> uvs;
    vector<vector<float>> normals;
    vector<vector<FaceVertex>> faces;
};

Mesh parseObj(string fileName){
    vector<string> lines = readLines(fileName);
    Mesh mesh;

    // Iterate through each line
    for (string line : lines){
        
        // Check for leading whitespace
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            continue;
        }

        string content = line.substr(first);

        // Split line into tokens
        vector<string> tokens = split(content, ' ');
        if (tokens.empty()) {
            continue;
        }

        // Read first word to find line type (v, vt, vn, f)
        string lineType = tokens[0];

        // Convert tokens and store data
        if (lineType == "v"){
            if (tokens.size() != 4) {
                cerr << "Incorrect token number in line: " << line << endl;
            }

            // Convert XYZ vertex location
            float x = stof(tokens[1]);
            float y = stof(tokens[2]);
            float z = stof(tokens[3]);

            vector<float> vertex = {x, y, z};
            mesh.vertices.push_back(vertex);
        }

        else if (lineType == "vt"){
            if (tokens.size() != 3) {
                cerr << "Incorrect token number in line: " << line << endl;
            }

            // Convert vertex uv coordinates
            float u = stof(tokens[1]);
            float v = stof(tokens[2]);

            vector<float> uv = {u, v};
            mesh.uvs.push_back(uv);
        }

        else if (lineType == "vn"){
            if (tokens.size() != 4) {
                cerr << "Incorrect token number in line: " << line << endl;
            }

            // Convert vertex XYZ normal
            float x = stof(tokens[1]);
            float y = stof(tokens[2]);
            float z = stof(tokens[3]);

            vector<float> normal = {x, y, z};
            mesh.normals.push_back(normal);
        }

        else if (lineType == "f"){
            if (tokens.size() < 4) {
                cerr << "Incorrect token number in line: " << line << endl;
            }

            vector<FaceVertex> face;
            for (string token : tokens) {
                if (token == "f") {
                    continue;
                }
                // Parce each vertex
                vector<string> indeces = split(token, '/');

                FaceVertex vertex;
                vertex.vertexIndex = stoi(indeces[0]) - 1;
                vertex.uvIndex = stoi(indeces[1]) - 1;
                vertex.normalIndex = stoi(indeces[2]) - 1;
                face.push_back(vertex);
            }
            mesh.faces.push_back(face);
        }

        else {
            // Skip unnecessary lines

        }
    }

    // Validate parsed face(s)
    for (vector<FaceVertex> face : mesh.faces) {
        // Confirm face is a triangle
        if (face.size() != 3){
            cerr << "Face is not a triangle" << endl;
        }
    }

    return mesh;
}

void print_mesh_details(Mesh mesh){
    cout << "Vertices:" << endl;
    for (vector<float> vertex : mesh.vertices) {
        cout << "\t(" << vertex[0] << ", " << vertex[1] << ", " << vertex[2] << ")" << endl;
    }

    cout << "UVs:" << endl;
    for (vector<float> uv : mesh.uvs) {
        cout << "\t(" << uv[0] << ", " << uv[1] << ")" << endl;
    }

    cout << "Normals:" << endl;
    for (vector<float> normal : mesh.normals) {
        cout << "\t(" << normal[0] << ", " << normal[1] << ", " << normal[2] << ")" << endl;
    }

    cout << "Faces:" << endl;
    for (vector<FaceVertex> face : mesh.faces) {
        cout << "Face:" << endl;
        for (FaceVertex vertex : face) {
            vector<float> v = mesh.vertices[vertex.vertexIndex];
            vector<float> uv = mesh.uvs[vertex.uvIndex];
            vector<float> n = mesh.normals[vertex.normalIndex];
            cout << "\tVertex: (" << v[0] << ", " << v[1] << ", " << v[2] << ")" << endl;
            cout << "\tUV: (" << uv[0] << ", " << uv[1] << ")" << endl;
            cout << "\tNormal: (" << n[0] << ", " << n[1] << ", " << n[2] << ")" << endl;
        }
    }
}

int main(){
    cout << "Input fileName to parce: ";
    string fileName;
    cin >> fileName;

    cout << "Attempting to parce file: " << fileName << "...\n" << endl;
    Mesh mesh = parseObj(fileName);
    cout << "Mesh created for file: " << fileName << endl;
    print_mesh_details(mesh);
    
    return 0;
}