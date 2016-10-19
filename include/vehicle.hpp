/*
	R. Fezzani 10/2016

	Vehicle object describes the properties of a mooving vehicle with
	cyclic boundary condition.

	Parameters:
	----------

	reaction_time : driver reaction time (in seconds),
	safety_dist : safety distance (in meters),
	length : length of the vehicle (in meters),
	position : linear vehicle position on the road (in meters),
	velocity : vehicle veocity (in meters per seconds),
	max_velocity : maximum vehicle veocity (in meters per seconds),
	relative_position : current dist to precedent vehicle (in meters),
	time_since_perturbation : time since the perturbation is observed (in seconds),
	precedent_vehicle : pointer to the precedent vehicle.

*/

#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#define PI 3.141592653589793

#include <iostream>
#include <algorithm>

class Vehicle{
public:

	// --- Constructors
	Vehicle(){
		reaction_time_ = 3.0;
		safety_dist_ = 10.0;
		length_ = 0.0;
		position_ = 2.0;
		velocity_ = 2.0;
		max_velocity_ = 2.0;
		relative_position_ = 10.0;
		time_since_perturbation_ = 0.0;
		precedent_vehicle_ = NULL;
	}

	// --- Access to private data
	double position(){return position_;}
	double length(){return length_;}
	double safety_dist(){return safety_dist_;}
	double relative_position(){return relative_position_;}
	double reaction_time(){return reaction_time_;}
	double velocity(){return velocity_;}
	Vehicle precedent_vehicle(){return *precedent_vehicle_;}
	

	// --- Setters

	void set_precedent_vehicle(Vehicle *vehicle, double cycle_length){
		precedent_vehicle_ = vehicle;
		update_relative_position(cycle_length);
	}
	
	void set_position(double position, double cycle_length){
		position_ = fmod(position, cycle_length);
	}

	void reset_time_since_perturbation(){
		time_since_perturbation_ = 0.0;
	}

	// --- Updaters

	void update_position(double dt, double cycle_length){
		position_ += dt*velocity_;
		if (position_ > cycle_length)
			position_ -= cycle_length;
	}

	void update_relative_position(double cycle_length){
		
		relative_position_ = (precedent_vehicle_)->position()-(precedent_vehicle_)->length()-position_;
		if (relative_position_ < 0.0){
			relative_position_ += cycle_length;
		}
	}

	void update_time_since_perturbation(double dt){
		time_since_perturbation_ += dt;
	}

	void update_velocity(){
		if (time_since_perturbation_>=reaction_time_){
			// --- Deceleration
			velocity_ *= 0.5;
		}else{
			// --- Keep going
			velocity_ = std::min(max_velocity_, 1.2*velocity_);
		}	
	}

	// --- Utils

	double get_position_on_circle(double cycle_length){
		// --- Returns in radian the angle defining the position of the
		// --- vehicle on a circle of circonference cycle_length

		return position_*2.0*PI/cycle_length;
	}

	void print(){
		std::cout << "Position = " << position_ << ", Velocity = " << velocity_ << std::endl;
	}

private:

	// General attributes
	double reaction_time_;
	double safety_dist_;
	double length_;
	double position_;
	double velocity_;
	double max_velocity_;
	double time_since_perturbation_;
	double relative_position_;
	Vehicle *precedent_vehicle_;
};
	
#endif // VEHICLE_HPP
