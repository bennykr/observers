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

#define assert_with_message(exp, msg) assert(((void)msg, exp))

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

    // Called directly only on program exit. Called indirectly after `delete_instance`.
    virtual ~SubjectBase() = default;

    static void delete_instance(){
        assert(instance != nullptr);

        if (0 != get_events().number_of_attached_handles()){
        	assert_with_message(false, "Subject instance cannot be deleted as "
        				               "there are observers attached to it.");
        }
        instance.reset(nullptr);
    }

    static TDerived & get_instance(){
        assert(instance != nullptr);
        return *instance;
    }

    static SubjectEvents<TDerived> & get_events(){
        assert(instance != nullptr);
        return instance->events;
    }

    static bool exists(){return !(instance == nullptr);}

    template <template <typename T> class TEventHandle>
    static void attach_event_handle(TEventHandle<TDerived> & event_handle){
        assert(instance != nullptr);
        instance->events.attach_event_handle(event_handle);
    }

    template <template <typename T> class TEventHandle>
    static void detach_event_handle(TEventHandle<TDerived> & event_handle){
        assert(instance != nullptr);
        instance->events.detach_event_handle(event_handle);
    }


    friend std::unique_ptr<TDerived> std::make_unique<TDerived>();
    static void create(size_t const size = 0){
        assert(instance == nullptr);
        instance = std::make_unique<TDerived>();
    }

};

// Initialization of the static instance pointer
template <typename TDerived>
std::unique_ptr<TDerived> SubjectBase<TDerived>::instance(nullptr);


} // namespace observers

#endif /* OBSERVERS_SUBJECT_BASE_HPP_ */
