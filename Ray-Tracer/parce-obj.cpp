#include <iostream>
#include "file_util.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2){
        cout << "Error: OBJ filename required." << endl;
        return 1;
    }

    // Read file
    string file_name = argv[1];
    cout << "Parsing file `" << file_name << "`..." << endl;
    vector<string> lines = readLines(file_name);

    vector<vector<float>> vertices;
    vector<vector<float>> uvs;
    vector<vector<float>> normals;
    vector<vector<vector<int>>> faces;

    // Iterate through each line
    for (string line : lines){
        
        // Check for leading whitespace
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            continue; // Empty line
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
                cout << "Error: Incorrect token number in line: " << line << endl;
            }

            cout << "DEBUG--lineType = v: " << line << endl;
            // Convert XYZ vertex location
            float x = stof(tokens[1]);
            float y = stof(tokens[2]);
            float z = stof(tokens[3]);

            vector<float> vertex = {x, y, z};
            vertices.push_back(vertex);
            cout << "DEBUG--Vertex: (" << vertex[0] << ", " << vertex[1] << ", " << vertex[2] << ")" << endl;
        }

        else if (lineType == "vt"){
            if (tokens.size() != 3) {
                cout << "Error: Incorrect token number in line: " << line << endl;
            }

            cout << "DEBUG--lineType = vt: " << line << endl;
            // Convert vertex uv coordinates
            float u = stof(tokens[1]);
            float v = stof(tokens[2]);

            vector<float> uv = {u, v};
            uvs.push_back(uv);
            cout << "DEBUG--UV: (" << uv[0] << ", " << uv[1] << ")" << endl;
        }

        else if (lineType == "vn"){
            if (tokens.size() != 4) {
                cout << "Error: Incorrect token number in line: " << line << endl;
            }

            cout << "DEBUG--lineType = vn: " << line << endl;
            // Convert vertex XYZ normal
            float x = stof(tokens[1]);
            float y = stof(tokens[2]);
            float z = stof(tokens[3]);

            vector<float> normal = {x, y, z};
            normals.push_back(normal);
            cout << "DEBUG--Normal: (" << normal[0] << ", " << normal[1] << ", " << normal[2] << ")" << endl;
        }

        else if (lineType == "f"){
            if (tokens.size() < 4) {
                cout << "Error: Incorrect token number in line: " << line << endl;
            }

            cout << "DEBUG--lineType = f: " << line << endl;
            // Parse the face
            vector<vector<int>> face;
            for (string token : tokens) {
                if (token == "f") {
                    continue;
                }
                // Parce and split each vertex
                vector<string> indeces = split(token, '/');
                cout << "DEBUG--Vertex indeces: " << indeces[0] << ", " << indeces[1] << ", " << indeces[2] << endl;
                // Use indeces to form each vertex
                int vertexIndex = stoi(indeces[0]) - 1;
                int uvIndex = stoi(indeces[1]) - 1;
                int normalIndex = stoi(indeces[2]) - 1;

                vector<int> vertex = {vertexIndex, uvIndex, normalIndex};
                face.push_back(vertex);
            }
            faces.push_back(face);
        }

        else {
            cout << "DEBUG--skip line: " << line << endl;
            // Skip unnecessary lines

        }
    }

    // Validate parsed face(s)
    for (vector<vector<int>> face : faces) {
        // Confirm face is a triangle
        if (face.size() != 3){
            return 1;
        }
    }

    return 0;
}