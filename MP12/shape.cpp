#include "shape.hpp"


//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
Shape::Shape(string name) {
    name_ = name;
}

string Shape::getName() {
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
	return width_*length_;
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
	double n_width = fmax(0, width_ - rec.getWidth());
	double n_length = fmax(0, length_ - rec.getLength());

	return Rectangle(n_width, n_length);
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
	return pow(radius_, 2) * M_PI;
}

double Circle::getVolume()const {
	return 0;
}

Circle Circle::operator + (const Circle& cir) {
	double radius = radius_ + cir.getRadius();
	return Circle(radius);
}

Circle Circle::operator - (const Circle& cir) {
	double n_width = fmax(0, radius_ - cir.getRadius());
	return Circle(n_width);
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
	return 4/3 * M_PI * pow(radius_, 3);
}

Sphere Sphere::operator + (const Sphere& sph) {
	double radius = radius_ + sph.getRadius();
	return Sphere(radius);
}

Sphere Sphere::operator - (const Sphere& sph) {
	double n_width = fmax(0, radius_ - sph.getRadius());
	return Sphere(n_width);
}

double Sphere::getRadius()const{return radius_;}



//RectPrism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
RectPrism::RectPrism(double width, double length, double height) : Shape("RectPrism") {
}

double RectPrism::getArea()const {

	return 2 * ((width_ * length_) * (width_ * height_) * (length_ * height_));

}

double RectPrism::getVolume()const {

	return width_ * length_ * height_;

}

RectPrism RectPrism::operator + (const RectPrism& rectp) {
	double width = width_ + rectp.getWidth();
	double length = length_ + rectp.getLength();
	double height = height_ + rectp.getHeight();

	return RectPrism(width, length, height);
}

RectPrism RectPrism::operator - (const RectPrism& rectp) {
	double n_width = fmax(0, width_ - rectp.getWidth());
	double n_length = fmax(0, length_ - rectp.getLength());
	double n_height = fmax(0, length_ - rectp.getHeight());

	return RectPrism(n_width, n_length, n_height);
}

double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){

	double max_area = 0;

	for (int i=0; i < shapes.size(); i++){
		max_area = fmax(shapes[i]->getArea(), max_area);
	}

	return max_area;

}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
		
	double max_volume = 0;

	for (int i=0; i < shapes.size(); i++){
		max_volume = fmax(shapes[i]->getVolume(), max_volume);
	}

	return max_volume;

}
