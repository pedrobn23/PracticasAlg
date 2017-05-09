#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <limits>

// Point in the 2 dimensional euclidean space,
// to the extent allowed by floating point precision.
struct Point {
  double x;
  double y;

  bool operator==(const Point& other)
  {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Point& other)
  {
    return !(*this == other);
  }

  friend std::istream& operator>>(std::istream& is, Point& p)
  {
    char comma;
    is >> p.x >> comma >> p.y;

    return is;
  }

  friend std::ostream& operator<<(std::ostream& os, const Point& p)
  {
    os << p.x << ',' << p.y;

    return os;
  }
};

// Canonical distance in the 2 dimensional euclidean space.
double euclideanDistance(Point x1, Point x2)
{
  return std::sqrt(std::pow(x1.x-x2.x, 2)+std::pow(x1.y-x2.y, 2));
}

/*
 * Advance a forward iterator in a container as in a circular list.
 */
auto circularAdvance = [](auto& forwdIt, auto& cont, int n) {
  for(int i=0; i<n; i++)
  {
    forwdIt++;
    if(forwdIt == cont.end())
      forwdIt = cont.begin();
  }
};

/*
 * Finds the list of strings in a polygon. A string is an edge between two vertices
 * at distance 2. 
 *
 * If a polygon's number of nodes is odd, then you can find all of its
 * strings by traversing the vertices alternatively until you get to the initial.
 * If it's even, then there are two cycles of strings, therefore you need to apply
 * the aforementioned process starting at the first and the second vertex.
 */
std::vector<std::pair<Point, Point>> listStrings(std::vector<Point> poly)
{

  std::vector<std::pair<Point, Point>> ret;
  
  auto p = poly.begin();

  /*
   * This lambda function implements the actual traversal of strings
   * starting in a vertex.
   */
auto listForVertex = [&ret,&poly](auto p, auto p0) {
      do {
	auto prev = p;
	circularAdvance(p, poly, 2);
        ret.push_back( std::make_pair(*prev, *p) );
      }while(*p != p0);
  };

  listForVertex(p, poly[0]);
  if(!(poly.size() % 2)) listForVertex(++p, poly[1]);

  return ret;
}

int main(int argc, char** argv)
{
  int n_verts;
  std::cin >> n_verts;

  std::vector<Point> poly(n_verts);
  for(auto& p : poly)
    std::cin >> p;

  auto strings = listStrings(poly);

  auto& minString = strings[0];
  double minDistance = std::numeric_limits<double>::max();
  for(auto& s : strings)
  {
      if(euclideanDistance(s.first, s.second) < minDistance)
      {
	minDistance = euclideanDistance(s.first, s.second);
	minString = s;
      }
  }

  std::cout << "minDistance: " << minDistance << " minString: " << minString.first << '-' << minString.second << std::endl;
  
  return 0;
}
