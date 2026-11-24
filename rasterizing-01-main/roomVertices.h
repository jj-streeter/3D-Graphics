#pragma once

float roomVertices[] = {
    //Front Wall

    /*position*/ +1, +1, -1, /* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex one
    /*position*/ -1, +1, -1, /* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex two
    /*position*/ +1, -1, -1, /* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex three
    
    /*position*/ -1, +1, -1, /* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex two
    /*position*/ +1, -1, -1, /* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex three
    /*position*/ -1, -1, -1, /* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex one

    //Back Wall

    /*position*/ +1, +1, +1, /* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex one
    /*position*/ -1, +1, +1, /* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex two
    /*position*/ +1, -1, +1, /* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex three
    
    /*position*/ -1, +1, +1, /* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex two
    /*position*/ +1, -1, +1, /* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex three
    /*position*/ -1, -1, +1, /* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex one

    //Side Wall

    /*position*/-1, +1, +1,/* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex one
    /*position*/-1, +1, -1,/* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex two
    /*position*/-1, -1, +1,/* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex three
    
    /*position*/-1, +1, -1,/* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex two
    /*position*/-1, -1, +1,/* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex three
    /*position*/-1, -1, -1,/* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex one

    //Side Wall
    
    /*position*/+1, +1, +1,/* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex one
    /*position*/+1, +1, -1,/* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex two
    /*position*/+1, -1, +1,/* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex three
    
    /*position*/+1, +1, -1,/* uvs */ 1, 0, /*normals*/ 0, 0, 1, // Vertex two
    /*position*/+1, -1, +1,/* uvs */ 1, 1, /*normals*/ 0, 0, 1, // Vertex three
    /*position*/+1, -1, -1,/* uvs */ 0, 0, /*normals*/ 0, 0, 1, // Vertex one
};