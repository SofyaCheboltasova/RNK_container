#include    <iostream>
#include <cassert>
#include <string>
#include "RNK.h"

Nucl get_complem(Nucl nucleotide) {
    switch(nucleotide) {
        case A:
            return T;
        case G:
            return C;
        case C:
            return G;
        case T:
            return A;
        default:
            return A;
    }
}

RNK::RNK() {
    size = 0;

    for(auto nucl : {Nucl::A, Nucl::G, Nucl::C, Nucl::T }){
        card.insert(map::value_type(nucl, 0));
    }
}

RNK::RNK(size_t size1, Nucl nucleotide) {
    size = size1;
    Vector new_vector(size, nucleotide);
    vector = new_vector;

    for(auto nucl : {Nucl::A, Nucl::G, Nucl::C, Nucl::T }) {
        card.insert(map::value_type(nucl, 0));
    }
    card.at(nucleotide) = size;
}

RNK::RNK(const RNK &rnk2) {
    for(size_t i = 0; i < rnk2.size; ++i) {
        vector.push_back(rnk2.vector.get(i));
        card.at(rnk2.get_nucl(i))++;
    }
    size = rnk2.size;
}

RNK::~RNK() {
    vector.~Vector();
}

void RNK::push(const RNK& rnk2) {
    for(size_t i = 0; i < rnk2.size; ++i) {
        vector.push_back(rnk2.vector.get(i));
        card.at(rnk2.get_nucl(i))++;
    }
    size = size + rnk2.size;
}

void RNK::push(Nucl nucl) {
    vector.push_back(nucl);
    ++card.at(nucl);
    ++size;
}

RNK RNK::operator+(const RNK& rnk1) const {
    RNK rnk;
    rnk.push(*this);
    rnk.push(rnk1);
    return rnk;
}

bool RNK::operator==(const RNK& rnk1) const {
    if(rnk1.size == size) {
        for(size_t i = 0; i < rnk1.size; ++i) {
            if(rnk1.vector.get(i) != vector.get(i))
                return false;
        }
        return true;
    }
    else return false;
}

bool RNK::operator!=(const RNK& rnk1) const{
    if(rnk1.size == size) {
        for(size_t i = 0; i < rnk1.size; ++i) {
            if(rnk1.vector.get(i) != vector.get(i))
                return true;
        }
        return false;
    }
    else return true;
}

Nucl RNK::operator[](size_t idx) const{
    return (get_nucl(idx));
}

RNK::Nucl_ref RNK::operator[](const size_t idx) {
    assert(idx + 1 <= size);
    return Nucl_ref(idx, *this);
}

RNK::Nucl_ref::Nucl_ref(const size_t idx, RNK& rnk2) {
    index = idx;
    rnk = &rnk2;
}

RNK::Nucl_ref& RNK::Nucl_ref::operator=(Nucl nucl) {
    rnk->set_nucl(index, nucl);
    return *this;
}

RNK::Nucl_ref::operator Nucl(){
    return rnk->get_nucl(index);
}

void RNK::set_nucl(size_t index, const Nucl nucl) {
    --card.at(get_nucl(index));
    vector.push(index, nucl);
    ++card.at(nucl);
}

RNK& RNK::operator=(const RNK& rnk2) {
    if(rnk2 != *this) {
        this->vector.copy_vector(rnk2.vector);
        this->size = rnk2.size;

        card.clear();
        for (auto nucl : {Nucl::A, Nucl::G, Nucl::C, Nucl::T}) {
            card.insert(map::value_type(nucl, 0));
        }

        for (size_t i = 0; i < rnk2.size; ++i)
            ++card.at(rnk2.get_nucl(i));
    }
    return *this;
}


RNK RNK::operator!() const {
    RNK rnk_new;

    for(size_t i = 0; i < size; ++i) {
        rnk_new.push(get_complem(get_nucl(i)));
        rnk_new.card.at(get_complem(get_nucl(i)))++;
    }
    return rnk_new;
}


size_t RNK::length() const {
    return size;
}

Nucl RNK::get_nucl(const size_t idx) const {
    assert(idx + 1 <= size);
    return ((Nucl)vector.get(idx));
}

bool RNK::is_complementary(const RNK &other) const {
    return (*this != other);
}

RNK RNK::split(size_t idx) const {
    assert (idx + 1 <= size);

    RNK rnk_new;
    for (size_t i = idx; i < size; ++i) {
        rnk_new.vector.push_back(vector.get(i));
        rnk_new.card.at(get_nucl(i))++;
        ++rnk_new.size;
    }
    return rnk_new;
}

void RNK::trim(size_t idx) {
    assert (size > 0 && idx + 1 <= size && idx > 0);
    int* new_array = new int[idx];

    for(size_t i = 0; i < idx; ++i)
        new_array[i] = vector.get(i);

    for(size_t i = idx; i < size; ++i)
        --card.at(get_nucl(i));

    vector.setArray(new_array);
    vector.setSize(idx);
    vector.setCapacity(idx);
    size = idx;
}

int RNK::cardinality(Nucl nucl) {
    return card.at(nucl);
}

void RNK::print (const RNK& rnk){
    char Letters[4] = {'T', 'C', 'A', 'G'};

    if(rnk.size != 0) {
        for(size_t i = 0; i < rnk.size; ++i) {
            std::cout << Letters[rnk.get_nucl(i)] << " ";
        }
        std::cout << std::endl;
    }
    else
        std::cout << "rnk is empty" << std::endl;
}

