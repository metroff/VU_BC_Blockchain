#include "include/myLib.hpp"
#include "include/users.hpp"
#include "include/utility.hpp"
#include "include/pool.hpp"
#include "include/time.hpp"
#include "include/block.hpp"
#include "include/blockchain.hpp"
#include "include/console.hpp"
#include <omp.h>
#include <sys/stat.h>

bool checkIfFileExists(const string& fileName){
    struct stat buffer;
    return (stat(fileName.c_str(), &buffer)==0);
}

int main() {
    if (!checkIfFileExists("log")) {
        if(std::system("mkdir log") == 0) {
            cout << "Created log folder." << endl;
        }
    }

    int user_count = 1000, transaction_count = 10000, block_transactions = 100;

    if (!yesNoQuestion("Use default values?")) {
        user_count = getInt("User count (>1): ", 2);
        transaction_count = getInt("Transaction count (>0): ", 1);
        block_transactions = getInt("Transactions in block: ", 0);
    }

    cout << "User count = " << user_count << ", Transaction count = " << transaction_count << ", Transactions in block = " << block_transactions << endl << endl;

    BlockChain block_chain;
    Users users;
    cout << "Generating users (" << user_count << ")" << endl;
    users.generate_users(user_count);
    print_stream_file(users.to_sstream(), "log/users_start.txt");

    Pool pool;
    cout << "Generating transactions (" << transaction_count << ")" << endl;
    pool.generate_transaction_pool(users, transaction_count);
    print_stream_file(pool.to_sstream(), "log/all_transactions.txt");

    string genesis_block_hash = "0000000000000000000000000000000000000000000000000000000000000000";

    string prev_block_hash;
    int index = 1;

    while(pool.get_transaction_count() > 0) {
        int nonce_limit = 100000;

        if (!block_chain.is_empty()) {
            prev_block_hash = block_chain.get_last_block_hash();
        } else {
            prev_block_hash = genesis_block_hash;
        }

        vector<Block> potential_blocks;
        potential_blocks.reserve(5);

        for (int i = 0; i < 5; i++)
        {
            Block block(prev_block_hash, 1, 0.1);
            block.add_transactions(pool.get_transactions(block_transactions));
            potential_blocks.push_back(block);
        }

        string abc[5] = { "A", "B", "C", "D", "E" };

        cout << "Mining block: " << std::to_string(index) << endl;

        while (true) {
            cout << "Nonce limit: " << nonce_limit << ", ";

            #pragma omp parallel for
            for (int i = 0; i < 5; i++)
            {
                #pragma omp critical 
                {
                    cout << index << abc[i] << " ";
                }

                potential_blocks[i].mine(nonce_limit);
            }

            cout << endl;

            bool block_found = false;
            Block block = potential_blocks[0];
            int min_nonce = potential_blocks[0].get_nonce();

            for (Block& b : potential_blocks) {
                if (b.get_nonce() <= nonce_limit) {
                    if (b.get_nonce() < min_nonce)
                    {
                        min_nonce = b.get_nonce();
                        block = b;
                    }
                    block_found = true;
                }
            }
            if (block_found)
            {
                pool.remove_transactions(block.get_transactions());

                block.confirm_transactions();

                block_chain.add_block(block);

                print_stream_file(block.to_sstream(), "log/block-" + std::to_string(index) + ".txt", index);

                break;
            }

            nonce_limit += 100000;
        }

        index++;
    }

    print_stream_file(users.to_sstream(), "log/users_end.txt");

    print_stream(block_chain.to_sstream());
}