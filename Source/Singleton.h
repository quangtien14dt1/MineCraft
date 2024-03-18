#pragma once
#include <string>

struct SingleTon {
    SingleTon() = default;
    SingleTon(const SingleTon&) = delete;
    SingleTon& operator=(const SingleTon&) = delete;
};