/*
 * event_handle.hpp
 *
 *  Created on: Aug 19, 2020
 *      Author: benny
 */

#ifndef OBSERVERS_EVENT_HANDLE_HPP_
#define OBSERVERS_EVENT_HANDLE_HPP_

#include <memory>

// TODO: temp
#include <string>

namespace observers {

template <typename TSubject>
class EventHandle{

private:

    struct AbstractHandle {
        virtual ~AbstractHandle() = default;

        virtual void test_event(std::string const & message) const = 0;
    };

    template <typename TObserver>
    struct HandleImplementation : public AbstractHandle {
    	TObserver & observer;

        HandleImplementation(TObserver & observer_) : observer(observer_){}
        virtual ~HandleImplementation() = default;


        virtual void test_event(std::string const & message) const {
        	observer.template test_event<TSubject>(message);
        }
    };

    std::unique_ptr<AbstractHandle> impl;

public:

    template <typename TObserver>
    explicit EventHandle(TObserver & observer)
	: impl(std::make_unique<HandleImplementation<TObserver> >(observer)){
    	// Make sure the TObserver observes 'TSubject'
    	static_assert(TObserver::template observes_subject<TSubject>());
    }

    void test_event(std::string const & message) const {
        impl->test_event(message);
    }

};

} // namespace observers



#endif /* OBSERVERS_EVENT_HANDLE_HPP_ */
