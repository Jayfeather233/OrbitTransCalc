#include "types.h"
#include "celestial_bodies.h"

const double AU = 1.495978707e11;
/**
 * Solar System
*/
const body Sun(1.9885e30, 696e6);
// Dont forget to minus the radius of the centrial body.
const body Earth(orbit(Sun, 146402450e3, 151401597e3, 7.155), 5.9722e24, 6371000);
const body Moon(orbit(Earth, 356299e3, 399029e3, 5.145), 7.342e22, 1737400);
const body Mars(orbit(Sun, 2.0592e11, 2.4853e11, 5.6521), 6.4185e23, 3389.5e3);
const body Ceres(orbit(Sun, 2.55*AU, 2.98*AU, 9.20), 9.38392e20, 964e3);
const body Venus(orbit(Sun, 107477e6, 108939e6, 3.86), 4.8676e24, 6051.8e3);
const body Neptune(orbit(Sun, 4.46e12, 4.54e12, 6.43), 1.02413e26, 24764e3);

/**
 * Kerbol System
*/
const body Kerbol(1.757e28, 261600e3);
const body Kerbin(orbit(Kerbol, 13338240.256e3, 13338240.256e3, 0.0), 5.2915158e22, 600e3);
const body Mun(orbit(Kerbin, 11400000, 11400000, 0.0), 9.7599066e20, 200e3);