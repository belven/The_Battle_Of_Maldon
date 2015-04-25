///////////////////////////////////////////////////////////
//  Part.h
//  Implementation of the Class Part
//  Created on:      25-Apr-2015 08:58:36
//  Original author: sam
///////////////////////////////////////////////////////////


#if !defined(EA_EDB72366_6253_46fc_8917_6BC649218681__INCLUDED_)
#define EA_EDB72366_6253_46fc_8917_6BC649218681__INCLUDED_

UENUM(BlueprintType)
namespace PartEnums
{
	enum PartType
	{
		LeftLeg,
		RightLeg,
		LeftArm,
		RightArm,
		Chest,
		Head,
		Other
	};

}

class Part
{
private:
	double vitality = 1000;

public:	
	Part();
	virtual ~Part();
	double GetVitality();
	void SetVitality(double newVal);
	PartEnums::PartType GetPartType();
	void SetPartType(PartEnums::PartType value);
private:
	TEnumAsByte<PartEnums::PartType> partType = PartEnums::Other;


};
#endif // !defined(EA_EDB72366_6253_46fc_8917_6BC649218681__INCLUDED_)


