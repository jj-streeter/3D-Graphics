/// Include the image write library and enable it
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Vector3.hpp"
#include "Triangle.hpp"
#include "obj_parser.hpp"

using namespace std;

/// Dimensions of the final image
const int w = 200;
const int h = 200;

/// Offset value
const float e = 0.0001f;

int bounces = 1;

/// The 1d array for storing the pixel we have generated
unsigned char pixels[w * h * 3];

/// Camera parameters
Vector3 camera_origin = Vector3{2.8, -2.8, 0.2f};
Vector3 camera_look_at = Vector3{0, 0, 0};
Vector3 camera_up = Vector3{0, 0, 1};

float aspect = w / h;
float fov_scale = tan(45.0f * 3.14159265f / 360.0f); // 45 degree vertical FOV

vector<Triangle> triangles = {};

Vector3 background_color = Vector3{0, 128, 0};

// Function to clamp pixel values to 0-255
unsigned char clamp(float val){
  return char(max(0.f, min(255.f, val)));
}

// Ray distance function
float trace_ray_distance(Vector3 origin, Vector3 direction){
  float closest_t = INFINITY;

  // Iterate through every triangle
  for(const Triangle& triangle : triangles)
  {
    // Find where we hit the plane
    Vector3 edge_one = triangle.one - triangle.two;
    Vector3 edge_two = triangle.three - triangle.two;
    Vector3 p = edge_two.cross(edge_one);
    Vector3 abc = p.normalize();
    float d = -abc.dot(triangle.one);

    float t = -(abc.dot(origin) + d) / abc.dot(direction);

    if(t > closest_t || t <= 0)
      continue;

    Vector3 collision_point = direction * t + origin;

    Vector3 minus_one = collision_point - triangle.one;
    Vector3 minus_two = collision_point - triangle.two;
    Vector3 minus_three = collision_point - triangle.three;

    float triangle_area = p.length() / 2;
    float area_one = minus_two.cross(minus_three).length() / 2;
    float area_two = minus_three.cross(minus_one).length() / 2;
    float area_three = minus_one.cross(minus_two).length() / 2;

    float u = area_one / triangle_area;
    float v = area_two / triangle_area;
    float a = area_three / triangle_area;

    float sum = u + v + a;

    float diff = abs(1 - sum);

    if(diff > 0.00001 || isnan(sum)){
      // Not in the triangle
    }
    else{
      // In the triangle
      closest_t = t;
    }
  }
  return closest_t;
}

// Ray tracing function
Vector3 trace_ray(Vector3 origin, Vector3 direction, int bounces = 2){
  
  Vector3 color = Vector3{background_color.x, background_color.y, background_color.z};
  
  if (bounces <= 0)
    return background_color;

  float closest_t = 1000000;

    // Iterate through every triangle
    for(const Triangle& triangle : triangles)
    {
      // Find where we hit the plane
      Vector3 edge_one = triangle.one - triangle.two;
      Vector3 edge_two = triangle.three - triangle.two;
      Vector3 p = edge_two.cross(edge_one);
      Vector3 abc = p.normalize();
      float d = -abc.dot(triangle.one);

      float t = -(abc.dot(origin) + d) / abc.dot(direction);

      if(t > closest_t || t <= 0)
        continue;

      Vector3 collision_point = direction * t + origin;

      Vector3 minus_one = collision_point - triangle.one;
      Vector3 minus_two = collision_point - triangle.two;
      Vector3 minus_three = collision_point - triangle.three;

      float triangle_area = p.length() / 2;
      float area_one = minus_two.cross(minus_three).length() / 2;
      float area_two = minus_three.cross(minus_one).length() / 2;
      float area_three = minus_one.cross(minus_two).length() / 2;

      float u = area_one / triangle_area;
      float v = area_two / triangle_area;
      float a = area_three / triangle_area;

      float sum = u + v + a;

      float diff = abs(1 - sum);

      if(diff > 0.00001 || isnan(sum)){
        // Not in the triangle
      }
      else{
        // In the triangle
        closest_t = t;

        /// SHADER
        Vector3 base_color = Vector3{255, 255, 255}; // white
        
        Vector3 ambient = base_color * .1;
        Vector3 normal = p.normalize();
        if (normal.dot(direction) > 0)
          normal *= -1;

        Vector3 light_direction = Vector3{-.5f, -5.f, .5f}.normalize();
        Vector3 offset_origin = collision_point + normal * e;

        float strength = max(0.f, normal.dot(light_direction));

        Vector3 diffuse = base_color * strength;

        // Check if the light is blocked by any other triangle
        if (trace_ray_distance(offset_origin, light_direction) != INFINITY){
          diffuse = Vector3{0, 0, 0};
        }

        Vector3 reflective = Vector3{0, 0, 0};

        if (true){
          Vector3 reflective_direction = direction - normal * 2 * normal.dot(direction);
          reflective = trace_ray(offset_origin, reflective_direction, bounces - 1) * .5;
          diffuse *= .5;
          ambient *= .5;
        }

        Vector3 _color = ambient + diffuse + reflective;
        color = _color;
      }
  }
  return color;
}

