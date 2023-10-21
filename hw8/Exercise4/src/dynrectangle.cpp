/*
Name: Arushi Sadam
UT EID: ars7724
TACC ID: a2097855
*/

// Purpose: create two dynamic rectangles such that the top right (tr) point of rectangle (lielow, in code) is the bottom left (bl) point of another rectangle (upper, in code). 
// The bl point of liewlow and the tr point of upper are fixed. The current lielow tr point is halfway between the bl point of liewlow and the tr point of upper. 
// Input a scale factor to scale the tr point of liewlow, and see the areas of the two rectangles change. 

// include input and output streams
#include <iostream>
using std::cin;
using std::cout;

// for use of shared pointers:
#include <memory>
using std::make_shared;
using std::shared_ptr;

//Point class: used to initialize Rectangle's corner points + for the scale function
class Point {
protected:
  float x, y;
public:
// uses an input scaling factor and scales the x and y coordinates of the point by the factor
  void scale(float factor){
    x = factor*x;
    y = factor*y;
  };
// initialize Point with input parameters (ux, uy)
  Point(float ux, float uy) {
    x = ux;
    y = uy;
  }
  // Point class methods: find the width and length of the rectangle (dx, dy)
  float dx(Point other) {return other.x - x;}
  float dy(Point other) {return other.y - y;}
};

// Class that uses pointers to the bottom left (bl) and top right (tr) to build a dynamic rectangle. Has function to compute the area of the rectangle.
class DynRectangle {
private:
  shared_ptr<Point> bl, tr; // pointers to Points bl and tr
public:
  // initialize the Dynamic rectangle with the input pointer parameters (ibl, itr)
  DynRectangle(shared_ptr<Point> ibl, shared_ptr<Point> itr) : bl(ibl), tr(itr) {}
  float area() { return (bl->dx(*tr)) * (bl->dy(*tr));} // use pointers to find the width and height of rectangle -> to find area
  // *tr dereferences the shared pointer 
};

//gets scalefactor, calls appropriate functions to find areas of the rectangles, and outputs the areas of both rectangles before and after scaling
int main() {

  float scalefactor; //get a scale factor from user
  cout << "Input a scaling factor for bottom rectangle top right point: ";
  cin >> scalefactor;

  // main, initialize point objects
  Point origin(0, 0), fivetwo(5, 2), tenfour(10,4);
 
  // main, initialize pointers to points
  auto originp = make_shared<Point>(0, 0);
  auto fivetwop = make_shared<Point>(5, 2);
  auto tenfourp = make_shared<Point>(10,4);
  
  //make two dynamic rectangles such that the top right of one (lielow) is the bottom left of the other (upper)
  DynRectangle lielow(originp, fivetwop);
  DynRectangle upper(fivetwop, tenfourp);

  // record the area before scaling of both rectangles
  cout << "Area of Bottom Rectangle: " << lielow.area() << '\n';
  cout << "Area of Top Rectangle: " << upper.area() << '\n';

  // Scale the shared point
  fivetwop->scale(scalefactor);

  // Print the areas of the rectangles after scaling
  cout << "Area of Bottom Rectangle after scaling: " << lielow.area() << '\n';
  cout << "Area of Top Rectangle after scaling: " << upper.area() << '\n';

  return 0;
};
