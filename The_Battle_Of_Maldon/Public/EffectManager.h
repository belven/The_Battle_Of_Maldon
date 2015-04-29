
#pragma once
#include "Array.h"
#include "Effect.h"
#include <condition_variable>
#include <mutex>

class EffectManager {
public:
	TArray<Effect*> currentEffects = *new TArray<Effect*>();
	TArray<Effect*> effectsToRemove = *new TArray<Effect*>();
	bool beingRed = false;
	//std::condition_variable cv;
	//std::mutex m;

	/*This will check all current effects to see if they need applying or removing*/
	void CheckEffects(float deltaTime){
		/*std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [&]{ return isNotBeingRed(); });
		beingRed = true;*/

		//UE_LOG(LogTemp, Log, TEXT("Checking effects"));


		for (TArray<Effect*>::TConstIterator it = currentEffects.CreateConstIterator(); it; it++){
			Effect* e = (Effect*)*it;
			CheckEffect(e, deltaTime);
		}

		for (Effect* e : effectsToRemove){
			UE_LOG(LogTemp, Log, TEXT("Effect Removed"));
			currentEffects.Remove(e);
		}

		effectsToRemove.Empty();

		/*beingRed = false;
		lk.unlock();
		cv.notify_one();*/
	}

	/*Checks a single effect to allow for re-usability*/
	void CheckEffect(Effect* e, float deltaTime){
		e->lastDuration += deltaTime;
		e->totalTime += deltaTime;

		while (e->ShouldApply()) {
			e->ApplyEffect();
			e->EffectApplied();
			e->lastDuration -= e->dely;

			if (e->EffectExpired()) {
				e->Expired();
				effectsToRemove.Add(e);
			}
		}
	}

	bool isNotBeingRed(){
		return !beingRed;
	}

	/*Checks to see if an entity has an effect with a matching ID*/
	bool HasEffect(Effect* newE) {
		UE_LOG(LogTemp, Log, TEXT("Has Effect"));

		for (TArray<Effect*>::TConstIterator it = currentEffects.CreateConstIterator(); it; it++){
			Effect* e = (Effect*)*it;
			if (e->id.Equals(newE->id)){
				return true;
			}
		}
		return false;
	}

	/*Assigns a new effect to an entity or replaces an existing one, based on if the effect stacks*/
	void GiveEffect(Effect* newE) {
		/*std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [&]{ return isNotBeingRed(); });
		beingRed = true;*/

		UE_LOG(LogTemp, Log, TEXT("Giving effect"));

		if (!newE->stacks && HasEffect(newE)) {
			for (TArray<Effect*>::TConstIterator it = currentEffects.CreateConstIterator(); it; it++){
				Effect* e = (Effect*)*it;
				if (e->id.Equals(newE->id) && e->Score() < newE->Score()){
					e = newE;
				}
			}
		}
		else {
			currentEffects.Add(newE);
		}

		/*beingRed = false;
		lk.unlock();
		cv.notify_one();*/
	}

};
