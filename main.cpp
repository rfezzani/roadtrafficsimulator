/*
	R. Fezzani 10/2016

	Circular road simulator.
*/

#include <iostream>
#include <cstddef>
#include <stdlib.h>

#include "roadSegment.hpp"

int main( int argc, const char* argv[] )
{
	
	double length = 100.0;
	std::size_t num_vehicles = 9;
	
	if ( argc == 3 ){
		length = atof( argv[1] );
		num_vehicles = (std::size_t)atoi( argv[2] );
	}

	std::cout << "The road is a circle of radius " << (length/ 6.283185307179586)<< "m." << std::endl;
	
	// --- Time loop parameters
	double simulation_duration = 10.0;
	double fps = 30.0;
	double dt = 1.0/fps;
	double t = 0.0;

	// --- Obstacle simulation
	double perturbation_date = 0.2*simulation_duration;
	std::size_t idx = 5;
	bool perturb = true;

	// --- Road initialization
	RoadSegment road = RoadSegment(length, num_vehicles);

	// --- Road traffic simulation
	while (t < simulation_duration){
		std::cout << "T = " << t << std::endl;

		if ((t > perturbation_date) and perturb){
			std::cout << "----- Chicken Run -----" << std::endl;
		
			road.perturb(idx);
			perturb = false;
		}
		
		road.update_traffic(dt);
		for(auto & v: road.vehicles()){
			v.print();
			std::cout << "\tCorresponds to the angle " << v.get_position_on_circle(length) << " rad." << std::endl;
		}
		
		t += dt;
		
	}
	
}
