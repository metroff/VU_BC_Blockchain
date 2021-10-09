#include "pool.hpp"

void Pool::generate_transaction_pool(Users& users, int count) {
    for (int i = 0; i < count; i++)
    {
        User* sender = users.get_random_user();
        User* receiver = users.get_random_user();
        while(sender->get_public_key() == receiver->get_public_key()) {
            receiver = users.get_random_user();
        }
        
        Transaction transaction(sender, receiver, generateIntInRange(0, sender->get_balance()/2));

        vector<Transaction>::iterator it = std::find_if(transaction_pool.begin(), transaction_pool.end(), [&transaction](Transaction &t) {
            return transaction.get_id() == t.get_id();
        });

        while (it != transaction_pool.end()) {
            Transaction transaction(sender, receiver, generateIntInRange(0, sender->get_balance()/2));

            it = std::find_if(transaction_pool.begin(), transaction_pool.end(), [&transaction](Transaction &t) {
                return transaction.get_id() == t.get_id();
            });
        }

        transaction_pool.push_back(transaction);
    }
}

Transaction Pool::get_transaction(int index) {
    return transaction_pool[index];
}

vector<Transaction> Pool::get_transactions(int count) {
    vector<Transaction> transactions;
    for (int i = 0; i < std::min(count, get_transaction_count()); i++)
    {
        transactions.push_back(get_transaction(i));
    }
    return transactions;
}

int Pool::get_transaction_count() {
    return transaction_pool.size();
}

stringstream Pool::to_sstream() {
    stringstream ss;
    for (Transaction &transaction: transaction_pool) {
        ss << "TANSACTION ID: " << transaction.get_id() << endl
        << "SENDERS_PUBLIC_KEY: " << transaction.get_senders_hash() << endl
        << "RECEIVERS_PUBLIC_KEY: " << transaction.get_reveivers_hash() << endl
        << "AMOUNT: " << transaction.get_amount() << endl;
        ss << string(50, '-') << endl;
    }
    return ss; 
}

void Pool::remove_transaction(Transaction &_t) {
    vector<Transaction>::iterator it = std::find_if(transaction_pool.begin(), transaction_pool.end(),[&_t](Transaction& t) {
        return t.get_id() == _t.get_id();
    });

    if (it != transaction_pool.end()) {
        transaction_pool.erase(it);
    }   
}

void Pool::remove_transactions(vector<Transaction> &_t) {
    for (Transaction& t : _t){
        remove_transaction(t);
    }
}