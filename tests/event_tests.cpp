#include "gtest/gtest.h"
#include "subject_base.hpp"
#include "observer_base.hpp"
#include <array>

using namespace observers;

namespace event_tests {

    class SubjectA : public SubjectBase<SubjectA>{
    public:
        static auto constexpr name = "Subject_A";
    };

    class SubjectB : public SubjectBase<SubjectB>{
    public:
        static auto constexpr name = "Subject_B";
    };

    template <typename TDerived, typename... TSubjects>
    class NotifiableObserver : public ObserverBase<TDerived, TSubjects...>{
    public:

        std::array<unsigned, sizeof...(TSubjects)> num_notified;
        std::string name;
        NotifiableObserver(std::string const & name_) : num_notified(), name(name_){}

        template <typename Subject>
        void notify(std::string const & message) {
            num_notified[utils::index_in_list<Subject, TSubjects...>()]++;

            std::cout << "Observer " <<  name << " was notified by "
            << Subject::name << ": " << message << std::endl;
        }
    };

    class ObserverA : public NotifiableObserver<ObserverA, SubjectA>{
    public:
        ObserverA(std::string const & name_ = "DefaultObserver_A") : NotifiableObserver(name_){}
    };

    class ObserverAB : public NotifiableObserver<ObserverAB, SubjectA, SubjectB>{
    public:
        ObserverAB(std::string const & name_ = "DefaultObserver_AB") : NotifiableObserver(name_){}
    };

    class EventsWithSubjects : public ::testing::Test {
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

} // namespace event_tests
using namespace event_tests;


TEST(Events, AttachWithNonexistingSubject) { 
    ASSERT_DEATH(ObserverA(), "Subject was not created");
}

TEST(Events, NotifyNonexistingSubject) {
    ASSERT_DEATH(SubjectA::notify(""), "Subject was not created");
}

TEST_F(EventsWithSubjects, SingleNotify) {
    ObserverA a;
    ASSERT_EQ(0u, a.num_notified[0]);
    SubjectA::notify("");
    ASSERT_EQ(1u, a.num_notified[0]);
}

TEST_F(EventsWithSubjects, NotifyDetached) {
    ObserverA a;
    a.detach_from_events();
    SubjectA::notify("");
    ASSERT_EQ(0u, a.num_notified[0]);
}

TEST_F(EventsWithSubjects, MultipleNotify) {
    using NumNotifiedArray = std::array<unsigned, 2u>;
    ObserverAB ab;
    ASSERT_EQ((NumNotifiedArray{0, 0}), ab.num_notified);
    SubjectA::notify("");
    ASSERT_EQ((NumNotifiedArray{1, 0}), ab.num_notified);
    SubjectB::notify("");
    ASSERT_EQ((NumNotifiedArray{1, 1}), ab.num_notified);
    SubjectA::notify("");
    ASSERT_EQ((NumNotifiedArray{2, 1}), ab.num_notified);
}