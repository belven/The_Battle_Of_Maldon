///////////////////////////////////////////////////////////
//  PersonBody.cpp
//  Implementation of the Class PersonBody
//  Created on:      25-Apr-2015 14:02:41
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"
#include "PersonBody.h"


PersonBody::PersonBody(){
	GetParts().push_back(new Arm(PartEnums::LeftArm));
	GetParts().push_back(new Arm(PartEnums::RightArm));
	GetParts().push_back(new Leg(PartEnums::RightLeg));
	GetParts().push_back(new Leg(PartEnums::RightLeg));
	GetParts().push_back(new Chest(PartEnums::Chest));
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