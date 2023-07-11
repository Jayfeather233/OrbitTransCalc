#include "types.h"

body::body(const orbit &o, const double mass, const double radius)
    : orb(o), mass(mass), radius(radius)
{
}
body::body(const double mass, const double radius)
    : orb(orbit(*this, 0)), mass(mass), radius(radius)
{
}

bool body::operator==(const body &o) const
{
    return this == &o;
}