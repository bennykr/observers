/*
 * event_handles_container.hpp
 *
 *  Created on: Aug 19, 2020
 *      Author: benny
 */

#ifndef OBSERVERS_EVENT_HANDLES_CONTAINER_HPP_
#define OBSERVERS_EVENT_HANDLES_CONTAINER_HPP_

#include "event_handle.hpp"
#include "utils.hpp"

namespace observers {

template <typename... TSubjects>
class EventHandlesContainer;

template <typename TSubject, typename... TNextSubjects>
class EventHandlesContainer<TSubject, TNextSubjects...>{
    static_assert(utils::unique_list<TSubject, TNextSubjects...>(),
                  "Duplicate subjects in arguments pack");

public:

    template <typename TObserver>
    explicit EventHandlesContainer(TObserver & observer)
        :event_handle(observer), next_event_handles(observer){
        TSubject::attach_event_handle(event_handle);
    }

    ~EventHandlesContainer(){
        TSubject::detach_event_handle(event_handle);
    }

private:
    EventHandle<TSubject> event_handle;
    EventHandlesContainer<TNextSubjects...> next_event_handles;
};

// Recursion's stopping condition:
template <>
class EventHandlesContainer<>{
public:
    template <typename TObserver>
    explicit EventHandlesContainer(TObserver &){}
};

} // namespace observers



#endif /* OBSERVERS_EVENT_HANDLES_CONTAINER_HPP_ */
