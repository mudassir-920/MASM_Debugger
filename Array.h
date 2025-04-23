#ifndef ARRAY_H
#define ARRAY_H
class Array
{
    int* data;
    int capacity;
    bool isValidIndex(int index) const;
public:
    Array(int cap = 0, ...);
    Array(const Array& ref);
    int& getSet(int index);
    const int& getSet(int index) const;
    int getCapacity() const;
    ~Array();
    void resize(int newCap);
};
#endif