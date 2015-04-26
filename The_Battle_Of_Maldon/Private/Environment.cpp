///////////////////////////////////////////////////////////
//  Environment.cpp
//  Implementation of the Class Environment
//  Created on:      25-Apr-2015 21:41:55
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"
#include "Environment.h"

Environment::Environment(){

}

Environment::~Environment(){

}

std::vector<Weather*> Environment::GetWeather(){
	return weather;
}


void Environment::SetWeather(std::vector<Weather*> newVal){
	weather = newVal;
}


Weather* Environment::GetCurrentWeather(){
	return currentWeather;
}


void Environment::SetCurrentWeather(Weather* newVal){
	currentWeather = newVal;
}


Weather* Environment::GetDefaultWeather(){
	return defaultWeather;
}


void Environment::SetDefaultWeather(Weather* newVal){
	defaultWeather = newVal;
}