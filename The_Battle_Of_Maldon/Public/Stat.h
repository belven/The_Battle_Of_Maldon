///////////////////////////////////////////////////////////
//  Stat.h
//  Implementation of the Class Stat
//  Created on:      27-Apr-2015 19:02:38
//  Original author: sam
///////////////////////////////////////////////////////////

#pragma once
#include "UnrealString.h"
//#include "Object.h"
//#include "Stat.generated.h"

//UCLASS(Blueprintable, BlueprintType)
template<typename T>
class UStat //: public UObject
{

	//GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Stats")
		UStat(T value, FString inName);

	virtual ~UStat();

	UFUNCTION(BlueprintCallable, Category = "Stats")
		T GetValue();

	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetValue(T newVal);

	UFUNCTION(BlueprintCallable, Category = "Stats")
		FString GetName();

	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetName(FString newVal);
private:
	T value;
	FString name = "";


};

