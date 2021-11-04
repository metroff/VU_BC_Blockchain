#include "pool.hpp"

void Pool::generate_transaction_pool(Users& users, int count) {
    for (int i = 0; i < count; i++)
    {
        User* sender = users.get_random_user();
        User* receiver = users.get_random_user();
        while(sender->get_public_key() == receiver->get_public_key()) {
            receiver = users.get_random_user();
        }
     
        int amount = generateIntInRange(0, sender->get_balance() / 2);

        Transaction transaction;

        int sum = 0;
        auto available_outputs = sender->get_unspent_outputs();
        for (int i = 0; i < available_outputs.size(); i++)
        {
            TransactionInput input;
            sum += available_outputs[i]->amount;
            input.prev_transaction = available_outputs[i];
            transaction.add_input(input);
            if (sum >= amount) {
                break;
            } 
        }
        
        transaction.add_output(std::shared_ptr<TransactionOutput>(new TransactionOutput(amount, receiver)));
        transaction.add_output(std::shared_ptr<TransactionOutput>(new TransactionOutput(sum-amount, sender)));
        transaction.set_id();
        transaction.execute();

        add_transaction(transaction);
    }
}

void Pool::add_transaction(Transaction& t) {
    if (t.get_id() == t.generate_id())
    {
        transaction_pool.push_back(t);
    }
}

Transaction Pool::get_transaction(int index) {
    return transaction_pool[index];
}

vector<Transaction> Pool::get_transactions(int count) {
    shuffle(count);
    vector<Transaction> transactions;
    for (int i = 0; i < std::min(count, get_transaction_count());)
    {
        Transaction t = get_transaction(i);

        if (t.get_amount() > t.get_input_amount())
        {
            remove_transaction(t);
            continue;
        }
        transactions.push_back(t);
        i++;
    }
    return transactions;
}

void Pool::shuffle(int num_random) {
    for (int i = 0; i < std::min(num_random, get_transaction_count()); i++)
    {
        std::swap(transaction_pool[i], transaction_pool[generateIntInRange(i, get_transaction_count() - 1)]);
    }
}

int Pool::get_transaction_count() {
    return transaction_pool.size();
}

stringstream Pool::to_sstream() {
    stringstream ss;
    for (Transaction &transaction: transaction_pool) {
        ss << transaction.to_sstream().rdbuf();
    }
    return ss; 
}

void Pool::remove_transaction(const Transaction &_t) {
    vector<Transaction>::iterator it = std::find_if(transaction_pool.begin(), transaction_pool.end(),[&_t](Transaction& t) {
        return t.get_id() == _t.get_id();
    });

    if (it != transaction_pool.end()) {
        transaction_pool.erase(it);
    }   
}

void Pool::remove_transactions(const vector<Transaction> &_t) {
    for (const Transaction& t : _t){
        remove_transaction(t);
    }
}