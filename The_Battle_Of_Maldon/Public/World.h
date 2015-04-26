///////////////////////////////////////////////////////////
//  World.h
//  Implementation of the Class World
//  Created on:      25-Apr-2015 21:41:53
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_E2BC511F_E6E9_41f3_B7E9_A98332997C93__INCLUDED_)
#define EA_E2BC511F_E6E9_41f3_B7E9_A98332997C93__INCLUDED_

#include "Environment.h"
#include "LivingEntity.h"
#include "BaseVolume.h"
#include <vector>

class World
{

public:
	World();
	virtual ~World();

	std::vector<Environment*> GetEnvironments();
	void SetEnvironments(std::vector<Environment*> newVal);
	std::vector<ALivingEntity*> GetCurrentLivingEntities();
	void SetCurrentLivingEntities(std::vector<ALivingEntity*> newVal);
	std::vector<ABaseVolume*> GetCurrentSites();
	void SetCurrentSites(std::vector<ABaseVolume*> newVal);

private:
	std::vector<Environment*> environments;
	std::vector<ALivingEntity*> currentLivingEntities;
	std::vector<ABaseVolume*> currentSites;

};
#endif // !defined(EA_E2BC511F_E6E9_41f3_B7E9_A98332997C93__INCLUDED_)
