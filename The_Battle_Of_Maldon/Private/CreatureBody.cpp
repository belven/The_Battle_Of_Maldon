///////////////////////////////////////////////////////////
//  CreatureBody.cpp
//  Implementation of the Class CreatureBody
//  Created on:      25-Apr-2015 14:05:42
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"
#include "CreatureBody.h"


CreatureBody::CreatureBody(){

}



CreatureBody::~CreatureBody(){

}

double CreatureBody::GetTotalVitality(){
	double health = 0.0;
	for (Part* p : GetParts()){
		health += p->GetVitality();
	}

	return health;
}