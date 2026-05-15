#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <random>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace Utils {

    static std::string generate_alphanumeric(size_t length) {
        const std::string alphabet = 
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        
        static std::random_device rd; 
        static std::mt19937 gen(rd());
        
        std::uniform_int_distribution<> dist(0, static_cast<int>(alphabet.size() - 1));
        
        std::string result;
        result.reserve(length);
        for (size_t i = 0; i < length; ++i) {
            result += alphabet[dist(gen)];
        }

        return result;
    }
    
    static std::chrono::system_clock::time_point get_current_time() {
        return std::chrono::system_clock::now();
    }

    static std::string get_formatted_date_time_from_utc(std::chrono::system_clock::time_point time) {
        std::time_t t = std::chrono::system_clock::to_time_t(time);
        std::tm tm{};
    #if defined(_WIN32)
        gmtime_s(&tm, &t);
    #else
        gmtime_r(&t, &tm);
    #endif
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    static std::string get_db_iso_string() {
        std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm tm{};
    #if defined(_WIN32)
        gmtime_s(&tm, &t);
    #else
        gmtime_r(&t, &tm);
    #endif
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
        return oss.str();
    }
}
static std::string generate_commit_id(){
    return generate_alphanumeric(40);
   } m
   static void log(const std::string& message){
    std::cout << "[MiniGit]" << " " << message  << std::endl;
   }

#endif 