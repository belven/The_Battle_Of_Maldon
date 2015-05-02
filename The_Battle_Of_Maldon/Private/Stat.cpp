///////////////////////////////////////////////////////////
//  Stat.cpp
//  Implementation of the Class Stat
//  Created on:      27-Apr-2015 19:02:38
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"
#include "Stat.h"

template<typename T> 
UStat<typename T>::UStat(T value, FString inName){
	SetValue(value);
	SetName(inName);
}


template<typename T> 
UStat<typename T>::~UStat(){

}


template<typename T> 
T UStat<typename T>::GetValue(){
	return value;
}


template<typename T> 
void UStat<typename T>::SetValue(T newVal){
	value = newVal;
}


template<typename T>
FString UStat<T>::GetName(){
	return name;
}


template<typename T>
void UStat<T>::SetName(FString newVal){
	name = newVal;
}