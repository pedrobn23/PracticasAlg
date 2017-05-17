#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <cmath>
#include <algorithm>

int main(int argc, char** argv)
{
  int n_verts = std::stoi(argv[1]);
  double radius = std::stod(argv[2]);
  
  const double PI = 3.14152654;
  
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_real_distribution<> dist(0, 2*PI);

  std::vector<double> angles;

  std::cout << argv[1] << std::endl;

  for(int i=0; i<n_verts; i++)
    angles.push_back(dist(eng));

  std::sort(angles.begin(), angles.end());

  for(auto ang : angles)
  {
    std::cout << std::cos(ang)*radius << "," << std::sin(ang)*radius << std::endl;
  }
  
}
