// template <typename T>
// class HashNode {
// public:
//     T value;
//     HashNode(T v);
// };

template <typename  T>
class HashTable {
private:
    int tablesize;
    int count;
    T** table;
    
    int hashFunction(T key);
    void resize();
public:
    HashTable();
    ~HashTable();
    
    void insert(T key);

    T*& search(T key);

    void remove(T key);

};

template class HashTable<int>;