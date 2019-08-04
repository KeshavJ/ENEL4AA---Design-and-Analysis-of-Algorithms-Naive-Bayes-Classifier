/*************************************************************************
* ENEL4AA - Design and Analysis of Algorithms
* Assignment 2: Naive Bayes Classifier
* Keshav Jeewanlall 213508238
* 10 May 2019
*************************************************************************/

#ifndef __ATTRIB_H__
#define __ATTRIB_H__

#define _USE_MATH_DEFINES
#include<math.h>

class attrib
{
private: double mu;				
private: double sigma;			
private: char* attribName;		


public: attrib(void)
{
	setAttributeName("Unkown Attribute");
	setMean(0);
	setStandardDeviation(1);
}

public: attrib(char* name)
{
	setAttributeName(name);
	setMean(0);
	setStandardDeviation(1);
}

public: void setAttributeName(char* attrName)
{
	attribName = attrName;
}

public: char* getAttributeName(void)
{
	return attribName;
}

public: void setMean(double mean)
{
	mu = mean;
}


public: double getMean(void)
{
	return mu;
}

public: void setStandardDeviation(double standardDeviation)
{
	sigma = standardDeviation;
}

public: double getStandardDeviation(void)
{
	return sigma;
}

public: double gaussian(double x)
{
	
	double z = (x - mu) / (sigma); 
	return (1 / sqrt(2 * M_PI*sigma*sigma))*(exp(-(pow(z, 2)) / 2));
}

public: void printAttributeData()
{
	printf("\n\rName:%s\nMean:%f\nStandard Deviation:%f",
		getAttributeName(), getMean(), getStandardDeviation());
}
};

#endif
