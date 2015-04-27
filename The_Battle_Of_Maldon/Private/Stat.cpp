///////////////////////////////////////////////////////////
//  Stat.cpp
//  Implementation of the Class Stat
//  Created on:      27-Apr-2015 19:02:38
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"
#include "Stat.h"

Stat::Stat(double value){
	SetValue(value);
}


Stat::~Stat(){

}


double Stat::GetValue(){
	return value;
}


void Stat::SetValue(double newVal){
	value = newVal;
}