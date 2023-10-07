/*
Name: Arushi Sadam
UT EID: ars7724
TACC Username: a2097855
*/

//Purpose: use classes and pointers to make a dynamic rectangle.

//using standard input and output streams
#include <iostream>
using std::cin;
using std::cout;

// for use of shared pointers:
# include <memory>
using std::shared_ptr;
using std::make_shared;

//Point class: used to initialize Rectangle's corner points + for the scale function
class Point {
private:
  float x,y; 
public:
  // uses an input scaling factor and scales the x and y coordinates of the point by the factor
  void scale (float factor)
  {
    x = factor*x;
    y = factor*y;
  };
  Point(float ix,float iy) { x = ix; y = iy; }; // initialize Point with input parameters (ix, iy)

  // define get_x and get_y functions to acess the Point's x and y coordinates
  float get_x() const { return x; }
  float get_y() const { return y; }
};

// class that uses pointers to the bottom left (bl) and top right (tr) to build a dynamic rectangle
// has function to compute the area of the rectangle
class DynRectangle{
private:
  shared_ptr<Point> bl, tr; // pointers to Points bl and tr
public:
  // initialize the Dynamic rectangle with the input pointer parameters (ibl, itr)
  DynRectangle(shared_ptr<Point> ibl, shared_ptr<Point> itr)
    : bl(ibl), tr(itr) {};
  
  // computes the area of the rectangle
  float area() {
    float w = tr->get_x() - bl->get_x(); // get the x coordinates of the top right and bottom left points. The positive difference between x coordinates is the width of the rectangle.
    float h = tr->get_y() - bl->get_y(); // get the y coordinates of the top right and bottom left points. The positive difference between y coordinates is the height, h, of the rectangle.
    return w * h; // area rectangle is width*height
  };
};

//initializes pointers to to Points, bottom left and top right. Finds area of a rectangle, scales each side of the rectangle by 2, then computes area again.
int main()
{
  // make two pointers to the Points (0,0) and (5,2)
  auto origin = make_shared<Point> (0,0); // bottom left or bl point
  auto fivetwo = make_shared<Point>(5,2); // top right or tr point
  DynRectangle lielow(origin, fivetwo); // create a rectangle with the specified bl and tr points; lielow is arbitary name for the rectantle

  cout << "Area: " << lielow.area() << "\n"; // compute area of lielow
  fivetwo->scale(2); // scale Point (5,2) to be twice as far (2 * x value + 2 * y value). Scale factor is 2. Call function scale from Point class.
  cout << "Area: " << lielow.area() << "\n"; // compute area of new lielow rectangle, area should be 4 times as previous area

  return 0;
};
