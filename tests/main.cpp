#include "gtest/gtest.h"
#include "subject_base.hpp"
#include "observer_base.hpp"

#include <string>

using namespace observers;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::GTEST_FLAG(filter) = "*FILTER*";
    return RUN_ALL_TESTS();
}

class Sbj1 : public SubjectBase<Sbj1>{
public:
    static auto constexpr name = "Sbj1";
};

class Sbj2 : public SubjectBase<Sbj2>{
public:
    static auto constexpr name = "Sbj2";
};

class Obs : public ObserverBase<Obs, Sbj1, Sbj2>{
public:
    std::string const name;
    Obs(std::string const & name_) : name(name_){}

    template <typename Sbj>
    void test_event(std::string const & message) const {
        std::cout << name << " - " << Sbj::name << ": " << message << std::endl;
    }
};

TEST(TITLE, SUBTITLE) {
    
    Sbj1::create();
    Sbj2::create();
    Sbj1::get_instance();

    Sbj1::get_events().test_event("test1_before");

    Obs observer1{"observer1"};

    Sbj1::get_events().test_event("test2_after");

    Sbj2::get_events().test_event("test3_after");


    ASSERT_EQ(1, 1);
}