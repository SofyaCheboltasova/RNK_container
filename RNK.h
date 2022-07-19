#pragma once
#include "Vector.h"
#include <unordered_map>
#include <stdio.h>

class RNK {
    typedef std::unordered_map <Nucleotide, int, std::hash<int>> map;
public:
    size_t size;
    Vector vector;
    map card;

    RNK();
    RNK(size_t size1, Nucl nucleotide);
    RNK(const RNK &other);
    ~RNK();

    class Nucl_ref {
    public:
        Nucl_ref(size_t idx, RNK& rnk);
        ~Nucl_ref() = default;
        Nucl_ref& operator=(Nucl nucl);
        explicit operator Nucl();

    private:
        size_t index;
        RNK* rnk = nullptr;
    };

    void push(const RNK& other);
    void push(Nucl nucl);

    bool operator==(const RNK& rnk1) const;
    bool operator!=(const RNK& rnk1) const;
    RNK operator+(const RNK& rnk1) const;
    Nucl operator[] (size_t idx) const;
    Nucl_ref operator[](size_t idx);
    RNK& operator=(const RNK& rnk);
    RNK operator!() const;

    bool is_complementary(const RNK &other) const;
    Nucl get_nucl(size_t idx) const;
    RNK split(size_t idx) const;
    size_t length() const;
    void trim(size_t idx);

    void set_nucl(size_t index, Nucl nucl);
    int cardinality(Nucl nucleotide);
    static void print (const RNK& rnk);
};
