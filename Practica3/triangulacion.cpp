#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <utility>
#include <cmath>
#include <limits>

// Point in the 2 dimensional euclidean space,
// to the extent allowed by floating point precision.
struct Point {
  int id;
  double x;
  double y;


  bool operator==(const Point& other)
  {
    return id == other.id;
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
    os << p.id << '@' << p.x << ',' << p.y;

    return os;
  }
};

// Canonical distance in the 2 dimensional euclidean space.
double euclideanDistance(Point x1, Point x2)
{
  return std::sqrt(std::pow(x1.x-x2.x, 2)+std::pow(x1.y-x2.y, 2));
}


/*
 * Advance an element (an iterator or an integer) as in a circular list.
 */
auto circularAdvance = [](auto& forwdIt, auto initValue, auto endValue, int n) {
  for(int i=0; i<n; i++)
  {
    forwdIt++;
    if(forwdIt == endValue)
      forwdIt = initValue;
  }
};

auto sumModulo = [](int a, int b, int n)
{
  return (a+b)%n;
};

auto subModulo = [](int a, int b, int n)
{
  return a>b ? (a-b)%n : n-(a-b)%n;
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
std::unordered_map<int, std::pair<Point, Point>> listStrings(std::map<int, Point> poly)
{

  std::unordered_map<int, std::pair<Point, Point>> ret;
  
  /*
   * This lambda function implements the actual traversal of strings
   * starting in a vertex.
   */

  //Esta función la hago aquí porque solo la hago aquí
  auto listForVertex = [&ret,&poly](int p) {
      int p0 = p;
      do {
	auto prev = p;
	circularAdvance(p, 0, (int) poly.size(), 2);
	
        ret[sumModulo(prev, 1, poly.size())] = std::make_pair(poly[prev], poly[p]);
      }while(p != p0);
  };

  listForVertex(0);
  if(!(poly.size() % 2)) listForVertex(1);

  return ret;
}

int main(int argc, char** argv)
{
  int n_verts;
  std::cin >> n_verts;

  std::map<int, Point> poly;
  for(int i=0; i<n_verts; i++)
  {
    Point p;
    std::cin >> p;

    p.id = i;
    poly[i] = p;
  }

  auto strings = listStrings(poly);
  std::vector<std::pair<Point, Point>> sol;

  /* DEBUG */
  for(auto& s : strings)
  {
    std::cout << "Key: " << s.first << "  " << s.second.first << " <-> " << s.second.second << "  " << euclideanDistance(s.second.first, s.second.second) << std::endl;
  }

  std::cout << std::endl;
  /* DEBUG */

  while(poly.size() > 3)
  {
    double minDistance = std::numeric_limits<double>::max();
    auto minString = std::pair<Point, Point>();
    int minKey;
    std::cout << std::endl << std::endl;
    for(auto& s : strings)
    {
        if(euclideanDistance(s.second.first, s.second.second) < minDistance)
        {
    	  minDistance = euclideanDistance(s.second.first, s.second.second);
    	  minString = s.second;
	  minKey = s.first;
        }
	
	std::cout << "Key: " << s.first << "  " << s.second.first << " <-> " << s.second.second << "  " << euclideanDistance(s.second.first, s.second.second) << std::endl;
    }

    // Unnecesary, fix
    int toEraseVertex = sumModulo(minString.first.id, 1, n_verts);
    poly.erase(toEraseVertex);

    std::cout << "Erased " << toEraseVertex << " " << subModulo(toEraseVertex, 1, n_verts) << std::endl;
    
    strings.erase(subModulo(toEraseVertex, 1, n_verts));
    strings.erase(sumModulo(toEraseVertex, 1, n_verts));

    sol.push_back(strings[minKey]);
    strings.erase(minKey);
  }

  for(auto& s : sol)
  {
    std::cout << s.first << " <-> " << s.second << std::endl;
  }
  
  return 0;
}
