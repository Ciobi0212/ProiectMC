import peg;
import <iostream>;
using twixt::Peg;

int main() {
	Peg p1(1, 2, "red");
	p1.setColor("red");
	std::cout << p1.getColor();

	
	
}