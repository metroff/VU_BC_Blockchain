#pragma once
#include "myLib.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>

using time_point = std::chrono::system_clock::time_point;
string serializeTimePoint( const time_point&, const string&);
string get_timestamp_now();