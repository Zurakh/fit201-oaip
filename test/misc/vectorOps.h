#pragma once

#include <vector>

std::vector<int> operator+(const std::vector<int>& vec1, const std::vector<int>& vec2);

bool operator==(const std::vector<int>& vec1, const std::vector<int>& vec2);

bool vectorEachValEq(const std::vector<int>& vec, int val);
