//
// This file contains necessary code for Minimal Absent Word (MAW)
// based difference matrix calculation
//
// The lower triangle of the diff matrix is filled. This is because
// the code used to generate phylogenetic tree needs the lower triangle
//

#include <cassert>
#include "Set.h"
#include "Constants.h"

double calculateTVD(
    vector<pair<int, double>> rgA,
    vector<pair<int, double>> rgB
    );

void runMaw(double diffMatrix[][NUM_GENE], int diffIndex)
{
    int i, j;
    Set maw[NUM_GENE];
    Set diff, a, b;
    char strFileName[MAX_PATH];

    //
    // 1. Read Input
    // 2. Compute Symmetric Difference
    // 3. Calculate index
    // 4. Produce the difference matrix for the 11 genes
    //
    for (i = 0; i < g_numGenes; i++)
    {
        sprintf(strFileName, "%s\\%s.maw.txt", g_strDataDir, g_strSpeciesFullName[i]);
        maw[i] = Set::CreateFromFile(strFileName);
    }

    for (i = 0; i < g_numGenes; i++)
    {
        for (j = 0; j < i; j++)
        {
            switch(diffIndex)
            {
            case MAW_LWI_SDIFF:
                diff = maw[i].SymmetricDifference(maw[j]);
                diffMatrix[i][j] = diff.LengthWeightedIndex();
                break;

            case MAW_LWI_INTERSECT:
                diff = maw[i].Intersection(maw[j]);
                diffMatrix[i][j] = -diff.LengthWeightedIndex();
                break;

            case MAW_GCC_SDIFF:
                diff = maw[i].SymmetricDifference(maw[j]);
                diffMatrix[i][j] = diff.GCContent();
                break;
    
            case MAW_GCC_INTERSECT:
                diff = maw[i].Intersection(maw[j]);
                diffMatrix[i][j] = 1.0 - diff.GCContent();
                break;

            case MAW_JD:
                a = maw[i].Union(maw[j]);
                b = maw[i].Intersection(maw[j]);
                diffMatrix[i][j] = 1.0 - 1.0 * b.Cardinality() / a.Cardinality();
                break;
            
            case MAW_TVD:
                diffMatrix[i][j] = calculateTVD(
                                        maw[i].LengthDistribution(),
                                        maw[j].LengthDistribution()
                                        );
                break;
            }
        }
    }
}

//
// Calculate the Total Variation Distance (TVD) between
// 2 sets of (minimal absent) words.
//
// TVD(P, Q) = 0.5 * sum(abs(P(i) - Q(i))), over all lengths i
//
// Assumption: the vectors are sorted in length order
//
double calculateTVD(
    vector<pair<int, double>> rgA,
    vector<pair<int, double>> rgB
    )
{
    double res = 0.0;

    int indexA, indexB;
    double distA, distB;
    int lenA, lenB;

    for (indexA = 0, indexB = 0; indexA < (int)rgA.size() || indexB < (int)rgB.size(); )
    {
        distA = distB = 0.0;
        lenA = lenB = INT_MAX;

        if (indexA < (int)rgA.size() && indexB < (int)rgB.size())
        {
            lenA = rgA[indexA].first;
            lenB = rgB[indexB].first;
            
            if (lenA == lenB)
            {
                distA = rgA[indexA++].second;
                distB = rgB[indexB++].second;
            }
            else if (lenA < lenB)
            {
                distA = rgA[indexA++].second;
            }
            else
            {
                distB = rgB[indexB++].second;
            }
        }
        else if (indexA < (int)rgA.size())
        {
            distA = rgA[indexA++].second;
        }
        else
        {
            distB = rgB[indexB++].second;
        }

        res += abs(distA - distB);
    }

    res /= 2.0;

    return res;
}

