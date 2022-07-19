#include <iostream>
#include <gtest/gtest.h>
#include "RNK.h"

RNK test(size_t size) {
    RNK rnk;
    for (size_t i = 0; i < size; ++i) {
        rnk.push(A);
    }
    return rnk;
}


TEST(get_nucl, push_nucl){
    RNK rnk1 = test(5);
    RNK rnk2(5, A);
    ASSERT_EQ(rnk1, rnk2);
}

TEST(push, push_rnk) {
    RNK rnk1(10, A);
    RNK rnk2;
    rnk2.push(rnk1);
    ASSERT_EQ(rnk1, rnk2);
}

TEST(get_nucl, construct_rnk){
    RNK rnk1(10, A);
    const RNK& rnk2(rnk1);
    ASSERT_EQ(rnk1, rnk2);
}

TEST(get_nucl, million) {
    RNK rnk = test(1000000);

    ASSERT_EQ(rnk.get_nucl(2), (Nucl)rnk[2]);
}

TEST(get_nucl, appropriation_nucl) {
    RNK rnk(10, A);
    rnk[5] = T;
    ASSERT_EQ((Nucl)rnk[5], T);
}

TEST(get_nucl, appropriation_nuc) {
    const RNK rnk(10, A);
    Nucl nucl;
    nucl = rnk[5];
    ASSERT_EQ(nucl, A);
}

TEST(get_nucl, cardinality) {
    RNK rnk(10, A);
    ASSERT_EQ(rnk.cardinality(A), 10);
}

TEST(get_nucl, is_complemenary) {
    RNK rnk1(10, T);
    RNK rnk2(10, A);
    ASSERT_EQ(rnk1.is_complementary(rnk2), true);
}

TEST(get_nucl, get_nucl){
    RNK rnk1(10, A);
    ASSERT_EQ(rnk1.get_nucl(4), A);
}

TEST(size, length) {
    RNK rnk(100, A);
    ASSERT_EQ(rnk.size, rnk.length());
}

TEST(operators, add) {
    RNK rnk1(20, T);
    RNK rnk2(10, A);
    ASSERT_EQ( rnk1 + rnk2, rnk1 + rnk2);
}

TEST(operators, equals) {
    RNK rnk1(10, A);
    RNK rnk2(10, A);
    bool b1 = false, b2 = true;
    if(rnk1 == rnk2) b1 = true;
    ASSERT_EQ( b1, b2);
}

TEST(operators, not_equals) {
    RNK rnk1(10, A);
    RNK rnk2(10, A);
    rnk1[5] = T;
    ASSERT_EQ(rnk1 != rnk2 , true);
}

TEST(operators, negation) {
    RNK rnk1(10, A);
    RNK rnk2(10, A);
    bool b1 = false, b2 = true;
    if(rnk1 != !rnk2) b1 = true;
    ASSERT_EQ( b1, b2);
}

TEST(operators, appropriation) {
    RNK rnk1(10, A);
    RNK rnk2;
    rnk2 = rnk1;
    ASSERT_EQ( rnk1, rnk2);
}

TEST(trim, rnk) {
    RNK rnk(5, A);
    rnk.trim(3);
    ASSERT_EQ(rnk.size, 3);
}

TEST(get_nucl, split) {
    RNK rnk1(5, T);
    RNK rnk2(3, T);
    ASSERT_EQ(rnk1.split(2), rnk2);
}

TEST(get_nucl, print){
    RNK rnk1(5, A);
    RNK::print(rnk1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}