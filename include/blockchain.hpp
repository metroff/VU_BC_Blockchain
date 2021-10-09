#pragma once
#include "myLib.hpp"
#include "block.hpp"

class BlockChain {
    private:
        vector<Block> blocks;

    public:
        void add_block(Block&);
        int get_block_count();
        bool is_empty();
        string get_last_block_hash();
        int get_transaction_count();
        stringstream to_sstream();
};