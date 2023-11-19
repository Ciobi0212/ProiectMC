#pragma once
#include <iostream>;
#include <string>;


namespace twixt {
	class Peg {
	public:
		Peg();
		Peg(uint16_t x, uint16_t y, const std::string& color);
		~Peg();
		uint16_t getX() const;
		uint16_t getY() const;
		std::string getColor() const;
		uint16_t setX(uint16_t x);
		uint16_t setY(uint16_t y);
		std::string setColor(const std::string& color);


	private:
		uint16_t m_x;
		uint16_t m_y;
		std::string m_color;
	};
}