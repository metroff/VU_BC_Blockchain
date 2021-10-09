#include "utility.hpp"

void print_stream(stringstream stream) {
    cout << stream.str();
}

void print_stream_file(stringstream stream, string filename, int block) {
    std::ofstream out_file(filename);
    if (block != 0)
    {
        out_file << "Block: " << block << endl << string(50, '-') << endl;
    }  
    out_file << stream.rdbuf();
    out_file.close();
}