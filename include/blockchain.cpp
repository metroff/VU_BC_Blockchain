#include "blockchain.hpp"

void BlockChain::add_block(Block& block) {
    blocks.push_back(block);
}

int BlockChain::get_block_count() {
    return blocks.size();
}

int BlockChain::get_transaction_count() {
    int output = 0;
    for(Block &b: blocks) {
        output += b.get_transaction_count();
    }
    return output;
}

bool BlockChain::is_empty() {
    return blocks.size() == 0;
}

string BlockChain::get_last_block_hash() {
    return blocks.back().get_block_hash();
}

stringstream BlockChain::to_sstream() {
    stringstream ss;
    ss << endl << string(50, '-') << endl << "Blockchain statistics" << endl
    << "Block count: " << get_block_count() << endl
    << "Transaction count: " << get_transaction_count() << endl;
    return ss;
}