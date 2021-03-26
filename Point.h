#include <string>

class Point{
public:
	int x, y;
	
	Point(){
		x = -1, y = -1;
	}
	
	Point(int newX, int newY) {
		x = newX;
		y = newY;
	}
	
	std::string print() {
		std::string temp = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		return temp;
	}
};

class Line{
public:
	Point start, end;
	
	Line(){
		start = end = Point(-1, -1);
	}
	Line(Point newStart, Point newEnd){
		start = newStart;
		end = newEnd;
	}
	Line(int startX, int startY, int endX, int endY){
		start = Point(startX, startY);
		end = Point(endX, endY);
	}
	
	bool operator==(const Line& otherLine){
		if (otherLine.start.x == start.x 
			&& otherLine.start.y == start.y
			&& otherLine.end.x == end.x
			&& otherLine.end.y == end.y) {
			return true;
			}
		else {
			return false;
		}
	}
	
	bool operator!=(const Line& otherLine){
		if (otherLine.start.x != start.x 
			|| otherLine.start.y != start.y
			|| otherLine.end.x != end.x
			|| otherLine.end.y != end.y) {
			return true;
			}
		else {
			return false;
		}
	}
	
	std::string print(){
		return start.print() + " to " + end.print();
	}
};