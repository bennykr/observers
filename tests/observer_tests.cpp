#include "gtest/gtest.h"
#include "subject_base.hpp"
#include "observer_base.hpp"

using namespace observers;

class SubjectA : public SubjectBase<SubjectA>{
public:
    static auto constexpr name = "Subject_A";
};

class SubjectB : public SubjectBase<SubjectB>{
public:
    static auto constexpr name = "Subject_B";
};

class NotifiableObserver {
public:
    std::string name;
    NotifiableObserver(std::string const & name_) : name(name_){}

    template <typename Subject>
    void notify(std::string const & message) const {
        std::cout << "Observer " <<  name << " was notified by "
        << Subject::name << ": " << message << std::endl;
    }
};

class ObserverA : public NotifiableObserver,
                   public ObserverBase<ObserverA, SubjectA>{
public:
    ObserverA(std::string const & name_ = "DefaultObserver_A") : NotifiableObserver(name_){}
};

class ObserverAB : public NotifiableObserver,
                   public ObserverBase<ObserverAB, SubjectA, SubjectB>{
public:
    ObserverAB(std::string const & name_ = "DefaultObserver_AB") : NotifiableObserver(name_){}
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
    ASSERT_EQ(SubjectA::get_events().number_of_attached_handles(), 0u);

	ObserverA a;
    ASSERT_TRUE(a.is_attached());

    ASSERT_EQ(SubjectA::get_events().number_of_attached_handles(), 1u);
}

TEST_F(ObserverWithSubjects, Detach) {
	ObserverA a;
    a.detach_from_events();
    ASSERT_FALSE(a.is_attached());

    ASSERT_EQ(SubjectA::get_events().number_of_attached_handles(), 0u);
}

TEST_F(ObserverWithSubjects, Reattach) {
	ObserverA a;
    a.detach_from_events();
    a.attach_to_events();
    ASSERT_TRUE(a.is_attached());

    ASSERT_EQ(SubjectA::get_events().number_of_attached_handles(), 1u);
}

TEST_F(ObserverWithSubjects, InvalidAttach) {
	ObserverA a;
    ASSERT_DEATH(a.attach_to_events(), "already attached");
}


TEST_F(ObserverWithSubjects, MoveConstructor) {
	ObserverA a1("a1");

    ObserverA a2(std::move(a1));
    ASSERT_FALSE(a1.is_attached());
    ASSERT_TRUE(a2.is_attached());
    ASSERT_EQ(a2.name, "a1");
}

TEST_F(ObserverWithSubjects, MoveAssignment) {
	ObserverA a1("a1");
    ObserverA a2("a2");
    a2 = std::move(a1);
    
    ASSERT_FALSE(a1.is_attached());
    ASSERT_TRUE(a2.is_attached());
    ASSERT_EQ(a2.name, "a1");
}


TEST_F(ObserverWithSubjects, MultipleObserved) {
	ObserverAB ab1("ab1");
    ObserverAB ab2(std::move(ab1));
    ASSERT_TRUE(ab2.is_attached());
    ASSERT_FALSE(ab1.is_attached());

    ab1 = std::move(ab2);
    ASSERT_TRUE(ab1.is_attached());
    ASSERT_FALSE(ab2.is_attached());
}