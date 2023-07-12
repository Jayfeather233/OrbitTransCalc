#include <iostream>

#include "OTC.h"

using namespace std;

int main(){

    // speed TEST //
    // orbit o = orbit::create_orbit_v(Earth, 35786151, 3074.924491, 0);
    // printf("%lf %lf\n", o.get_pe(), o.get_ap());

    // orbit p = orbit(Earth, 35786151);
    // printf("%lf\n", p.get_velocity(0));
    // speed END //

    // Transfer TEST //
    orbit i1 = orbit(Earth, 200000, 200000, 19.61); // 200km 19.61° LEO at Wenchang
    orbit i2 = orbit(Earth, 200000, 35786151, 17.08);
    orbit i3 = orbit(Earth, 35786151);              // GEO
    dv_result result1 = i1.get_transfer_deltaV(i2);  // calculate dV
    dv_result result2 = i2.get_transfer_deltaV(i3);  // calculate dV
    show_result(i1, i2, result1, true, true);
    show_result(i2, i3, result2, true, false);
    printf("------------------\n");

    // simpler Transfer TEST //
    orbit i4 = orbit(Earth, 200000, 200000, 19.61); // 200km 19.61° LEO at Wenchang
    orbit i5 = orbit(Earth, 35786151);              // GEO
    dv_result result3 = i4.get_transfer_deltaV(i5);  // calculate dV
    show_result(i4, i5, result3);

    return 0;
}