/*
 * subject_base.hpp
 *
 *  Created on: Aug 19, 2020
 *      Author: benny
 */

#ifndef OBSERVERS_SUBJECT_BASE_HPP_
#define OBSERVERS_SUBJECT_BASE_HPP_

#include "logging.hpp"
#include "subject_events.hpp"

#include <memory>

namespace observers {

template <typename TDerived>
class SubjectBase {

protected:
    static std::unique_ptr<TDerived> instance;

    SubjectEvents<TDerived> events;

    SubjectBase() = default;

public:
    
    // Subject cannot be created by means other than calling 'create' for TDerived
    SubjectBase(SubjectBase const &) = delete;
    SubjectBase & operator=(SubjectBase const &) = delete;

    friend std::unique_ptr<TDerived> std::make_unique<TDerived>();
    static void create(){
        assert_with_message(instance == nullptr, "Subject already exists");
        instance = std::make_unique<TDerived>();
    }

    virtual ~SubjectBase() = default;

    static void assert_existance(){
        assert_with_message(instance != nullptr, "Subject was not created, or deleted");
    };

    static void delete_instance(){
        assert_existance();

        if (0 != number_of_attached_observers()){
            assert_with_message(false, "Subject instance cannot be deleted as "
                                       "there are observers attached to it");
        }
        instance.reset(nullptr);
    }

    [[nodiscard]] static bool exists(){return !(instance == nullptr);}

    [[nodiscard]] static size_t number_of_attached_observers() {
        assert_existance();
        return instance->events.number_of_attached_handles();
    }

    static void notify(std::string const & message){
        assert_existance();
        return instance->events.notify(message);
    }


    template <template <typename T> class TEventHandle>
    static void attach_event_handle(TEventHandle<TDerived> & event_handle){
        assert_existance();
        instance->events.attach_event_handle(event_handle);
    }

    template <template <typename T> class TEventHandle>
    static void detach_event_handle(TEventHandle<TDerived> & event_handle){
        assert_existance();
        instance->events.detach_event_handle(event_handle);
    }
};

// Initialization of the static instance pointer
template <typename TDerived>
std::unique_ptr<TDerived> SubjectBase<TDerived>::instance(nullptr);


} // namespace observers

#endif /* OBSERVERS_SUBJECT_BASE_HPP_ */
