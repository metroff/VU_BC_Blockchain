#include "time.hpp"

string serializeTimePoint( const time_point& time, const string& format)
{
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    std::tm tm = *std::gmtime(&tt); //GMT (UTC)
    //std::tm tm = *std::localtime(&tt); //Locale time-zone, usually UTC by default.
    std::stringstream ss;
    ss << std::put_time( &tm, format.c_str() );
    return ss.str();
}

string get_timestamp_now() {
    time_point input = std::chrono::system_clock::now();
    return serializeTimePoint(input, "%Y-%m-%d %H:%M:%S");
}