//
// Created by 666 on 2021/3/26.
//

#ifndef COMPUTERSCIENCEFOUNDATION_LINEARLIST_H
#define COMPUTERSCIENCEFOUNDATION_LINEARLIST_H
#include <ostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "PublicException.h"

using std::min;
using std::ostringstream;
using std::ostream_iterator;
using std::max;
using std::ostream;
using std::copy;
using std::copy_backward;
using std::find;


template<class T>
class linearList {

public:
    virtual ~linearList() = default;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int theIndex) const = 0;
    virtual int indexOf(const T& theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T& theElement) = 0;
    virtual void output(ostream& out) const = 0;

};

template<class T>
class arrayList : public linearList<T> {

protected:
    void checkIndex(int theIndex) const;
    T* element;
    const int initArrayLength;
    int arrayLength;
    int listSize;
public:
    explicit arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>& theList);
    ~arrayList() {delete [] element;}

    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;
    int capacity() const {return arrayLength;}

};

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength) {

    if(newLength < 0) {
        throw illegalParameterValue("new length must be >= 0");
    }

    T* temp = new T[newLength];
    int number = min(oldLength, newLength);
    copy(a, a + number, temp);
    delete [] a;
    a = temp;

}

template<class T>
arrayList<T>::arrayList(int initialCapacity) : initArrayLength(initialCapacity) {

    if(initialCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str().c_str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;

}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList) : initArrayLength(theList.arrayLength) {

    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);

}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const {

    if(theIndex < 0 || theIndex >= listSize) {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalParameterValue(s.str().c_str());
    }

}

template<class T>
T& arrayList<T>::get(int theIndex) const {

    checkIndex(theIndex);
    return element[theIndex];

}

template<class T>
int arrayList<T>::indexOf(const T &theElement) const {

    int theIndex = (int)(find(element, element + listSize, theElement) - element);

    if(theIndex == listSize) {
        return -1;
    } else {
        return theIndex;
    }

}

template<class T>
void arrayList<T>::erase(int theIndex) {

    checkIndex(theIndex);
    copy(element + theIndex + 1, element + listSize, element + theIndex);
    element[--listSize].~T();

    if(listSize < arrayLength / 4) {
        changeLength1D(element, arrayLength, max(initArrayLength, arrayLength / 2));
        arrayLength = max(initArrayLength, arrayLength / 2);
    }

}

template<class T>
void arrayList<T>::insert(int theIndex, const T &theElement) {

    if(theIndex < 0 || theIndex > listSize) {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalParameterValue(s.str().c_str());
    }

    if(listSize == arrayLength) {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;
    listSize++;

}

template<class T>
void arrayList<T>::output(ostream &out) const {

    copy(element, element + listSize, ostream_iterator<T>(cout, " "));

}

template<class T>
ostream& operator<<(ostream& out, const arrayList<T>& x) {

    x.output(out);
    return out;

}

#endif //COMPUTERSCIENCEFOUNDATION_LINEARLIST_H
