#pragma once
#include "myLib.hpp"
#include "transaction.hpp"
#include <algorithm>
#include "time.hpp"
#include "omp.h"
#include <bitcoin/system.hpp>

class Block {
    private:
        string block_hash;
        string prev_block_hash;
        string timestamp;
        string merkle_root_hash;
        int nonce;
        int difficulty_target;
        double version;
        bool mined;
        vector<Transaction> transactions;
        bool check_hash_difficulty(string&);

    public:
        Block();
        Block(string prev_block_hash,
            int difficulty_target,
            double version);

        string get_merkle_root_hash();
        bc::hash_digest create_merkle(bc::hash_list&);
        void add_transactions(const vector<Transaction>&);
        void add_transaction(Transaction&);
        void mine(int&);
        void confirm_transactions();
        string get_block_hash();
        vector<Transaction> get_transactions();
        stringstream to_sstream();
        string get_timestamp();
        int get_transaction_count();
        int get_difficulty();
        int get_transaction_volume();
        int get_nonce();
        bool is_mined();
};
