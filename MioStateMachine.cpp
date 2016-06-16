#include "MioStateMachine.h"
using namespace mioware;
#include <iostream>
#include <assert.h>

//
State * State::create()
{
	auto ptr = new (std::nothrow) State();
	return ptr;
}

void State::release(){
	delete this;
}

State::State() {

}

State::~State(){
}

StateMachine::StateMachine() {
	
}

StateMachine::~StateMachine(){
	for (auto it : mStateMap) {
		(it.second)->release();
	}
	mStateMap.clear();
}
 
void StateMachine::deleteState(const std::string& stateName) {
	auto state = mStateMap[stateName];
	mStateMap.erase(stateName);
	state->release();
}

void StateMachine::addState(State* state){
	if (state != nullptr) { 
		mStateMap[state->stateName] = state;
	}
}
 
bool mioware::StateMachine::transition(const std::string & to){
	return performTransition( mStateMap[to]);
}


bool StateMachine::performTransition(State * from, State * to){
	if (to == nullptr) return false; 
	mStateMap[from] = mStateMap[mCurrentStateName];
	this->StateLeave(from);
	this->StateEnter(to);

	return false;
}

void StateMachine::StateEnter(State* state) {
	if (state && state->enterFunc) {
		state->transitionType = StateTransitionType::kEnter;
		mCurrentStateName = state->stateName;
		state->enterFunc();
	}
}

void StateMachine::StateLeave(State* state) {
	if (state && state->leaveFunc) {
		state->transitionType = StateTransitionType::kLeave;
		state->leaveFunc();
	}
}

void StateMachine::tick() {
	auto state = mStateMap[mCurrentStateName];
	if (state && state->tickFunc != nullptr ) {
		state->tickFunc();
	}
}
 
