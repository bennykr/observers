/*
 * subject_events.hpp
 *
 *  Created on: Aug 19, 2020
 *      Author: benny
 */

#ifndef OBSERVERS_SUBJECT_EVENTS_HPP_
#define OBSERVERS_SUBJECT_EVENTS_HPP_

#include "logging.hpp"
#include "event_handle.hpp"

#include <set>
#include <string>

namespace observers {



// Forward deceleration, for the purpose of declaring 'Subject' a friend
template <typename TDerived>
class SubjectBase;


template <typename TSubject>
class SubjectEvents{
private:
    // Observers are attached (detached) in EventHandlesContainer
    // using `SubjectBase::attach_event_handle(event_handle)`, which 
    // refers the attachment (detachment) operation to its `events` object.
    // For this purpose it needs to be a friend of the 'SubjectEvents' class.
	template <typename TDerived>
    friend class SubjectBase;

	// One events handle per attached data structure parameterized on TAxis
    std::set<EventHandle<TSubject>*> attached_event_handles;

    void attach_event_handle(EventHandle<TSubject> & event_handle){
    	assert(attached_event_handles.count(&event_handle) == 0);
    	attached_event_handles.insert(&event_handle);
    }

    // Called by base class BaseAxis of TAxis
    void detach_event_handle(EventHandle<TSubject> & event_handle){
        assert(attached_event_handles.count(&event_handle) > 0);
        attached_event_handles.erase(&event_handle);
    }

    // Used to make sure TSubject can safely be deleted.
    // Also used for tests.
    size_t number_of_attached_handles() const {
    	return attached_event_handles.size();
    }

    void notify(std::string const & message){
		for(EventHandle<TSubject> * event_handle : attached_event_handles){
			event_handle->notify(message);
		}
    }
};

} // namespace observers

#endif /* OBSERVERS_SUBJECT_EVENTS_HPP_ */
