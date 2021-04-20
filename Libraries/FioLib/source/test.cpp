#include <iostream>

#include "deserializers.h"
#include "serializers.h"

namespace {
using namespace fio;

void test_1() {
    fluid::Point p;
    p.value = 22;
    saveToFile("myPoint.json", serializePoint(p));
}

void test_2() {
    fluid::Point p = deserializePoint(loadFromFile("myPoint.json"));
    std::cout << p.value << ' ' << p.isInArea;
}
}

int main() {
    test_1();
    test_2();
}
