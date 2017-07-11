#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_() {
  std::ifstream in;
  in.open (filename, std::ifstream::in);
  if (in.fail()) {
    return;
  }
  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line.c_str());
    char trash;
    if (!line.compare(0, 2, "v ")) {
      iss >> trash;
      Vec3f v;
      for (int i = 0; i < 3; i++) {
        iss >> v.raw[i];
      }
      verts_.push_back(v);
    } else if (!line.compare(0, 2, "f ")) {
      // Going to toss the 'f' character
      iss >> trash;

      std::string idx;
      iss >> idx;
      std::vector<int> f;
      int slashPos = idx.find_first_of('/');
      if (slashPos != std::string::npos) {
				// Going to assume that if we find a '/' character in line that
				// we have a face with notation 'f 111/222/333'
        f.push_back(std::stoi(idx.substr(0, slashPos)) - 1);
        while (iss >> idx) {
          slashPos = idx.find_first_of('/');
          f.push_back(std::stoi(idx.substr(0, slashPos)) - 1);
        }
      } else {
        f.push_back(std::stoi(idx) - 1);
        while (iss >> idx) {
          f.push_back(std::stoi(idx) - 1);
        }
      }
      faces_.push_back(f);
    }
  }
  std::cerr << "#vertices: " << verts_.size() << " #faces: "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
  return verts_.size();
}

int Model::nfaces() {
  return faces_.size();
}

std::vector<int> Model::face(int idx) {
  return faces_[idx];
}

Vec3f Model::vert(int i) {
  return verts_[i];
}