int main()
{
  // DEBUG
  cout << "Importing obj file as mesh..." << endl;

  /// Import obj file as a mesh
  Mesh mesh = parseObj("untitled.obj");
  
  // DEBUG
  cout << "Mesh imported. Converting mesh faces to triangles..." << endl;

  /// Convert all mesh faces to Triangle objects and add them to triangles
  /// before looping through pixels
  for (vector<FaceVertex> face : mesh.faces)
  {
    vector<Vector3> positions;
    for (FaceVertex vertex : face)
    {
      Vector3 pos = Vector3{mesh.vertices[vertex.vertexIndex][0],
                            mesh.vertices[vertex.vertexIndex][1],
                            mesh.vertices[vertex.vertexIndex][2]};
      positions.push_back(pos);
    }
    Triangle tri = Triangle{positions[0], positions[1], positions[2]};
    triangles.push_back(tri);
  }

  // DEBUG
  cout << "Mesh faces converted. Looping over pixels..." << endl;

  Vector3 forward = (camera_look_at - camera_origin).normalize();
  Vector3 right = forward.cross(camera_up).normalize();
  Vector3 up = right.cross(forward).normalize();

  /// Loop over each line doing down
  for (int y = 0; y < h; y++)
  {
    //DEBUG
    if (y % 10 == 0)
      cout << "Ray tracing line: " << y << " of " << h << endl;

    /// While going down, loop over every pixel going right
    for (int x = 0; x < w; x++)
    {
      /// Figure out our index in the 1d array of pixels
      int index = y * w * 3 + x * 3;

      unsigned char r = background_color.x;
      unsigned char g = background_color.y;
      unsigned char b = background_color.z;

      /// How do we ray trace?
      float screen_x = (2.0f * (x + 0.5f) / w - 1.0f) * aspect * fov_scale;
      float screen_y = (1.0f - 2.0f * (y + 0.5f) / h) * fov_scale;

      Vector3 ray = (forward + right * screen_x + up * screen_y).normalize();
      Vector3 color = trace_ray(camera_origin, ray, bounces);

      /// Assign the r, g, and b values to the pixel at index
      r = clamp(color.x);
      g = clamp(color.y);
      b = clamp(color.z);

      pixels[index] = r;
      pixels[index + 1] = g;
      pixels[index + 2] = b;
    }
  }

  // DEBUG
  cout << "Finished ray tracing. Writing image..." << endl;

  ///Write the final image as a png
  stbi_write_png("Suzanne.png", w, h, 3, pixels, w * 3);

  // DEBUG
  cout << "Image written. Exiting..." << endl;

  return 0;
}