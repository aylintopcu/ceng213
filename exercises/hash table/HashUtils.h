
#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <string>
#include "HashStringTable.h"

class HashUtils{
public:
    HashUtils() {}

    // calls add function to insert elements of the name vector into the hash table
    void addNameList(vector<string> nameVector) {
        int len = nameVector.size();
        for (int i=0; i<len; i++) {
            addName(nameVector[i]);
        }

        cout << "size = " << T.get_size() << " count = " << T.get_count() << "\n";
    }

    // calls contains function of the hash table to check whether hast table contains the entry
    bool searchName(string name){
        if (T.contains(name)) {
            cout << name << ": Yes" << "\n";
            return true;
        }
        else {
            cout << name <<": No" << "\n";
            return false;
        }
    }

    // calls remove function of the hash table to delete the entry from hash table.
    void deleteName(string name){
        if (T.remove(name)) {
            cout << name << " is deleted" << "\n";
        }
        else {
            cout << name <<" does not exist" << "\n";
        }
    }
    // calls add function to insert the entry into the table.
    void addName(string name) {
        T.add(name);
        cout << name << " is added" << "\n";
    }

    // lists statistics about the hash table
    void report() {
        cout << "Table size = " << T.get_size() << "\n";
        cout << "Number of names in the table = " << T.get_count() << "\n";
        cout << "Load factor = " << (double)T.get_count()/T.get_size()<< "\n";

    }

private:
    HashStringTable T;

};

#endif //HASHUTILS_H
