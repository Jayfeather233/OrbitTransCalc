#pragma once

#include "uni_constant.h"

#include <cmath>

class body {
private:
    double mass;
    double radius;

public:
    body(double mass) : mass(mass) {}
    body(double mass, double radius) : mass(mass), radius(radius) {}
    double get_mass() const { return mass; }
    double get_radius() const { return radius; }

    /**
     * get orbiting velocity.
     * radius starts from ground.
     */
    double get_velocity(double orbit_radius) const
    {
        return sqrt(2 * (get_E(orbit_radius) - get_E_g(orbit_radius)));
    }

    /**
     * get orbiting velocity.
     * If at_pe == True, then return the velocity at pe.
     * Otherwise return it at ap.
     * pe, ap starts from ground.
     */
    double get_velocity(double pe, double ap, bool at_pe) const
    {
        return sqrt(2 * (get_E(pe, ap) - get_E_g(at_pe ? pe : ap)));
    }

    /**
     * Used to get the Gravitational Potential Energy
     * Here `height` means height from ground.
     * assume the spacecraft has mass 1kg
     */
    double get_E_g(double height) const
    {
        return -G * mass / (height + this->radius);
    }

    /**
     * Used to get the Mechanical energy
     * pe, ap starts from ground.
     * assume the spacecraft has mass 1kg
     */
    double get_E(double pe, double ap) const
    {
        return -G * mass / (pe + ap + 2 * this->radius);
    }

    /**
     * Used to get the Mechanical energy
     * pe, ap starts from ground.
     * assume the spacecraft has mass 1kg
     */
    double get_E(double orbit_radius) const
    {
        return -G * mass / (2 * orbit_radius + 2 * this->radius);
    }

    /**
     * Calculate the transfer deltaV. Using Hohmann Transfer.
    */
    std::pair<double, double> get_transfer_deltaV(double from_radius,
                                                  double to_radius) const
    {
        return std::make_pair(
            get_velocity(from_radius, to_radius, 1) - get_velocity(from_radius),
            get_velocity(to_radius) - get_velocity(from_radius, to_radius, 0));
    }

    /**
     * Calculate the transfer deltaV. Using Hohmann Transfer.
     * If pe2pe == True, then it will act like: 1. from_ap -> to_pe -> to_ap
     *                                          2. from_pe -> to_ap -> to_pe
     * Else: 1. from_ap -> to_ap -> to_pe
     *       2. from_pe -> to_pe -> to_ap
    */
    std::pair<double, double> get_transfer_deltaV(double from_pe, double from_ap,
                                                  double to_pe, double to_ap, bool pe2pe) const
    {
        if(pe2pe){
            std::pair<double, double> v1(get_velocity(to_pe, from_ap, 0)-get_velocity(from_pe,from_ap,0), get_velocity(to_pe, to_ap, 1) - get_velocity(to_pe, from_ap, 1));
            std::pair<double, double> v2(get_velocity(from_pe, to_ap, 1)-get_velocity(from_pe,from_ap,1), get_velocity(to_pe, to_ap, 0) - get_velocity(from_pe, to_ap, 0));
            double dv1 = v1.first+v1.second;
            double dv2 = v2.first+v2.second;
            printf("deltaV1: %lf, deltaV2: %lf\n", dv1,dv2);
            return dv1 < dv2 ? v1 : v2;
        } else {
            std::pair<double, double> v1(get_velocity(to_ap, from_ap, 0)-get_velocity(from_pe,from_ap,0), get_velocity(to_ap, to_pe, 1) - get_velocity(to_ap, from_ap, 1));
            std::pair<double, double> v2(get_velocity(from_pe, to_pe, 1)-get_velocity(from_pe,from_ap,1), get_velocity(to_ap, to_pe, 0) - get_velocity(from_pe, to_pe, 0));
            double dv1 = v1.first+v1.second;
            double dv2 = v2.first+v2.second;
            printf("deltaV1: %lf, deltaV2: %lf\n", dv1,dv2);
            return dv1 < dv2 ? v1 : v2;
        }
    }
};