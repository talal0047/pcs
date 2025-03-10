#pragma once

#include <unordered_map>
#include <string>
#include <ostream>
#include <fstream>
#include <vector>

#include "pcs/lts/state.h"
#include "pcs/common/log.h"

namespace pcs {

	/**
	 * @brief Labelled Transition System: comprised of states and transitions to other states 
	 * @tparam KeyT: the data type used to defined keys/state names. E.g std::string, std::vector<std::string>
	 * @tparam TransitionT : defines the data type used to represent transitions. E.g. std::string, CompositeOperation
	 * @tparam HashF: the Hash functor for keys. Defaults to std::hash<KeyT>>.
	 */
	template <typename KeyT = std::string, typename TransitionT = std::string, typename HashF = std::hash<KeyT>>
	class LTS {
	public:
		using State = pcs::State<KeyT, TransitionT>;
	private:
		std::unordered_map<KeyT, State, HashF> states_;
		KeyT initial_state_;
	public:
		LTS() = default;

		LTS(const KeyT& initial_state, bool create_initial=true) {
			SetInitialState(initial_state, create_initial);
		}

		~LTS() = default;

		const std::unordered_map<KeyT, State, HashF>& states() const {
			return states_;
		}

		const KeyT& initial_state() const {
			return initial_state_;
		}

		void set_initial_state(const KeyT& state, bool create_if_not_exists=true) {
			if (!HasState(state) && create_if_not_exists) {
				AddState(state, State());
			}
			initial_state_ = state;
		}

		bool HasState(const KeyT& key) const {
			return states_.contains(key);
		}

		size_t NumOfStates() const {
			return states_.size();
		}

		size_t NumOfTransitions() const {
			size_t total = 0;
			for (const auto& [k, v] : states_) {
				total += v.transitions_.size();
			}
			return total;
		}

		/**
		 * @brief: Removes a given state but _allows_ dangling transitions to exist from other states to the now deleted state 
		 * @note: the State which is the initial state may also be removed, but formally, a LTS does not need initial states
		 */
		bool EraseShallow(const KeyT& key) {
			if (HasState(key)) {
				states_.erase(key);
				return true;
			}
			return false;
		}

		/**
		 * @brief Removes a given state and then checks for dangling transitions with all other states and deletes such transitions
		 */
		bool EraseDeep(const KeyT& key) {
			if (HasState(key)) {
				states_.erase(key);
				for (auto& [k, v] : states_) {
					typename std::vector<std::pair<TransitionT, KeyT>>::iterator it = v.transitions_.begin();
					while (it != v.transitions_.end()) {
						if (it->second == key) {
							v.transitions_.erase(it++);
						} else {
							++it;
						}
					}
				}
				return true;
			}
			return false;
		}

		void AddTransition(const KeyT& start_state, const TransitionT& label, const KeyT& end_state, 
		                   bool create_missing_states = true) {
			if (!HasState(start_state) && create_missing_states) {
				AddState(start_state, State());
			}
			if (!HasState(end_state) && create_missing_states) {
				AddState(end_state, State());
			}

			State& s = states_.at(start_state);
			s.AddTransition(label, end_state);
		}

		/**
		 * @brief AddTransition should be preferred as the method for creating State objects by creating them as needed with transitions. 
		 */
		bool AddState(const KeyT& key) {
			return AddState(key, State());
		}

		bool operator==(const LTS& other) const {
			return (initial_state_ == other.initial_state_) && (states_ == other.states_);
		}

		State& operator[](const KeyT& key) {
			return states_[key];
		}

		const State& operator[](const KeyT& key) const {
			return states_.at(key);
		}

		template <typename _KeyT, typename _TransitionT, typename _HashF>
		friend std::ostream& operator<<(std::ostream& os, const LTS<_KeyT, _TransitionT, _HashF>& lts);

		template <typename _KeyT, typename _TransitionT, typename _HashF>
		friend std::ofstream& operator<<(std::ofstream& os, const LTS<_KeyT, _TransitionT, _HashF>& lts);

	private:
		bool AddState(const KeyT& name, State&& state) {
			if (!HasState(name)) {
				states_.emplace(name, std::move(state));
				return true;
			}
			return false;
		}

		bool AddState(const KeyT& name, const State& state) {
			if (!HasState(name)) {
				states_.emplace(name, state);
				return true;
			}
			return false;
		}
	};

}

/* 
	@Todo: unordered map STL container
*/

#include "pcs/lts/writers.h"