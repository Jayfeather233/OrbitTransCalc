#include <iostream>

#include "OTC.h"

using namespace std;

int notmain(){
    // orbit i1 = orbit(Earth, 200000, 200000, 19.61);
    // orbit i2 = orbit(Earth, 1000000, 4500000, 19.61);
    // dv_result result1 = i1.get_transfer_deltaV(i2);
    // show_result(i1,i2, result1);
    
    // orbit i1 = orbit(Earth, 200000, 200000, Moon.get_orbit().get_inc());
    // double s1 = i1.get_velocity(false)+3200;
    // orbit i2 = orbit::create_orbit_V(Earth, 200000, s1, i1.get_inc());
    // double s2 = (double)(std::sqrt(2*(0.0-Moon.get_E_g(20000) + i2.get_E() - Earth.get_E_g(Moon.get_orbit().get_pe() - Moon.get_radius()))));
    // s2 -= Moon.get_orbit().get_velocity();
    // printf("%lf\n", s2);
    // printf("%lf\n", orbit(Moon, 20000, 20000, 0).get_velocity());
    // orbit i3 = orbit::create_orbit_V(Moon, 20000, s2 - 300, 0);
    // printf("%lf %lf\n", i3.get_ap(), i3.get_pe());

    // orbit i1 = orbit(Earth, 200000, 200000, 19.61);
    // orbit i2 = orbit(Earth, 39238000, 600000, 19.61);
    // dv_result result = i1.get_transfer_deltaV(i2);
    // show_result(i1,i2, result);

    // orbit i2 = orbit::create_orbit_T(Earth, 500000, 43082, 63.4); // Molniya orbit
    // printf("%lf %lf\n", i2.get_pe(), i2.get_ap());
    // printf("%lf\n",i2.get_Ecc());
}

int main(){

    // orbit i1 = orbit(Earth, 210000, 210000, 38);
    // //orbit i2 = orbit::create_orbit_E(Earth, 210000, 0.04, 19.61);
    // orbit i2 = orbit(Earth, 210000, 860000, 38);
    // orbit i3 = orbit(Earth, 860000, 4600000, 38);
    // dv_result result1 = i1.get_transfer_deltaV(i2);
    // dv_result result2 = i2.get_transfer_deltaV(i3, false);
    // show_result(i1, i2, result1, true, true);
    // show_result(i2, i3, result2, false, false);

    orbit GEO = orbit::create_rorbit_T(Earth, 23*3600+56*60+4);
    printf("%.3lf", GEO.get_ap());

    orbit i1 = orbit(Earth, 210000, 210000, 63.4);
    orbit i2 = orbit::create_orbit_T(Earth, 597000, 11*3600+58*60+2, 63.4);
    printf("pe:%8.3e ap:%8.3e ecc:%8.3e\n", i2.get_pe(), i2.get_ap(), i2.get_Ecc());
    dv_result result1 = i1.get_transfer_deltaV(i2);
    show_result(i1, i2, result1);

    // speed TEST //
    // orbit o = orbit::create_orbit_V(Earth, 35786151, 3074.924491, 0);
    // printf("%lf %lf\n", o.get_pe(), o.get_ap());

    // orbit i1 = orbit(Earth, 200000, 200000, 0);
    // orbit i2 = orbit(Earth, 200000, Moon.get_orbit().get_pe(), Moon.get_orbit().get_inc());
    // dv_result u = i1.get_transfer_deltaV(i2);
    // show_result(i1, i2, u);
    // orbit i1 = orbit(Earth, 200000, 200000, 0);
    // orbit i2 = orbit(Earth, 200000, Moon.get_orbit().get_pe(), Moon.get_orbit().get_inc());
    // dv_result u = i1.get_transfer_deltaV(i2);
    // show_result(i1, i2, u);

    // Transfer TEST //
    orbit i1 = orbit(Earth, 200000, 200000, 19.61); // 200km 19.61° LEO at Wenchang
    orbit i2 = orbit(Earth, 200000, 35786151, 17.5);
    orbit i3 = orbit(Earth, 35786151);              // GEO
    dv_result result1 = i1.get_transfer_deltaV(i2);  // calculate dV
    dv_result result2 = i2.get_transfer_deltaV(i3);  // calculate dV
    show_result(i1, i3, result1, true, true);
    show_result(i2, i3, result2, true, false);
    printf("total: %-8.3e\n", result1.second.first + result1.second.second + result2.second.first + result2.second.second);

    // simpler Transfer TEST //
    orbit i4 = orbit(Earth, 210000, 210000, 45); // 200km 19.61° LEO at Wenchang
    orbit i5 = orbit(Earth, 210000, 1000000, 45);
    orbit i6 = orbit(Earth, 1000000, 5000000, 45);
    dv_result result3 = i4.get_transfer_deltaV(i5);  // calculate dV
    dv_result result4 = i5.get_transfer_deltaV(i6, false);  // calculate dV
    show_result(i4, i5, result3, true, true);
    show_result(i5, i6, result4, false, false);
    printf("total: %-8.3e\n", result3.second.first + result3.second.second);

    // planet transfer test. Fly-by. Does not count inclination //
    // orbit i6 = orbit(Earth, 300000, 300000, 0); 
    // dv_result result4 = i6.get_transfer_deltaV(Mars.get_orbit());
    // printf("Mars:\n");
    // show_result(result4); // should around 3.6k, calculate 3.7k (why?)
    // printf("\n");
    
    // dv_result result5 = i6.get_transfer_deltaV(Neptune.get_orbit());
    // printf("Neptune:\n");
    // show_result(result5); // should around 8.2k, calculate 8.15k

    return 0;
}