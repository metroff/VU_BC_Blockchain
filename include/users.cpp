#include "users.hpp"

void Users::generate_users(int count){
    for (int i = 0; i < count; i++)
    {
        User user("User-"+std::to_string(i+1), generateIntInRange(MIN_BALANCE, MAX_BALANCE));

        vector<User>::iterator it = std::find_if(users.begin(), users.end(), [&user](User &u) {
            return u.get_public_key() == user.get_public_key();
        });

        while (it != users.end()) {
            user = User("User-"+std::to_string(i), generateIntInRange(MIN_BALANCE, MAX_BALANCE));

            it = std::find_if(users.begin(), users.end(), [&user](User &u) {
                return u.get_public_key() == user.get_public_key();
            });
        }

        users.push_back(user);
    }
}

stringstream Users::to_sstream() {
    stringstream ss;
    for (User user: users) {
        ss << "Name: " << user.get_name() << endl
        << "Public key: " << user.get_public_key() << endl
        << "Current balance: " << user.get_balance() << endl;
        ss << string(50, '-') << endl;
    }
    return ss; 
}

User* Users::get_random_user() {
    return &users[generateIntInRange(0, users.size()-1)];
}