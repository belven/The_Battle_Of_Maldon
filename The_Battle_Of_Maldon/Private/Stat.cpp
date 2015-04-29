///////////////////////////////////////////////////////////
//  Stat.cpp
//  Implementation of the Class Stat
//  Created on:      27-Apr-2015 19:02:38
//  Original author: sam
///////////////////////////////////////////////////////////
#include "The_Battle_of_Maldon.h"
#include "Stat.h"

template<typename T> Stat<typename T>::Stat(T value){
	SetValue(value);
}


template<typename T> Stat<typename T>::~Stat(){

}


template<typename T> T Stat<typename T>::GetValue(){
	return value;
}


template<typename T> void Stat<typename T>::SetValue(T newVal){
	value = newVal;
}