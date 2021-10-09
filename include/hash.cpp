#include "hash.hpp"

// Function for converting I type to hexString
template <typename I> std::string toHexString(I w, size_t hex_len = sizeof(I)<<1) {
    static const char* digits = "0123456789abcdef";
    std::string rc(hex_len,'0');
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}

// Bits rotation
int leftRotate(int n, unsigned int d) {
    return (n << d)|(n >> (32 - d));
}

unsigned int rightRotate(unsigned int n, unsigned int d)
{
    return (n >> d)|(n << (32 - d));
}

// Main hash function
std::string myHash(const std::string& input) {
    std::string output = "";
    // Initial values
    unsigned int hexes[8] = {3189621198, 405587210, 2844532716, 1761483275, 152458759, 2779224377, 4151057064, 1000842129};

    int length = input.length();

    int num = 1153;
    int sum = num;

    // Number transformations 
    for (int i = 0; i < length; i++){
        sum = num|(int(input[i])%num);
        num = leftRotate(num, 5) + int(input[i]) - num;
    }
    // Initial value rotation more "random" values
    for (int i = 1; i < sum % 100; i++) {
         hexes[i%8] = rightRotate(hexes[i%8], 16);
    }
    // More mixups to reduce collisions and for avalanche
    for (int i = 0; i < 8; i++) {
        hexes[i] ^= (~hexes[7-i]) * num;
        hexes[7-i] |= (~hexes[i]) * sum;
    }
    // Converting values to string
    for (int i = 0; i < 8; i++) {
        output += toHexString<unsigned int>(hexes[i]);
    }

    return output;
}