#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <utility>
#include <limits>
#include <cmath>


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
double euclidean_distance(Point x1, Point x2)
{
  return std::sqrt(std::pow(x1.x-x2.x, 2)+std::pow(x1.y-x2.y, 2));
}


/*
 * Advance an element (an iterator or an integer) as in a circular list.
 */
auto circular_advance = [](auto& forwdIt, auto initValue, auto endValue, int n) {
  for(int i=0; i<n; i++)
  {
    forwdIt++;
    if(forwdIt == endValue)
      forwdIt = initValue;
  }

  return forwdIt;
};




int main(int argc, char** argv)
{
  int n_verts;
  std::list<Point> points;

  std::cin >> n_verts;

  // Read points and assign ids.
  for(int i=0; i<n_verts; i++)
  {
    Point p;
    std::cin >> p;
    p.id = i;

    points.push_back(p);
  }

  std::vector<std::pair<Point, Point>> sol;

  while(points.size() > 3)
  {
    double min_distance = std::numeric_limits<double>::max();
    auto it_min = points.begin();
    std::pair<Point, Point> min_string;

    /* This lambda function serves to avoid explicitly
     * repeating a loop with different values.
     */
    auto find_min_string = [&min_distance, &it_min, &min_string, &points](auto initial_point_it) {
      auto p0 = initial_point_it;
      auto p = p0;

      do {
	auto prev = p;
	
	circular_advance(p, points.begin(), points.end(), 2);
	if(min_distance > euclidean_distance(*prev, *p))
	{
	  min_distance = euclidean_distance(*prev, *p);
	  min_string = std::make_pair(*prev, *p);
	  it_min = circular_advance(prev, points.begin(), points.end(), 1);
	}

      }while(p != p0);
    };

    // Unconditionally find minimum length string starting
    // at the first element
    find_min_string(points.begin());

    // If the polygon's number of edges is even, we need to
    // do the same starting at the second one
    auto it = points.begin();
    if(!(points.size()%2)) find_min_string(++it);

    sol.push_back(min_string);
    points.erase(it_min);
  }

  for(auto& s : sol)
  {
    std::cout << s.first << " <-> " << s.second << " -> " << euclidean_distance(s.first, s.second) << std::endl;
  }
  
  return 0;
}
