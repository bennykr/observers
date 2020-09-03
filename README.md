# observers
A meta-programming header-only library for the implementation of the observer pattern, with variadic (singleton) subjects per observer.

--------------------------------------------
**Usage example:**

Create subjects:

    class SubjectA : public SubjectBase<SubjectA>{
        static auto constexpr name = "Subject_A";
    };
    
    class SubjectB : public SubjectBase<SubjectB>{
        static auto constexpr name = "Subject_B";
    };
    
    SubjectA::create();
    SubjectB::create();

Create Observers:

    class Observer : public ObserverBase<Observer, SubjectA, SubjectB>{
    public:
        template <typename Subject>
        void notify(std::string const & message) {
            std::cout << "Observer was notified by "
            << Subject::name << ": " << message << std::endl;
        }
    };
    
Notify:

    SubjectA::notify("some-message");
    
This will cause the output:

    Observer was notified by Subject_A: some-message
    
--------------------------------------------------------
**Extensions**
The method `notify` is hard-coded into `SubjectBase`, `SubjectEvents` and `EventHandle`, in addition to the `Observer` class (inheriting from `ObserverBase`).
It can be replaced by a set of different methods, but doing so will require duplicating the code of `notify` in the locations mentioned above.

I would like to have only two occurances of the `notify` method: 
1. In the `Subject` class inheriting from `SubjectBase`.
2. In the `Observer` class inheriting from `ObserverBase`.
Any suggestions on how to do this will be appreciated.
