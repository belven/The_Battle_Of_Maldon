///////////////////////////////////////////////////////////
//  Part.cpp
//  Implementation of the Class Part
//  Created on:      25-Apr-2015 08:58:36
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"


Part::Part(){

}


Part::~Part(){

}

double Part::GetVitality(){
	return vitality;
}


void Part::SetVitality(double newVal){
	vitality = newVal;
}

PartEnums::PartType Part::GetPartType(){
	return partType;
}


void Part::SetPartType(PartEnums::PartType value){
	partType = value;
}