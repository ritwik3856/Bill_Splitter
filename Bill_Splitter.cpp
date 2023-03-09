#include <bits/stdc++.h>

using namespace std;

int main()
{
    string payer, taker, amount;
    int no_of_payers;

    vector<string> input; // input vector for a single transaction 0th place is the payer 1st place is the amount he payed
                          //  2nd to nth place for no. of participants.

    cout << "Enter the no. of payers : ";
    cin >> no_of_payers;

    map<string, int> net; // map for storing the net amt that each person will have at the end.(debit or credit).

    for (int i = 0; i < no_of_payers; i++)
    {
        cout << "Enter the name of payer " << i + 1 << " : ";
        cin >> payer;
        cout << "Enter the amount that he paid : ";
        cin >> amount;
        input.push_back(payer);
        input.push_back(amount);
        cout << "Enter no. of the participants including payer : ";
        int p, split;
        cin >> p;
        split = (stoi(input[1])) / p; // converting the amount to integer as it was taken as string.
        cout << "Enter their names \n";

        for (int j = 0; j < p; j++)
        {
            cin >> taker;
            input.push_back(taker);

            if (payer != taker) // if names are same then no need for splitting as he paid
            {

                if (!net.count(payer)) // if entry doesn't exist then create it in the map for both.
                    net[payer] = 0;

                if (!net.count(taker))
                    net[taker] = 0;

                net[payer] += split;
                net[taker] -= split;
            }
        }
        input.clear();
    }

    cout << endl;
    cout << "---Distributed Expenses---\n";
    for (auto i : net)
        cout << i.first << " -> " << i.second << endl;
    cout << endl;

    multiset<pair<int, string>> m; // helps to sort the entries and can have multiple values of same entries too.
    for (auto p : net)
    {
        string person = p.first;
        int amount = p.second;

        if (net[person] != 0) // if amount not 0 then there exists some transactions
        {
            m.insert(make_pair(amount, person));
        }
    }
    // Now we'll take out 2 people one from left(who'll give the money i.e. debitor)
    // and one from right (who'll get the money i.e. creditor).

    int count = 0; // count the no. of transactions that has been made.

    while (!m.empty())
    {
        auto low = m.begin();      // pointer at the first element.
        auto high = prev(m.end()); // gives the pointer after the last element

        int debit = low->first;
        string debit_person = low->second;

        int credit = high->first;
        string credit_person = high->second;

        m.erase(low);  // now we will erase these values from multiset & afterwards
        m.erase(high); // see if the transaction is settled or or one of them is cancelled.

        int settlement_amount = min(-debit, credit);
        debit += settlement_amount;
        credit -= settlement_amount;

        cout << debit_person << " will pay " << settlement_amount << " to " << credit_person << endl;

        if (debit != 0)
        {
            m.insert(make_pair(debit, debit_person));
        }

        if (credit != 0)
        {
            m.insert(make_pair(credit, credit_person));
        }

        count += 1;
    }
    cout << endl;
    cout << "Total no. of transactions : " << count;
    cout << endl<< endl;
    cout<<"Press Any Key To Exit...";
    system("pause>null");
}
