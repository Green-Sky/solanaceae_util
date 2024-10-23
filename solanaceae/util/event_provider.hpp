#pragma once

#include <array>
#include <vector>
#include <cstddef>

template<typename EventI>
struct EventProviderI {
	using enumType = typename EventI::enumType;

	// keeps track of subscriptions for you
	// and destorys them on destruction
	struct SubscriptionReference {
		EventProviderI& _ep;
		EventI* _object {nullptr};
		std::vector<enumType> _subs;

		SubscriptionReference(EventProviderI& ep, EventI* object) :
			_ep(ep), _object(object)
		{
		}

		~SubscriptionReference(void) {
			for (const enumType et : _subs) {
				auto& o_vec = _ep._subscribers.at(static_cast<size_t>(et));
				for (auto o_it = o_vec.cbegin(); o_it != o_vec.cend(); o_it++) {
					if (*o_it == _object) {
						o_vec.erase(o_it);
						break;
					}
				}
			}
		}

		SubscriptionReference& subscribe(const enumType event_type) {
			_ep._subscribers.at(static_cast<size_t>(event_type)).push_back(_object);
			_subs.push_back(event_type);
			return *this;
		}
	};

	virtual ~EventProviderI(void) {};

	// TODO: unsub
	virtual void subscribe(EventI* object, const enumType event_type) {
		_subscribers.at(static_cast<size_t>(event_type)).push_back(object);
	}

	SubscriptionReference newSubRef(EventI* object) {
		return SubscriptionReference{*this, object};
	}

	protected:
		template<typename T>
		bool dispatch(enumType event_type, const T& event) {
			for (auto* zei : _subscribers.at(static_cast<size_t>(event_type))) {
				if (zei->onEvent(event)) {
					return true;
				}
			}
			return false;
		}

	protected:
		std::array<
			std::vector<EventI*>,
			static_cast<size_t>(enumType::MAX)
		> _subscribers;
};

