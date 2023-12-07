#pragma once

#include <vector>
#include <unordered_map>

struct Coordinates{
    double latitude;
    double longitude;
};

struct Route{
    std::vector<string> stops_;
    bool is_circled = false;
};

using RouteBase = std::unordered_map<std::string, Route>;
using StopBase = std::unordered_map<std::string, Coordinates>;

class RouteDatabase{


private:
    RouteBase routebase_;
    StopBase stopbase_;
}
