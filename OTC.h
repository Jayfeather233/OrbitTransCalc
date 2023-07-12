#pragma once

#include "constant.h"
#include "types.h"

#include <cstdio>

void show_result(const dv_result &result)
{
    printf("first ignition at %s\n", result.first ? "pe" : "ap");
    printf("first ignition dV: %.3lf, second dV: %.3lf\n", result.second.first,
           result.second.second);
}

void show_result(const orbit &o1, const orbit &o2, const dv_result &result,
                 bool pe2pe = true, bool show_header = true)
{
    if (show_header) {
        printf("+---------+---------+---------+---------+\n");
        printf("|   pe    |   ap    |   inc   |   dV    |\n");
        printf("+---------+---------+---------+---------+\n");
        printf("|%-8.3e|%-8.3e|%-8.3e|   0.0   |\n", o1.get_pe(), o1.get_ap(),
               o1.get_inc());
        printf("+---------+---------+---------+---------+\n");
    }
    if (std::abs(result.second.first) >= 0.1) {
        if (pe2pe) {
            if (result.first) {
                printf("|%-8.3e|%-8.3e|%-8.3e|%-8.3e|\n", o1.get_pe(),
                       o2.get_ap(), o1.get_inc(), result.second.first);
            }
            else {
                printf("|%-8.3e|%-8.3e|%-8.3e|%-8.3e|\n", o1.get_ap(),
                       o2.get_pe(), o1.get_inc(), result.second.first);
            }
        }
        else {
            if (result.first) {
                printf("|%-8.3e|%-8.3e|%-8.3e|%-8.3e|\n", o1.get_pe(),
                       o2.get_pe(), o1.get_inc(), result.second.first);
            }
            else {
                printf("|%-8.3e|%-8.3e|%-8.3e|%-8.3e|\n", o1.get_ap(),
                       o2.get_ap(), o1.get_inc(), result.second.first);
            }
        }
        printf("+---------+---------+---------+---------+\n");
    }
    if (std::abs(result.second.second) >= 0.1) {
        printf("|%-8.3e|%-8.3e|%-8.3e|%-8.3e|\n", o2.get_pe(), o2.get_ap(),
               o2.get_inc(), result.second.second);
        printf("+---------+---------+---------+---------+\n");
    }
}