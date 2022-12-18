#include "helpers.h"
#include <iostream>
#include <array>
#include <cstdio>

bool arrayContains(const std::array<char, 10>& vals, char cellValue) {
    return (std::find(begin(vals), end(vals), cellValue) != end(vals));
}