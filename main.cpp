#include <iostream>

#include "OTC.h"

using namespace std;

int main(){

    auto u = Earth.get_transfer_deltaV(250000, 250000, 250000, 362600000, 1); // From LEO to Moon
    printf("%lf, %lf", u.first, u.second); // should around 3110 m/s

    return 0;
}