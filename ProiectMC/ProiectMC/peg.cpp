module peg;

using twixt::Peg;

Peg::Peg() = default;

Peg::Peg(uint16_t x, uint16_t y, const std::string& color) : m_x{ x }, m_y{ y }, m_color{color} {}

Peg::~Peg() = default;

uint16_t Peg::getX() const {
	return m_x;
}

uint16_t Peg::getY() const {
	return m_y;
}

std::string Peg::getColor() const {
	return m_color;
}

uint16_t Peg::setX(uint16_t x) {
	m_x = x;
	return m_x;
}

uint16_t Peg::setY(uint16_t y) {
	m_y = y;
	return m_y;
}

std::string Peg::setColor(const std::string& color) {
	m_color = color;
	return m_color;
}

