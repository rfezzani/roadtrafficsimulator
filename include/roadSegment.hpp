/*
	R. Fezzani 10/2016

	RoadSegment object describes road traffic over a given segment.
	Vehicles in this implementation do not overtake.
	The road is supposed of circular shape.

	Parameters:
	----------

	len : the len of the obseved segment (in meters),
  vehicles : vector of vehicles
	
*/

#ifndef ROADSEGMENT_HPP
#define ROADSEGMENT_HPP

#include <iostream>
#include <cstddef>
#include <vector>

#include "vehicle.hpp"


class RoadSegment{
public:

	// --- Constructors
	RoadSegment(){
		length_ = 0.0;
		vehicles_ = std::vector<Vehicle>();
	}

	RoadSegment( double length, std::size_t num_vehicles){
		length_ = length;
		vehicles_ = std::vector<Vehicle>(num_vehicles,Vehicle());
		for ( std::size_t i=0; i<(num_vehicles-1); ++i){
			vehicles_[i+1].set_position(vehicles_[i].position()+
																	vehicles_[i].safety_dist()+
																	vehicles_[i+1].length(), length_);
			vehicles_[i].set_precedent_vehicle(&vehicles_[i+1],length_);
		}

		vehicles_[num_vehicles-1].set_precedent_vehicle(&vehicles_[0], length_);
	}

	std::vector<Vehicle> vehicles(){return vehicles_;}

	// --- Simulate a perturbation on the road
	void perturb(std::size_t idx){
		// --- A chicken crosses the road on the way of perturbed_vehicle

		vehicles_[idx].update_time_since_perturbation(vehicles_[idx].reaction_time());

	}

	// --- Traffic update after a time step of dt
	void update_traffic(double dt){
			
		// --- Update all effective and relative vehicles positions
		for (auto &v: vehicles_){
			v.update_velocity();
			v.update_position(dt, length_);
		}

		for (auto &v: vehicles_){
			v.update_relative_position(length_);
		}

		// --- For each vehicle
		for (auto &v: vehicles_){
			if (v.relative_position() < v.safety_dist()){
				// --- Reaction time update 
				v.update_time_since_perturbation(dt);
			}else{
				// --- Release presure
				v.reset_time_since_perturbation();
			}

		}
	}
	
private:
	
	// --- General attributes
	double length_;
	std::vector<Vehicle> vehicles_;
		
};

#endif // ROADSEGMENT_HPP
