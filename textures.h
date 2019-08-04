/*************************************************************************
* ENEL4AA - Design and Analysis of Algorithms
* Assignment 2: Naive Bayes Classifier
* Keshav Jeewanlall 213508238
* 10 May 2019
*************************************************************************/


#include "features.h"

class texture
{
public: feature X;
private: char* textureName; 
private: double probablityOfTexture; 
private: int occurrences;

public: texture(void)
{
	setTextureName("Unkown Texture");
	setTextureProbability(0);
}


public: texture(char* name)
{
	setTextureName(name);
	setTextureProbability(0);
}


public: void setTextureName(char* name)
{
	textureName = name;
}

public: char* getTextureName(void)
{
	return textureName;
}

public: void setTextureProbability(double prob)
{
	if (prob >= 0 && prob <= 1)
	{
		probablityOfTexture = prob;
	}
	else
	{
		probablityOfTexture = -1;
	}
}


public: double getTextureProbability(void)
{
	return probablityOfTexture;
}

public: void setOccurrences(int numberOfTimes)
{
	if (numberOfTimes >= 0)
	{
		occurrences = numberOfTimes;
	}
	else
	{
		occurrences = 0;
	}
}


public: int getOccurrences(void)
{
	return occurrences;
}

public: void printTextureData(void)
{
	printf("\n\rName of Texture:%s\nProbablity of Texture:%f", getTextureName(), getTextureProbability());
}
};


