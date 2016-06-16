#ifndef _MIO_STATEMACHINE_H_
#define _MIO_STATEMACHINE_H_

/*
Desc: StateMachine

Date: 2016 06
Author: ade 
*/
// Only Support C11

#include <vector>
#include <unordered_map>
#include <string> 

namespace mioware {
	typedef void(*StateProcFunc)();
	enum class StateTransitionType {
		kUnspecified,
		kEnter,
		kLeave,
	};
	/* 
	为了避免state失效 禁用构造函数 强制所有State都是堆变量
	设置State::constructor State::deconstructor为private
	*/
	class State {
	public:
		static State* create();
		void release();

		std::string stateName;
		StateProcFunc enterFunc;
		StateProcFunc leaveFunc;
		StateProcFunc tickFunc;
		StateTransitionType transitionType; 
	protected:
		State();
		~State(); 
	};

	class StateMachine {
	public:
		StateMachine(); 
		~StateMachine();
		void deleteState(const std::string& stateName);
		void addState(State* state);
		bool transition( const std::string& to );
		void tick();

	protected:
		void StateEnter(State* state);
		void StateLeave(State* state);
		bool performTransition( State* to );
	protected:
		std::unordered_map<std::string, State*> mStateMap;
		std::string mCurrentStateName;

		friend State;
	};
}

#endif //_MIO_STATEMACHINE_H_
