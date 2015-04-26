///////////////////////////////////////////////////////////
//  World.cpp
//  Implementation of the Class World
//  Created on:      25-Apr-2015 21:41:53
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"
#include "World.h"


World::World(){

}

World::~World(){

}

std::vector<Environment*> World::GetEnvironments(){
	return environments;
}


void World::SetEnvironments(std::vector<Environment*> newVal){
	environments = newVal;
}


std::vector<ALivingEntity*> World::GetCurrentLivingEntities(){
	return currentLivingEntities;
}


void World::SetCurrentLivingEntities(std::vector<ALivingEntity*> newVal){
	currentLivingEntities = newVal;
}


std::vector<ABaseVolume*> World::GetCurrentSites(){
	return currentSites;
}


void World::SetCurrentSites(std::vector<ABaseVolume*> newVal){
	currentSites = newVal;
}