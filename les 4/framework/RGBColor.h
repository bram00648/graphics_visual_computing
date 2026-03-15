#pragma once

namespace cg {
	class RGBColor
	{
	private:
		unsigned char m_r;
		unsigned char m_g;
		unsigned char m_b;

	public:
		explicit RGBColor(unsigned int r = 255, unsigned int g = 255, unsigned b = 255) : m_r(r), m_g(g), m_b(b) {};

        unsigned char r() const {return m_r; };
		unsigned char g() const {return m_g; };
		unsigned char b() const {return m_b; };

	};
}


