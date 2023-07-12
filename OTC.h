#pragma once

#include "types.h"
#include "constant.h"

#include <cstdio>

void show_result(const dv_result &result){
    printf("first ignition at %s\n", result.first ? "pe" : "ap");
    printf("first ignition dV: %.3lf, second dV: %.3lf\n", result.second.first, result.second.second);
}

void show_result(const orbit &o1, const orbit &o2, const dv_result &result, bool pe2pe = true){
    printf("+---------+---------+---------+---------+\n");
    printf("|   pe    |   ap    |   inc   |   dV    |\n");
    printf("+---------+---------+---------+---------+\n");
    printf("|%-8.3e|%-8.3e|%-8.3e|   0.0   |\n", o1.get_pe(), o1.get_ap(), o1.get_inc());
    printf("+---------+---------+---------+---------+\n");
    if(pe2pe){
        if(result.first){
            printf("|%-8.3e|%-8.3e|%-8.3e|%-8.3e|\n", o1.get_pe(), o2.get_ap(), o1.get_inc(), result.second.first);
        } else {
            printf("|%-8.3e|%-8.3e|%-8.3e|%-8.3e|\n", o1.get_ap(), o2.get_pe(), o1.get_inc(), result.second.first);
        }
    } else {
        if(result.first){
            printf("|%-8.3e|%-8.3e|%-8.3e|%-8.3e|\n", o1.get_pe(), o2.get_pe(), o1.get_inc(), result.second.first);
        } else {
            printf("|%-8.3e|%-8.3e|%-8.3e|%-8.3e|\n", o1.get_ap(), o2.get_ap(), o1.get_inc(), result.second.first);
        }
    }
    printf("+---------+---------+---------+---------+\n");
    printf("|%-8.3e|%-8.3e|%-8.3e|%-8.3e|\n", o2.get_pe(), o2.get_ap(), o2.get_inc(), result.second.second);
    printf("+---------+---------+---------+---------+\n");
}