#include "types.h"
#include "body_constant.h"
/**
 * Solar System
*/
const body Sun(1.9885e30, 696e6);
// Dont forget to minus the radius of the centrial body.
const body Earth(orbit(Sun, 146402450e3, 151401597e3, 7.155), 5.9722e24, 6371000);
const body Moon(orbit(Earth, 356299e3, 399029e3, 28.58), 7.342e22, 1737400);

/**
 * Kerbol System
*/
const body Kerbol(1.757e28, 261600e3);
const body Kerbin(orbit(Kerbol, 13338240.256e3, 13338240.256e3, 0.0), 5.2915158e22, 600e3);
const body Mun(orbit(Kerbin, 11400000, 11400000, 0.0), 9.7599066e20, 200e3);