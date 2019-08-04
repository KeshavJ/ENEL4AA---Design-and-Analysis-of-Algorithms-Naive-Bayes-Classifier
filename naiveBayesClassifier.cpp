/*************************************************************************
* ENEL4AA - Design and Analysis of Algorithms
* Assignment 2: Naive Bayes Classifier
* Keshav Jeewanlall 213508238
* 10 May 2019
*************************************************************************/

#include <stdio.h>	
#include <fstream>	
#include "attributes.h"
#include "features.h"
#include "textures.h"

using namespace std;

#define NumberOfClasses (4)
#define False			(0)
#define	True			(1)

enum TextureType { MARBLE, GRANITE, WALL, WOOD };

int train(texture* textureClass, char* trainingSet);
int classify(texture* TextureClass, double x[NumberOfAttributes]);
int confusion_matrix(char* testFile, texture* TextureClass, int confusion_Matrix[NumberOfClasses][2][2], int classType);
double sensitivity(int confusion_Matrix[2][2]);
double specificity(int confusion_Matrix[2][2]);
double positive_predictive_value(int confusion_Matrix[2][2]);
double negative_predictive_value(int confusion_Matrix[2][2]);

int totalNumberofSamples = 0;
int numberOfClassSamples = 0;

int main(void)
{
	texture classSet[NumberOfClasses];
	attrib* attribVector;
	int positives[NumberOfClasses][2][2] = { 0, };

	classSet[MARBLE].setTextureName("Marble");
	classSet[GRANITE].setTextureName("Granite");
	classSet[WALL].setTextureName("Wall");
	classSet[WOOD].setTextureName("Wood");

	train(&(classSet[MARBLE]), "train_data/Marble_Train.txt");
	train(&(classSet[GRANITE]), "train_data/Granite_Train.txt");
	train(&(classSet[WALL]), "train_data/Wall_Train.txt");
	train(&(classSet[WOOD]), "train_data/Wood_Train.txt");

	for (int i = 0; i < NumberOfClasses; i++)
	{
		classSet[i].setTextureProbability((double)classSet[MARBLE].getOccurrences() / totalNumberofSamples);
	}

	confusion_matrix("test_data/Marble_Test.txt", &(classSet[MARBLE]), positives, MARBLE);
	confusion_matrix("test_data/Granite_Test.txt", &(classSet[MARBLE]), positives, GRANITE);
	confusion_matrix("test_data/Wall_Test.txt", &(classSet[MARBLE]), positives, WALL);
	confusion_matrix("test_data/Wood_Test.txt", &(classSet[MARBLE]), positives, WOOD);

	printf("Confusion Matrices");
	for (int i = 0; i < NumberOfClasses; i++)
	{
		printf("\n%s", classSet[i].getTextureName());
		printf("\nTrue Positives - %d     False Negatives - %d", positives[i][0][0], positives[i][0][1]);
		printf("\nFalse Positives - %d     True Negatives - %d", positives[i][1][0], positives[1][1][1]);
		printf("\n");
	}

	printf("\nStatistics");
	for (int i = 0; i < NumberOfClasses; i++)
	{
		printf("\nSensitivity = %f", classSet[i].getTextureName(), ">", sensitivity(positives[i]));
		printf("\nSpecificty = %f", classSet[i].getTextureName(), ">", specificity(positives[i]));
		printf("\nPositive Predicted Texture = %f", classSet[i].getTextureName(), ">", positive_predictive_value(positives[i]));
		printf("\nNegatuve Predicted Texture = %f", classSet[i].getTextureName(), ">", negative_predictive_value(positives[i]));
		printf("\n");
	}

	printf("\n");

	system("PAUSE");
	return 0;
}

int train(texture* textureClass, char* trainingSet)
{
	enum eMeanVariance { muOld, sigmaOld, muNew, sigmaNew };
	double x[NumberOfAttributes] = { 0, };
	double mu[NumberOfAttributes] = { 0, };
	double sigma[NumberOfAttributes] = { 0, };
	attrib* attribVector;

	numberOfClassSamples = 0;
	ifstream trainingData(trainingSet);

	if (!trainingData)
	{
		printf("\n\rError opening training set file!\n\r");
		system("PAUSE");
		return -1;
	}

	while (trainingData >> x[0] >> x[1] >> x[2] >> x[3])
	{
		numberOfClassSamples++;
		totalNumberofSamples++;
		for (int i = 0; i < NumberOfAttributes; i++)
		{
			mu[i] += x[i];
		}
	}

	(*textureClass).setOccurrences(numberOfClassSamples);

	(*textureClass).setTextureProbability((double)numberOfClassSamples); 
	for (int i = 0; i < NumberOfAttributes; i++)
	{
		mu[i] = mu[i] / numberOfClassSamples;
	}
	trainingData.close();

	trainingData.open(trainingSet);
	if (!trainingData)
	{
		printf("\n\rError opening training set file!\n\r");
		system("PAUSE");
		return -1;
	}

	while (trainingData >> x[0] >> x[1] >> x[2] >> x[3])
	{
		for (int i = 0; i < NumberOfAttributes; i++)
		{
			sigma[i] += pow(x[i] - mu[i], 2);
		}
	}

	for (int i = 0; i < NumberOfAttributes; i++)
	{
		sigma[i] = sqrt(sigma[i] / numberOfClassSamples);
	}
	trainingData.close();

	attribVector = (*textureClass).X.getAttributes();
	for (int i = 0; i < NumberOfAttributes; i++)
	{
		attribVector[i].setMean(mu[i]);
		attribVector[i].setStandardDeviation(sigma[i]);
	}

	return 0;
}

