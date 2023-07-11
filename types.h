#pragma once

#include <cmath>

const double G = 6.6743015e-11;

class body;
class orbit;

typedef std::pair<int, std::pair<double, double>> dv_result;

class body {
private:
    const double mass;
    const double radius;
    const orbit &orb;

public:
    body(const orbit &o, const double mass, const double radius);
    body(const double mass, const double radius);

    inline const double get_mass() const { return mass; }
    inline const double get_radius() const { return radius; }
    inline const orbit &get_orbit() const { return orb; }

    /**
     * Used to get the Gravitational Potential Energy
     * Here `height` means height from ground.
     * assume the spacecraft has mass 1kg
     */
    inline double get_E_g(double height) const
    {
        return -G * mass / (height + this->radius);
    }

    bool operator==(const body &o) const;
};

class orbit {
private:
    const body &centrial_body;
    double pe;  // Periapsis
    double ap;  // Apoapsis
    double inc; // Inclination. It's position must be at ap. Cuz' I don't
                // what it to be messy

public:
    /**
     * inc: Inclination
     */
    orbit(const body &c_body, const double pe, const double ap,
          const double inc = 0);
    orbit(const body &c_body, const double radius);

    /**
     * e: Eccentricity
     * Create an orbit from periapsis and eccentricity
     */
    static orbit create_orbit_e(const body &c_body, const double pe,
                                const double e, const double inc = 0);

    /**
     * Create an orbit from height and velocity
     */
    static orbit create_orbit_v(const body &c_body, const double h,
                                const double v, const double inc = 0);

    inline double get_pe() const { return pe; }
    inline double get_ap() const { return ap; }
    inline double get_inc() const { return inc; }

    /**
     * get orbiting velocity.
     * If at_pe == True, then return the velocity at pe.
     * Otherwise return it at ap.
     * pe, ap starts from ground.
     */
    double get_velocity(bool at_pe) const;

    /**
     * Used to get the Mechanical energy
     * pe, ap starts from ground.
     * assume the spacecraft has mass 1kg
     */
    double get_E() const;

    /**
     * Calculate the transfer deltaV. Using Hohmann Transfer.
     * If pe2pe == True, then it will act like: 1. from_ap -> to_pe -> to_ap
     *                                          2. from_pe -> to_ap -> to_pe
     * Else: 1. from_ap -> to_ap -> to_pe
     *       2. from_pe -> to_pe -> to_ap
     */
    dv_result get_transfer_deltaV(const orbit &o, bool pe2pe = 1) const;
};