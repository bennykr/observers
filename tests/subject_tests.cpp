#include "gtest/gtest.h"
#include "subject_base.hpp"

using namespace observers;

class Subject : public SubjectBase<Subject>{
public:
    static auto constexpr name = "Subject";
};

TEST(Subject, Nonexisting) {
    ASSERT_FALSE(Subject::exists());
    ASSERT_DEATH((void) Subject::get_instance(), "not created");
}

TEST(Subject, Create) {
    Subject::create();
    ASSERT_TRUE(Subject::exists());
    
    Subject::delete_instance();
}

TEST(Subject, MultipleCreate) {
    Subject::create();
    ASSERT_DEATH(Subject::create(), "already exists");

    Subject::delete_instance();
}

TEST(Subject, DeleteNonexisting) {
    ASSERT_DEATH(Subject::delete_instance(), "not created");
}

TEST(Subject, Delete) {
    Subject::create();
    Subject::delete_instance();
    ASSERT_FALSE(Subject::exists());
}


