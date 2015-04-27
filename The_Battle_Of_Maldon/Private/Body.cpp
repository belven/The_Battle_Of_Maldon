///////////////////////////////////////////////////////////
//  Body.cpp
//  Implementation of the Class Body
//  Created on:      25-Apr-2015 09:00:17
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"
#include "Body.h"
#include "Arm.h"
#include "Leg.h"
#include "Head.h"
#include "Chest.h"


Body::Body(){

}


Body::~Body(){

}

TArray<Part*> Body::GetParts(){
	return parts;
}


void Body::SetParts(TArray<Part*> newVal){
	parts = newVal;
}