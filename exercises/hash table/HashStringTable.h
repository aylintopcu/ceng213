#ifndef _HTABLE
#define _HTABLE
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#define REMOVED "XXX"
using namespace std;

class HashStringTable{
public:
    // constructor that initializes the elements as a vector of size 11
    // with "" values.It also initializes oher private data members
    HashStringTable();

    // Adds string value to elements. It first checks the load factor.
    // If the load factor of elements is >=0.75 then its size is doubled and
    // all data are rehashed. During insertion duplicate values are ignored
    // (i.e. they are not added to the hash table)
    void add(string value) ;

    // returns the size of the hash table (i.e. vector elements)
    int get_size();

    //returns the number of data values in the hash table
    int get_count();

    //returns the average number of probes for successful search
    double get_avgProbe();

    // returns the average number of probes for unsuccessful search
    double get_unsuccessProbe();

    // returns true if the string value is in the hash table; false otherwise
    bool contains(string value);

    // returns true if value is removed successfully from the hash table; false otherwise
    // For the deleted items, you should use the "REMOVED" macro.
    bool remove(string value);

private:
    vector<string> elements; // the hash table implemented as a vector
    int cnt;	//current number of items in the table

    int total_probes;   //total number of probes that helps calculating the
    //average number of probes for successful search.


    // Hash function that finds the hash code corresponding to string str.
    // It should map the given string to an integer value between 0 and
    // hash table size -1.
    // Make sure that your hash function uses all characters of the string in
    // the computation.
    int hashcode(string str);

    // resizes the hash table by doubling its size. The new size will be
    //(oldsize*2)+1
    void rehash() ;

}; //end of class HashStringTable

HashStringTable::HashStringTable() {
    elements.resize(11,"");
    cnt = 0;
    total_probes = 0;
}

void HashStringTable::add(string value) {
// TODO:
    int size = get_size();
    
    if (cnt / size >= 0.75)
    {
        cnt = 0;
        total_probes = 0;
        rehash();
    }
    
    int key = hashcode(value);
    
    while (elements[key] != "")
    {
        if (elements[key] == value)
        {
            return;
        }
        
        total_probes++;
        key = (key + 1) % size;
    }
    
    elements[key] = value;
    cnt++;
    
    if (cnt / size >= 0.75)
    {
        cnt = 0;
        total_probes = 0;
        rehash();
    }
}

int HashStringTable::get_size() {
    return elements.size();
}

int HashStringTable::get_count() {
    return cnt;
}

double HashStringTable::get_avgProbe() {
    return (cnt == 0)?1:(double)total_probes/(double)cnt;
}

double HashStringTable::get_unsuccessProbe() {
// TODO:
    float load_factor = cnt / get_size();
    
    return (1 + (1 / pow(1 - load_factor, 2))) / 2;
}

bool HashStringTable::contains(string value) {
// TODO:
    int key = hashcode(value);
    
    while (elements[key] != "")
    {
        if (elements[key] == value)
        {
            return true;
        }
        
        key = (key + 1) % get_size();
    }
    
    return false;
}

bool HashStringTable::remove(string value) {
// TODO:
    int key = hashcode(value);
    
    while (elements[key] != "")
    {
        if (elements[key] == value)
        {
            elements[key] = REMOVED;
            cnt--;
            return true;
        }
        
        key = (key + 1) % get_size();
    }
    
    return false;
}

int HashStringTable::hashcode(string str) {
    int h = 0;
    for (unsigned i = 0; i < str.length(); i++) {
        h = 31 * h + str[i];
    }
    h %= elements.size();
    if (h < 0)   /* in case overflows occurs */
        h += elements.size();

    return h;
}

void HashStringTable::rehash() {
// TODO:
    vector<string> new_elements;
    vector<string> temp = elements;
    int size = get_size();
    
    elements.clear();
    elements.resize(size * 2 + 1, "");
    
    for (int i = 0; i < size; ++i)
    {
        if (temp[i] != "")
        {
            add(temp[i]);
        }
    }
}


#endif // _HTABLE

