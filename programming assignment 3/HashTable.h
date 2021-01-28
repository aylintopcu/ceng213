#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"
#include "ItemNotFoundException.h"
/* Do not add new libraries or files */

#define BUCKET_SIZE 2

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class K, class T>
class HashTable {
    struct Entry {
        K Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[BUCKET_SIZE];
    };

    int _capacity; // INDICATES THE TOTAL CAPACITY OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // THE HASH TABLE

    // == DEFINE HELPER METHODS & VARIABLES BELOW ==


public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    // COPY THE WHOLE CONTENT OF RHS INCLUDING THE KEYS THAT WERE SET AS DELETED
    HashTable(const HashTable<K, T>& rhs);
    HashTable<K, T>& operator=(const HashTable<K, T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. IF THE LOAD FACTOR OF THE TABLE IS GREATER THAN 0.6,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(const K& key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, THROW ItemNotFoundException()
    void Delete(const K& key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THROW ItemNotFoundException()
    T& Get(const K& key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES
    void Resize(int newCapacity);

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const; // RETURN THE TOTAL CAPACITY OF THE TABLE
    int Size() const; // RETURN THE NUMBER OF ACTIVE ITEMS
    void getKeys(K* keys); // PUT THE ACTIVE KEYS TO THE GIVEN INPUT PARAMETER
};

template <class K, class T>
HashTable<K, T>::HashTable() {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    this->_table = new Bucket[7];
    this->_capacity = 7;
    this->_size = 0;
}

template <class K, class T>
HashTable<K, T>::HashTable(const HashTable<K, T>& rhs) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    if (rhs._capacity != 0)
    {
        _capacity = rhs._capacity;
        _size = rhs._size;
        
        this->_table = new Bucket[_capacity];
                
        for (int i = 0; i < _capacity; ++i)
        {
            _table[i].entries[0].Key = rhs._table[i].entries[0].Key;
            _table[i].entries[0].Value = rhs._table[i].entries[0].Value;
            _table[i].entries[0].Active = rhs._table[i].entries[0].Active;
            _table[i].entries[0].Deleted = rhs._table[i].entries[0].Deleted;
            
            _table[i].entries[1].Key = rhs._table[i].entries[1].Key;
            _table[i].entries[1].Value = rhs._table[i].entries[1].Value;
            _table[i].entries[1].Active = rhs._table[i].entries[1].Active;
            _table[i].entries[1].Deleted = rhs._table[i].entries[1].Deleted;
        }
    }
}

template <class K, class T>
HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& rhs) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    if (rhs._capacity != 0)
    {
        if (this != &rhs)
        {
            delete [] _table;
            
            _capacity = rhs._capacity;
            _size = rhs._size;
            
            this->_table = new Bucket[_capacity];
            
            for (int i = 0; i < _capacity; ++i)
            {
                _table[i].entries[0].Key = rhs._table[i].entries[0].Key;
                _table[i].entries[0].Value = rhs._table[i].entries[0].Value;
                _table[i].entries[0].Active = rhs._table[i].entries[0].Active;
                _table[i].entries[0].Deleted = rhs._table[i].entries[0].Deleted;
                
                _table[i].entries[1].Key = rhs._table[i].entries[1].Key;
                _table[i].entries[1].Value = rhs._table[i].entries[1].Value;
                _table[i].entries[1].Active = rhs._table[i].entries[1].Active;
                _table[i].entries[1].Deleted = rhs._table[i].entries[1].Deleted;
            }
        }
    }
    
    else
    {
        delete [] _table;
        
        _capacity = 0;
        _size = 0;
    }
    
    return *this;
}

template <class K, class T>
HashTable<K, T>::~HashTable() {
    // TODO: IMPLEMENT THIS FUNCTION.

    delete [] _table;
}

template <class K, class T>
void HashTable<K, T>::Insert(const K& key, const T& value) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    int index = Hash(key) % _capacity;
    int temp = index;
    int x = 1;
    
    while (_table[index].entries[0].Active && _table[index].entries[1].Active)
    {
        if (_table[index].entries[0].Key == key)
        {
            _table[index].entries[0].Value = value;
            return;
        }
        
        else if (_table[index].entries[1].Key == key)
        {
            _table[index].entries[1].Value = value;
            return;
        }
        
        index = (temp + x * x) % _capacity;
        x++;
    }
    
