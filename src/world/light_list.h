#ifndef LIGHT_LIST_H
#define LIGHT_LIST_H

#include <memory>
#include <vector>

#include "light.h"

using std::shared_ptr;
using std::vector;

class LightList {
public:
    void add(shared_ptr<Light> light) { lights.push_back(light); }
    void clear() { lights.clear(); }
    vector<shared_ptr<Light>> lights;
};

#endif