int classify(texture* TextureClass, double x[NumberOfAttributes])
{
	int mosTrueProbableClass = -1;
	double posTrueProbability = -1;
	double maxPosTrueProbability = -1;

	for (int i = 0; i < NumberOfClasses; i++)
	{
		TextureClass[i].X.setMeasuredValue(x);
		posTrueProbability = (TextureClass[i].getTextureProbability()) * (TextureClass[i].X.ConditionallyIndependenTrueProbabilty());

		if (posTrueProbability > maxPosTrueProbability)
		{
			maxPosTrueProbability = posTrueProbability;
			mosTrueProbableClass = i;
		}
	}

	return mosTrueProbableClass;
}

int confusion_matrix(char* testFile, texture* TextureClass, int confusion_Matrix[NumberOfClasses][2][2], int classType)
{
	double sampleValue[NumberOfAttributes] = { 0, };
	ifstream testData(testFile);

	if (!testData)
	{
		printf("\n\rError opening test set file!\n\r");
		system("PAUSE");
		return -1;
	}

	int s = 2;

	while (testData >> sampleValue[0] >> sampleValue[1] >> sampleValue[2] >> sampleValue[3])
	{
		int classifiedAs = classify(TextureClass, sampleValue);

		if (classifiedAs == classType)
		{
			(confusion_Matrix[classType][0][0])++;
			for (int i = 0; i < NumberOfClasses; i++)
			{
				if (i != classType)
				{
					(confusion_Matrix[i][1][1])++;
				}
			}
		}
		else
		{
			(confusion_Matrix[classifiedAs][1][0])++; // it is False positive for the class that got classified
			(confusion_Matrix[classType][0][1])++;// it is a False negative for the class we're classifying for
			for (int i = 0; i < NumberOfClasses; i++) //and it's a True negative for the remaining classes
			{
				if ((i != classifiedAs) && (i != classType))
					(confusion_Matrix[i][1][1])++;
			}
		}
	}

	testData.close();
	return 0;
}

double sensitivity(int confusion_Matrix[2][2])
{
	int TrueP = 0;
	int TrueP_FalseN = 0;


	TrueP = confusion_Matrix[0][0];
	TrueP_FalseN = confusion_Matrix[0][0] + confusion_Matrix[0][1];

	if (TrueP_FalseN == 0)
	{
		return -1;
	}
	else
	{
		return (double)TrueP / TrueP_FalseN;
	}
}

double specificity(int confusion_Matrix[2][2])
{
	int TrueN = 0;
	int TrueN_FalseP = 0;


	TrueN = confusion_Matrix[1][1];
	TrueN_FalseP = confusion_Matrix[1][1] + confusion_Matrix[1][0];

	if (TrueN_FalseP == 0)
	{
		-1;
	}
	else
	{
		return (double)TrueN / TrueN_FalseP;
	}
}

double positive_predictive_value(int confusion_Matrix[2][2])
{
	int TrueP = 0;
	int TrueP_FlaseP = 0;


	TrueP = confusion_Matrix[0][0];
	TrueP_FlaseP = confusion_Matrix[0][0] + confusion_Matrix[1][0];

	if (TrueP_FlaseP == 0)
	{
		return -1;
	}
	else
	{
		return (double)TrueP / TrueP_FlaseP;
	}
}

double negative_predictive_value(int confusion_Matrix[2][2])
{
	int TrueN = 0;
	int TrueN_FlaseN = 0;


	TrueN = confusion_Matrix[1][1];
	TrueN_FlaseN = confusion_Matrix[1][1] + confusion_Matrix[0][1];

	if (TrueN_FlaseN == 0)
	{
		return -1;
	}
	else
	{
		return (double)TrueN / TrueN_FlaseN;
	}
}
