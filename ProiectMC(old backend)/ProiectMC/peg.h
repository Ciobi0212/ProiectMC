#pragma once
#include <iostream>;
#include <string>;



namespace twixt {
	enum class Color { RED,RED_TRANSPARENT, BLUE, BLUE_TRANSPARENT, NONE };
	using Position = std::pair<size_t, size_t>;
	struct PositionHash {
		std::size_t operator()(const Position& pos) const {
			return std::hash<std::size_t>()(pos.first) ^ std::hash<std::size_t>()(pos.second);
		}
	};
	
	class Peg {
	public:
		Peg();
		Peg(size_t x, size_t y, Color color);
		~Peg();
		size_t getX() const;
		size_t getY() const;
		Color getColor() const;
		void setX(uint16_t x);
		void setY(uint16_t y);
		void setColor(Color color);
		bool operator==(const Peg& peg) const;
		Position getPosition() const;


	private:
		size_t m_x;
		size_t m_y;
		Color m_color;
	};
}