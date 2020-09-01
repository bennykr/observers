/*
 * observer_base.hpp
 *
 *  Created on: Aug 19, 2020
 *      Author: benny
 */

#ifndef OBSERVERS_OBSERVER_BASE_HPP_
#define OBSERVERS_OBSERVER_BASE_HPP_

#include "logging.hpp"
#include "event_handles_container.hpp"
#include "utils.hpp"

#include <memory>

namespace observers {

template <typename TDerived, typename... TSubjects>
class ObserverBase {
private:
    using EventHandles = EventHandlesContainer<TSubjects...>;

    std::unique_ptr<EventHandles> event_handles;

protected:

    ObserverBase(){
        attach_to_events();
    }

    ObserverBase(ObserverBase const & other) = delete;
    void operator=(ObserverBase const & other) = delete;

    ObserverBase(ObserverBase && other)
    : event_handles(nullptr){
    	if (other.is_attached()){
    		other.detach_from_events();
            attach_to_events();
    	}
    }


    void operator=(ObserverBase && other){
    	event_handles.reset(nullptr);

    	if (other.is_attached()){
    		other.detach_from_events();
            attach_to_events();
    	}
    }

    virtual ~ObserverBase() = default;

public:

    void attach_to_events(){
    	assert_with_message(nullptr == event_handles, "Observer already attached");
    	event_handles = std::make_unique<EventHandles>(*static_cast<TDerived*>(this));
    }

    void detach_from_events(){
    	event_handles.reset(nullptr);
    }

    bool is_attached() const {return event_handles != nullptr;}

    template<typename TQuery>
    static bool constexpr observes_subject(){
        return utils::is_type_in_list<TQuery, TSubjects...>();
    }


};


} // namespace observers



#endif /* OBSERVERS_OBSERVER_BASE_HPP_ */
