#pragma once
#include <iostream>;
#include <string>;


namespace twixt {
	enum class Color { RED, BLUE, NONE };
	
	class Peg {
	public:
		Peg();
		Peg(size_t x, size_t y, Color color);
		~Peg();
		uint16_t getX() const;
		uint16_t getY() const;
		Color getColor() const;
		void setX(uint16_t x);
		void setY(uint16_t y);
		void setColor(Color color);


	private:
		size_t m_x;
		size_t m_y;
		Color m_color;
	};
}