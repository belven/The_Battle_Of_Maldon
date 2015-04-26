///////////////////////////////////////////////////////////
//  Weather.cpp
//  Implementation of the Class Weather
//  Created on:      25-Apr-2015 21:41:57
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"
#include "Weather.h"

Weather::Weather(){

}

Weather::~Weather(){

}

double Weather::GetDuration(){
	return duration;
}

void Weather::SetDuration(double newVal){
	duration = newVal;
}
