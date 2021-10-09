#include "block.hpp"

Block::Block(string prev_block_hash, int difficulty_target, double version) : 
    prev_block_hash{prev_block_hash}, difficulty_target{difficulty_target}, version{version} {
    nonce = 1;
    timestamp = get_timestamp_now();
}

void Block::add_transaction(Transaction &transaction) {
    vector<Transaction>::iterator it;
    it = std::find_if(transactions.begin(), transactions.end(), [&transaction](Transaction &t) {
        return t.get_id() == transaction.get_id();
    });

    if (it == transactions.end()) {
        transactions.push_back(transaction);
    }
}

string Block::get_merkle_root_hash(){
    stringstream ss;
    for (Transaction &t: transactions) {
        ss << t.get_id();
    }
    return myHash(ss.str());
}

void Block::add_transactions(vector<Transaction> &_t) {
    for (Transaction &t: _t) {
        transactions.push_back(t);
    }
}

void Block::mine() {
    string block_hash = get_block_hash();
    while(!check_hash_difficulty(block_hash)) {
        nonce++;    
        block_hash = get_block_hash();
    }
}

vector<Transaction> Block::get_transactions() {
    return transactions;
}

bool Block::check_hash_difficulty(string &hash) {
    for (int i = 0; i < difficulty_target; i++) {
        if (hash[i] != '0'){
            return false;
        }
    }
    return true;
}

string Block::get_block_hash() {
    stringstream ss;
    ss << prev_block_hash << timestamp << version << get_merkle_root_hash() << nonce << difficulty_target;
    return myHash(ss.str());
}

string Block::get_timestamp() {
    return timestamp;
}

int Block::get_transaction_count() {
    return transactions.size();
}

int Block::get_difficulty(){
    return difficulty_target;
}

int Block::get_transaction_volume(){
    int output = 0;
    for(Transaction& t: transactions) {
        output += t.get_amount();
    }
    return output;
}

stringstream Block::to_sstream() {
    stringstream ss;
    ss << "Block hash: " << get_block_hash() << endl
    << "Previous block hash: " << prev_block_hash << endl
    << "Timestamp: " << get_timestamp() << endl
    << "Transaction count: " << get_transaction_count() << endl
    << "Difficulty: " << difficulty_target << endl
    << "Merkle root hash: " << get_merkle_root_hash() << endl
    << "Version: " << version << endl
    << "Nonce: " << nonce << endl
    << "Transaction volume: " << get_transaction_volume() << endl << endl
    << "TRANSACTIONS" << endl
    << string(50, '-') << endl;
    for(Transaction &t: transactions) {
        ss << t.to_sstream().rdbuf();
    }
    return ss;
}