#include "gtest/gtest.h"
#include "utils.hpp"

using namespace observers::utils;

struct A;
struct B;
struct C;
struct D;
struct E;

TEST(Utils, IsTypeInList){
    ASSERT_TRUE(( is_type_in_list<A, A>() ));
    ASSERT_TRUE(( is_type_in_list<A, B, A>() ));
    ASSERT_TRUE(( is_type_in_list<A, B, A, C>() ));

    ASSERT_FALSE(( is_type_in_list<A, B>() ));
    ASSERT_FALSE(( is_type_in_list<A, B, C, B>() ));
}

TEST(Utils, CountTypeInList){
    ASSERT_EQ(1u, ( count_type_in_list<A, A>() ));
    ASSERT_EQ(2u, ( count_type_in_list<A, B, A, C, A>() ));
    ASSERT_EQ(3u, ( count_type_in_list<A, A, A, A>() ));
    ASSERT_EQ(0u, ( count_type_in_list<A, B, B>() ));
    ASSERT_EQ(0u, ( count_type_in_list<A, B, C, B>() ));
}

TEST(Utils, UniqueList){
    ASSERT_TRUE(( unique_list<A>() ));
    ASSERT_TRUE(( unique_list<A, B>() ));
    ASSERT_TRUE(( unique_list<A, B, C>() ));
    
    ASSERT_FALSE(( unique_list<A, A>() ));
    ASSERT_FALSE(( unique_list<A, B, A, C>() ));
}

TEST(Utils, IndexInList){
    ASSERT_EQ(0u, ( index_in_list<A, A>() ));
    ASSERT_EQ(1u, ( index_in_list<A, B, A, C>() ));
    ASSERT_EQ(2u, ( index_in_list<A, B, C, A, B, B>() ));
}