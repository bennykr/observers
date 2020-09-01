#include "gtest/gtest.h"
#include "subject_base.hpp"
#include "observer_base.hpp"

using namespace observers;

class SubjectA : public SubjectBase<SubjectA>{};

class SubjectB : public SubjectBase<SubjectB>{};

struct ObserverA : public ObserverBase<ObserverA, SubjectA>{
    template <typename> void notify(std::string const &) const {}
};

struct ObserverAB : public ObserverBase<ObserverAB, SubjectA, SubjectB>{
    template <typename> void notify(std::string const &) const {}
};


TEST(Observer, ObservedSubjects){
    EXPECT_TRUE(ObserverA::observes_subject<SubjectA>());
    EXPECT_FALSE(ObserverA::observes_subject<SubjectB>());

    EXPECT_TRUE(ObserverAB::observes_subject<SubjectA>());
    EXPECT_TRUE(ObserverAB::observes_subject<SubjectB>());
}



TEST(Observer, CreateWithNonexistingSubject) {
    ASSERT_FALSE(SubjectA::exists());
	ASSERT_DEATH(ObserverA(), "Subject was not created");
}

class ObserverWithSubjects : public ::testing::Test {
protected:
	virtual void SetUp() {
		SubjectA::create();
        SubjectB::create();
	}

	virtual void TearDown() {
		SubjectA::delete_instance();
        SubjectB::delete_instance();
	}
};

TEST_F(ObserverWithSubjects, CreateAttached) {
    ASSERT_EQ(SubjectA::number_of_attached_observers(), 0u);

	ObserverA a;
    ASSERT_TRUE(a.is_attached());

    ASSERT_EQ(SubjectA::number_of_attached_observers(), 1u);
}

TEST_F(ObserverWithSubjects, Detach) {
	ObserverA a;
    a.detach_from_events();
    ASSERT_FALSE(a.is_attached());

    ASSERT_EQ(SubjectA::number_of_attached_observers(), 0u);
}

TEST_F(ObserverWithSubjects, Reattach) {
	ObserverA a;
    a.detach_from_events();
    a.attach_to_events();
    ASSERT_TRUE(a.is_attached());

    ASSERT_EQ(SubjectA::number_of_attached_observers(), 1u);
}

TEST_F(ObserverWithSubjects, InvalidAttach) {
	ObserverA a;
    ASSERT_DEATH(a.attach_to_events(), "already attached");
}


TEST_F(ObserverWithSubjects, MoveConstructor) {
	ObserverA a1;
    ObserverA a2(std::move(a1));
    ASSERT_FALSE(a1.is_attached());
    ASSERT_TRUE(a2.is_attached());
}

TEST_F(ObserverWithSubjects, MoveAssignment) {
	ObserverA a1;
    ObserverA a2;
    a2 = std::move(a1);
    
    ASSERT_FALSE(a1.is_attached());
    ASSERT_TRUE(a2.is_attached());
}


TEST_F(ObserverWithSubjects, MultipleObserved) {
	ObserverAB ab1;
    ObserverAB ab2(std::move(ab1));
    ASSERT_TRUE(ab2.is_attached());
    ASSERT_FALSE(ab1.is_attached());

    ab1 = std::move(ab2);
    ASSERT_TRUE(ab1.is_attached());
    ASSERT_FALSE(ab2.is_attached());
}