    if (_table[index].entries[0].Active && _table[index].entries[0].Key == key)
    {
        _table[index].entries[0].Value = value;
        return;
    }
    
    else if (_table[index].entries[1].Active && _table[index].entries[1].Key == key)
    {
        _table[index].entries[1].Value = value;
        return;
    }
    
    else if (!_table[index].entries[0].Active)
    {
        _table[index].entries[0].Key = key;
        _table[index].entries[0].Value = value;
        _table[index].entries[0].Active = true;
        _table[index].entries[0].Deleted = false;
        _size++;
    }
        
    else if (!_table[index].entries[1].Active)
    {
        _table[index].entries[1].Key = key;
        _table[index].entries[1].Value = value;
        _table[index].entries[1].Active = true;
        _table[index].entries[1].Deleted = false;
        _size++;
    }
    
    if ((float) _size / (2 * _capacity) > 0.6)
    {
        int next_capacity = NextCapacity(_capacity);
        Resize(next_capacity);
    }
}

template <class K, class T>
void HashTable<K, T>::Delete(const K& key) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    int index = Hash(key) % _capacity;
    int temp = index;
    int x = 1;
    
    while (_table[index].entries[0].Active || _table[index].entries[1].Active)
    {
        if (_table[index].entries[0].Key == key)
        {
            _table[index].entries[0].Active = false;
            _table[index].entries[0].Deleted = true;
            _size--;
            return;
        }
        
        else if (_table[index].entries[1].Key == key)
        {
            _table[index].entries[1].Active = false;
            _table[index].entries[1].Deleted = true;
            _size--;
            return;
        }
        
        index = (temp + x * x) % _capacity;
        x++;
    }
    
    throw ItemNotFoundException();
}

template <class K, class T>
T& HashTable<K, T>::Get(const K& key) const {
    // TODO: IMPLEMENT THIS FUNCTION. 
    
    int index = Hash(key) % _capacity;
    int temp = index;
    int x = 1;
    
    while (_table[index].entries[0].Active || _table[index].entries[1].Active)
    {
        if (_table[index].entries[0].Key == key && !_table[index].entries[0].Deleted)
        {
            return _table[index].entries[0].Value;
        }
        
        else if (_table[index].entries[1].Key == key && !_table[index].entries[1].Deleted)
        {
            return _table[index].entries[1].Value;
        }
        
        index = (temp + x * x) % _capacity;
        x++;
    }
    
    throw ItemNotFoundException();
}

template <class K, class T>
void HashTable<K, T>::Resize(int newCapacity) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    Bucket *temp = new Bucket[_capacity];
    
    for (int i = 0; i < _capacity; ++i)
    {
        temp[i].entries[0].Key = _table[i].entries[0].Key;
        temp[i].entries[0].Value = _table[i].entries[0].Value;
        temp[i].entries[0].Active = _table[i].entries[0].Active;
        temp[i].entries[0].Deleted = _table[i].entries[0].Deleted;
                
        temp[i].entries[1].Key = _table[i].entries[1].Key;
        temp[i].entries[1].Value = _table[i].entries[1].Value;
        temp[i].entries[1].Active = _table[i].entries[1].Active;
        temp[i].entries[1].Deleted = _table[i].entries[1].Deleted;
    }
    
    int old_capacity = _capacity;
    
    delete [] _table;
    
    _size = 0;
    _capacity = newCapacity;
    _table = new Bucket[_capacity];
    
    for (int i = 0; i < old_capacity; ++i)
    {
        if (temp[i].entries[0].Active && !temp[i].entries[0].Deleted)
        {
            Insert(temp[i].entries[0].Key, temp[i].entries[0].Value);
        }
        
        if (temp[i].entries[1].Active && !temp[i].entries[1].Deleted)
        {
            Insert(temp[i].entries[1].Key, temp[i].entries[1].Value);
        }
    }
    
    delete [] temp;
}

template <class K, class T>
int HashTable<K, T>::Capacity() const {
    return _capacity;
}

template <class K, class T>
int HashTable<K, T>::Size() const {
    return _size;
}

template <class K, class T>
void HashTable<K, T>::getKeys(K* keys) {
    int index = 0;

    for (int i = 0; i < _capacity; i++) {
        Bucket& bucket = _table[i];
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (bucket.entries[j].Active && !bucket.entries[j].Deleted) {
                keys[index++] = bucket.entries[j].Key;
            }
        }
    }
}

#endif