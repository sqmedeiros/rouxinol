#include<bits/stdc++.h>
using namespace std;
 
int solve2() {
    int num_tickets, num_customers;
    multiset<int> tickets;
    cin >> num_tickets >> num_customers;
 
    for (int i = 0; i < num_tickets; i++) {
        int t;
        cin >> t;
        tickets.insert(t);
    }
 
    for (int i = 0; i < num_customers; i++) {
        int t;
        cin >> t;
        auto chosen_ticket = tickets.upper_bound(t);
        if (chosen_ticket == tickets.begin()) {
            cout << "-1" << endl;
            continue;
        } else {
            cout << *(--chosen_ticket) << endl;
            tickets.erase(chosen_ticket);
        }
    }
}
 
int main() {
    solve2();
    return 0;
}
