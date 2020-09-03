#include "gtest/gtest.h"
#include "subject_base.hpp"

using namespace observers;

namespace subject_tests {
    class Subject : public SubjectBase<Subject>{
    public:
        static auto constexpr name = "Subject";
    };
} // namespace subject_tests
using namespace subject_tests;

TEST(Subject, Nonexisting) {
    ASSERT_FALSE(Subject::exists());
    ASSERT_DEATH((void) Subject::number_of_attached_observers(), "not created");
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


