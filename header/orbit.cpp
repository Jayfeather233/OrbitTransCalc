#include "types.h"

#include <algorithm>
#include <cmath>

/**
 * inc: Inclination
 */
orbit::orbit(const body &c_body, const double pe, const double ap,
             const double inc)
    : centrial_body(c_body), pe(pe), ap(ap)
{
    this->inc = fmod(inc + 180, 360);
    this->inc = (this->inc < 0 ? this->inc + 360 : this->inc) - 180;
}
orbit::orbit(const body &c_body, const double radius)
    : centrial_body(c_body), pe(radius), ap(radius), inc(0)
{
}

/**
 * get orbiting velocity.
 * If at_pe == True, then return the velocity at pe.
 * Otherwise return it at ap.
 * pe, ap starts from ground.
 */
double orbit::get_velocity(bool at_pe) const
{
    return std::sqrt(2 * (get_E() - centrial_body.get_E_g(at_pe ? pe : ap)));
}

/**
 * Used to get the Mechanical energy
 * pe, ap starts from ground.
 * assume the spacecraft has mass 1kg
 */
double orbit::get_E() const
{
    return -G * centrial_body.get_mass() /
           (pe + ap + 2 * centrial_body.get_radius());
}

double vector_distance(const double v1, const double d1, const double v2, const double d2){
    return std::sqrt(v1*v1 + v2*v2 - 2.0*v1*v2*cos(std::abs(d1-d2)/180.0*M_PI));
}

/**
 * Calculate the transfer deltaV. Using Hohmann Transfer.
 * Inclination changes in second ignition.
 * If pe2pe == True, then it will act like: 0. from_ap -> to_pe -> to_ap
 *                                          1. from_pe -> to_ap -> to_pe
 * Else: 0. from_ap -> to_ap -> to_pe
 *       1. from_pe -> to_pe -> to_ap
 */
dv_result orbit::get_transfer_deltaV(const orbit &o, bool pe2pe) const
{
    dv_result ans1, ans2;
    if(this->centrial_body == o.centrial_body){
        if(pe2pe){
            orbit transfer_o1 = orbit(this->centrial_body, o.pe, this->ap, this->inc);
            orbit transfer_o2 = orbit(this->centrial_body, this->pe, o.ap, this->inc);
            ans1 = std::make_pair(0, std::make_pair(std::abs(transfer_o1.get_velocity(0) - this->get_velocity(0)),
                                    vector_distance(transfer_o1.get_velocity(1), transfer_o1.get_inc(), o.get_velocity(1), o.get_inc())));
            ans2 = std::make_pair(1, std::make_pair(std::abs(transfer_o2.get_velocity(1) - this->get_velocity(1)),
                                    vector_distance(transfer_o2.get_velocity(0), transfer_o2.get_inc(), o.get_velocity(0), o.get_inc())));
        } else {
            orbit transfer_o1 = orbit(this->centrial_body, this->ap, o.ap, this->inc);
            orbit transfer_o2 = orbit(this->centrial_body, this->pe, o.pe, this->inc);
            ans1 = std::make_pair(0, std::make_pair(std::abs(transfer_o1.get_velocity(1) - this->get_velocity(0)),
                                    vector_distance(transfer_o1.get_velocity(0), transfer_o1.get_inc(), o.get_velocity(0), o.get_inc())));
            ans2 = std::make_pair(1, std::make_pair(std::abs(transfer_o2.get_velocity(1) - this->get_velocity(1)),
                                    vector_distance(transfer_o2.get_velocity(0), -transfer_o2.get_inc(), o.get_velocity(1), o.get_inc())));
        }
    } else {
        // Not supported yet.
    }
    double v1 = ans1.second.first + ans1.second.second;
    double v2 = ans2.second.first + ans2.second.second;
    return v1 > v2 ? ans2 : ans1;
    // if (pe2pe) {
    //     std::pair<double, double> v1(get_velocity(to_pe, from_ap, 0) -
    //                                      get_velocity(from_pe, from_ap, 0),
    //                                  get_velocity(to_pe, to_ap, 1) -
    //                                      get_velocity(to_pe, from_ap, 1));
    //     std::pair<double, double> v2(get_velocity(from_pe, to_ap, 1) -
    //                                      get_velocity(from_pe, from_ap, 1),
    //                                  get_velocity(to_pe, to_ap, 0) -
    //                                      get_velocity(from_pe, to_ap, 0));
    //     double dv1 = std::abs(v1.first) + std::abs(v1.second);
    //     double dv2 = std::abs(v2.first) + std::abs(v2.second);
    //     return dv1 < dv2 ? std::make_pair(0, v1) : std::make_pair(1, v2);
    // }
    // else {
    //     std::pair<double, double> v1(get_velocity(to_ap, from_ap, 0) -
    //                                      get_velocity(from_pe, from_ap, 0),
    //                                  get_velocity(to_ap, to_pe, 1) -
    //                                      get_velocity(to_ap, from_ap, 1));
    //     std::pair<double, double> v2(get_velocity(from_pe, to_pe, 1) -
    //                                      get_velocity(from_pe, from_ap, 1),
    //                                  get_velocity(to_ap, to_pe, 0) -
    //                                      get_velocity(from_pe, to_pe, 0));
    //     double dv1 = std::abs(v1.first) + std::abs(v1.second);
    //     double dv2 = std::abs(v2.first) + std::abs(v2.second);
    //     return dv1 < dv2 ? std::make_pair(0, v1) : std::make_pair(1, v2);
    // }
}

orbit orbit::create_orbit_e(const body &c_body, const double pe, const double e,
                            const double inc)
{
    double ap = (1 + e) / (1 - e) * pe;
    return ap > pe ? orbit(c_body, pe, ap, inc) : orbit(c_body, ap, pe, -inc);
}

orbit orbit::create_orbit_v(const body &c_body, const double h, const double v,
                            const double inc)
{
    double h2 = -G * c_body.get_mass() / (c_body.get_E_g(h) + 1.0 / 2 * v * v) -
                h - 2 * c_body.get_radius();
    return (h2 > h) ? orbit(c_body, h, h2, inc) : orbit(c_body, h2, h, -inc);
}