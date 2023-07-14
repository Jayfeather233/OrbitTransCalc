#include "types.h"

body::body(const orbit &o, const long double mass, const long double radius)
    : orb(o), mass(mass), radius(radius)
{
}
body::body(const long double mass, const long double radius)
    : orb(orbit(*this, 0)), mass(mass), radius(radius)
{
}

bool body::operator==(const body &o) const { return this == &o; }

double body::get_after_escape_velocity(const double h, const double v) const
{
    long double Ek = this->get_E_g(h) + (long double)0.5 * v * v;
    return Ek < 0 ? 0 : std::sqrt(2 * Ek);
}