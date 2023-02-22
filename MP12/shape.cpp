#include "shape.hpp"

/* MP 12 - Eric Roch
 * This MP demonstrates C++ classes and inheritance.
 * The beginning of this file contains class implementations for
 * various shapes, which all extend a base class, Shape.
 * At the end of the file are three functions that read a list of
 * shapes from a file and compute the maximum area and volume of
 * those shapes.
 */


//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
Shape::Shape(string name) {
    name_ = name;
}

string Shape::getName() {
	return name_;
}

double Shape::getArea()const {return 0;}
double Shape::getVolume()const {return 0;}



//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
Rectangle::Rectangle(double width, double length) : Shape("Rectangle") {
	width_ = width;
	length_ = length;
}

double Rectangle::getArea()const {
	return width_ * length_;
}
double Rectangle::getVolume()const {
	return 0;
}

Rectangle Rectangle::operator + (const Rectangle& rec) {
	double width = width_ + rec.getWidth();
	double length = length_ + rec.getLength();
	return Rectangle(width, length);
}

Rectangle Rectangle::operator - (const Rectangle& rec) {
	double width = fmax(0, width_ - rec.getWidth());
	double length = fmax(0, length_ - rec.getLength());
	return Rectangle(width, length);
}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}



//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
Circle::Circle(double radius) : Shape("Circle") {
	radius_ = radius;
}

double Circle::getArea()const {
	return M_PI * pow(radius_, 2);
}

double Circle::getVolume()const {
	return 0;
}

Circle Circle::operator + (const Circle& cir) {
	double radius = radius_ + cir.getRadius();
	return Circle(radius);
}

Circle Circle::operator - (const Circle& cir) {
	double radius = fmax(0, radius_ - cir.getRadius());
	return Circle(radius);
}

double Circle::getRadius()const{return radius_;}



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
Sphere::Sphere(double radius) : Shape("Sphere") {
	radius_ = radius;
}

double Sphere::getArea()const {
	return 4 * M_PI * pow(radius_, 2);
}

double Sphere::getVolume()const {
	return 4.0 / 3.0 * M_PI * pow(radius_, 3);
}

Sphere Sphere::operator + (const Sphere& sph) {
	double radius = radius_ + sph.getRadius();
	return Sphere(radius);
}

Sphere Sphere::operator - (const Sphere& sph) {
	double radius = fmax(0, radius_ - sph.getRadius());
	return Sphere(radius);
}

double Sphere::getRadius()const{return radius_;}



//RectPrism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
RectPrism::RectPrism(double width, double length, double height) : Shape("RectPrism") {
	length_ = length;
	width_ = width;
	height_ = height;
}

double RectPrism::getArea()const {
	return 2 * ((length_ * width_) + (length_ * height_) + (width_ * height_));
}

double RectPrism::getVolume()const {
	return length_ * width_ * height_;
}

RectPrism RectPrism::operator + (const RectPrism& rectp) {
	double width = width_ + rectp.getWidth();
	double length = length_ + rectp.getLength();
	double height = height_ + rectp.getHeight();
	return RectPrism(width, length, height);
}

RectPrism RectPrism::operator - (const RectPrism& rectp) {
	double width = fmax(0, width_ - rectp.getWidth());
	double length = fmax(0, length_ - rectp.getLength());
	double height = fmax(0, height_ - rectp.getHeight());
	return RectPrism(width, length, height);
}

double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	// create and open an input file stream with the given file name
	ifstream input_file (file_name);

	// read in the number of shapes contained in the input file
	int num_shapes;
	input_file >> num_shapes;

	// declare return vector and temp pointer for adding shapes
	vector<Shape*> shape_vector;
	Shape* newShape;

	// iterate over the input file to read in shapes
	for (int i = 0; i < num_shapes; i++) {
		string shape_name;
		input_file >> shape_name;

		// read in the appropriate data based on the name of the shape
		if (shape_name == "Rectangle") {
			double w, l;
			input_file >> w >> l;
			newShape = new Rectangle(w,l);
		}
		else if (shape_name == "Circle") {
			double r;
			input_file >> r;
			newShape = new Circle(r);
		}
		else if (shape_name == "Sphere") {
			double r;
			input_file >> r;
			newShape = new Sphere(r);
		}
		else if (shape_name == "RectPrism") {
			double w, l, h;
			input_file >> w >> l >> h;
			newShape = new RectPrism(w,l,h);
		}

		// store the newly created shape in the vector
		shape_vector.push_back(newShape);
	}

	// close the input stream and return the vector
	input_file.close();
	return shape_vector;
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;

	// iterate through the vector and update max_area if
	// the current shape's area is larger
	for (int i = 0; i < shapes.size(); i++) {
		max_area = fmax(max_area, shapes[i]->getArea());
	}

	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;

	// iterate through the vector and update max_volume if
	// the current shape's volume is larger
	for (int i = 0; i < shapes.size(); i++) {
		max_volume = fmax(max_volume, shapes[i]->getVolume());
	}

	return max_volume;
}
