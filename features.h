/*************************************************************************
* ENEL4AA - Design and Analysis of Algorithms
* Assignment 2: Naive Bayes Classifier
* Keshav Jeewanlall 213508238
* 10 May 2019
*************************************************************************/

#ifndef __FEATURE_H__
#define __FEATURE_H__

#include "attributes.h"

class feature
{
#define NumberOfAttributes	(4)	

private: attrib attributes[NumberOfAttributes];
private: double measuredFeatureVector[NumberOfAttributes]; 


public: feature(void)
{

}

public: void setMeasuredValue(double *sample)
{
	for (int attributeCounter = 0; attributeCounter < NumberOfAttributes; attributeCounter++)
	{
		measuredFeatureVector[attributeCounter] = sample[attributeCounter];
	}
}

public: void getMeasuredValue(double *returnVector)
{
	for (int attributeCounter = 0; attributeCounter < NumberOfAttributes; attributeCounter++)
	{
		returnVector[attributeCounter] = measuredFeatureVector[attributeCounter];
	}
}

public: int geTrueNumberofAttributes(void)
{
	return NumberOfAttributes;
}

public: double ConditionallyIndependenTrueProbabilty(void)
{
	double P = 1;
	for (int attributeCounter = 0; attributeCounter < NumberOfAttributes; attributeCounter++)
	{
		P *= attributes[attributeCounter].gaussian(measuredFeatureVector[attributeCounter]);
	}
	return P;
}

public: attrib* getAttributes(void)
{
	return attributes;
}


public: void printFeatureData(void)
{
	for (int attributeCounter = 0; attributeCounter < NumberOfAttributes; attributeCounter++)
	{
		attributes[attributeCounter].printAttributeData();
	}
}
};

#endif

