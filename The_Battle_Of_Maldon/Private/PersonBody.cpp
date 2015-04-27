///////////////////////////////////////////////////////////
//  PersonBody.cpp
//  Implementation of the Class PersonBody
//  Created on:      25-Apr-2015 14:02:41
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"
#include "PersonBody.h"


PersonBody::PersonBody(){
	GetParts().Add(new Arm(PartEnums::LeftArm));
	GetParts().Add(new Arm(PartEnums::RightArm));
	GetParts().Add(new Leg(PartEnums::RightLeg));
	GetParts().Add(new Leg(PartEnums::RightLeg));
	GetParts().Add(new Chest(PartEnums::Chest));
}



PersonBody::~PersonBody(){

}

double PersonBody::GetTotalVitality(){
	double health = 0.0;
	for (Part* p : GetParts()){
		health += p->GetVitality();
	}

	return health;
}