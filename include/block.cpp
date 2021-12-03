#include "block.hpp"

Block::Block() : prev_block_hash{ "" }, difficulty_target{ 0 }, version{ 0 }, nonce{ 1 }, timestamp{ "" }, mined{false} {};

Block::Block(string prev_block_hash, int difficulty_target, double version) : 
    prev_block_hash{prev_block_hash}, difficulty_target{difficulty_target}, version{version}, mined{ false } {
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
    // vector<string> merkleTree;

    // merkleTree.reserve(transactions.size() * 2 + 16);

    // for (Transaction &t: transactions)
    //     merkleTree.push_back(t.get_id());
        
    // int j = 0;
    // for (int size = transactions.size(); size > 1; size = (size + 1) / 2)
    // {
    //     for (int i = 0; i < size; i += 2)
    //     {
    //         int i2 = std::min(i + 1, size - 1);

    //         merkleTree.push_back(myHash(merkleTree[j + i] + merkleTree[j + i2]));
    //     }
    //     j += size;
    // }
    // return (merkleTree.empty() ? string() : merkleTree.back());
    bc::hash_list tx_hashes;
    tx_hashes.reserve(transactions.size() * 2 + 16);

    for (Transaction &t: transactions) {
        string tid = t.get_id();
        char cstr[65];
        strncpy(cstr, tid.c_str(), sizeof(cstr));
        tx_hashes.push_back(bc::hash_literal(cstr));
    }

    const bc::hash_digest merkle_root = create_merkle(tx_hashes);

    return bc::encode_base16(merkle_root);
}

bc::hash_digest Block::create_merkle(bc::hash_list& merkle)
{
    // Stop if hash list is empty or contains one element
    if (merkle.empty())
    return bc::null_hash;
    else if (merkle.size() == 1)
    return merkle[0];
    // While there is more than 1 hash in the list, keep looping...
    while (merkle.size() > 1)
    {
        // If number of hashes is odd, duplicate last hash in the list.
        if (merkle.size() % 2 != 0)
            merkle.push_back(merkle.back());
        // List size is now even.
        assert(merkle.size() % 2 == 0);
        // New hash list.
        bc::hash_list new_merkle;
        // Loop through hashes 2 at a time.
        for (auto it = merkle.begin(); it != merkle.end(); it += 2)
        {
            // Join both current hashes together (concatenate).
            bc::data_chunk concat_data(bc::hash_size * 2);
            auto concat = bc::serializer<
            decltype(concat_data.begin())>(concat_data.begin());
            concat.write_hash(*it);
            concat.write_hash(*(it + 1));
            // Hash both of the hashes.
            bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
            // Add this to the new list.
            new_merkle.push_back(new_root);
        }
        // This is the new list.
        merkle = new_merkle;
        // DEBUG output -------------------------------------
        // std::cout << "Current merkle hash list:" << std::endl;
        // for (const auto& hash: merkle)
        //     std::cout << " " << bc::encode_base16(hash) << std::endl;
        // std::cout << std::endl;
        // --------------------------------------------------
    }
    // Finally we end up with a single item.
    return merkle[0];
}

void Block::add_transactions(const vector<Transaction> &_t) {
    for (const Transaction &t: _t) {
        transactions.push_back(t);
    }
}

void Block::mine(int& can_mine) {
    while(can_mine == 1) {    
        block_hash = get_block_hash();
        if (check_hash_difficulty(block_hash))
        {
            #pragma omp atomic
            can_mine -= 1;

            mined = true;
            return;
        }
        nonce++;
    }
}

bool Block::is_mined() {
    return mined;
}

void Block::confirm_transactions() {
    for (Transaction& t : transactions) {
        t.confirm();
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

int Block::get_nonce() {
    return nonce;
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