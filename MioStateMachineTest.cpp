#include "MioStateMachine.h"

void MioStateMachineTest(){
  using namespace mioware;
	StateMachine sm;
	// Walk State 
	State* walk_state = State::create();
	walk_state->stateName = "walk";
	walk_state->enterFunc = []() {
		log("Walk enter");
	};
	walk_state->leaveFunc = []() {
		log("Walk leave");
	};

	walk_state->tickFunc = []() {
		log("Walk tick");
	};
	sm.addState(walk_state);
	 
	// Run State
	State* run_state = State::create();
	run_state->stateName = "run";
	run_state->enterFunc = []() {
		log("Run enter");
	};
	run_state->leaveFunc = []() {
		log("Run leave");
	};

	run_state->tickFunc = []() {
		log("Run tick");
	};
	sm.addState(run_state);
	//
	
	sm.transition("walk");
	sm.tick();

	sm.transition("run");
	sm.tick();
	sm.tick();
}
