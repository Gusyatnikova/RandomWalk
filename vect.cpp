#include <cmath>
#include "vect.h"

namespace VECTOR {
	const double Rad_to_deg = 45.0 / std::atan(1.0);

	void Vector::set_mag() {
		mag = std::sqrt(x * x + y * y);
	}

	void Vector::set_ang() {
		ang = x == 0 && y == 0 ?
			0.0 : std::atan2(y, x);
	}

	void Vector::set_x() {
		x = mag * cos(ang);
	}

	void Vector::set_y() {
		y = mag * sin(ang);
	}

	Vector::Vector() {
		x = y = mag = ang = 0.0;
		mode = RECT;
	}

	Vector::Vector(double n1, double n2, Mode form) {
		mode = form;
		if (form == RECT) {
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if (form == POL) {
			mag = n1;
			ang = n2 / Rad_to_deg;
			set_x();
			set_y();
		}
		else {
			std::cout << "Incorrect 3rd argument to Vector() -- ";
			std::cout << "vector set to 0\n";
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}

	void Vector::reset(double n1, double n2, Mode form) {
		mode = form;
		if (form == RECT) {
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if (form == POL) {
			mag = n1;
			ang = n2 / Rad_to_deg;
			set_x();
			set_y();
		}
		else {
			std::cout << "Incorrect 3rd argument to Vector() -- ";
			std::cout << "vector set to 0\n";
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}

	Vector::~Vector() {}
	void Vector::polar_mode() {

		mode = POL;
	}

	void Vector::rect_mode() {

		mode = RECT;
	}

	Vector Vector::operator+(const Vector& b) const {
		return Vector(x + b.x, y + b.y);
	}

	Vector Vector::operator-(const Vector& b) const {
		return Vector(x - b.x, y - b.y);
	}

	Vector Vector::operator-() const {
		return Vector(-x, -y);
	}

	Vector Vector::operator*(double n) const {
		return Vector(n * x, n * y);
	}

	Vector operator*(double a, const Vector& v) {
		return v * a;
	}

	std::ostream& operator<<(std::ostream& os, const Vector& v) {
			os << "\n(x, y) = (" << v.x << ", " << v.y << ")\n";
			os << "(m, a) = (" << v.mag << ", "
				<< v.ang * Rad_to_deg << ")";
		if (v.mode != Vector::Mode::POL && v.mode != Vector::Mode::RECT) {
			os << "Vector object mode is invalid";
		}
		return os;
	}

}