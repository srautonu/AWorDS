//
// This file contains necessary code for Relative Absent Word (RAW)
// based difference matrix calculation
//
// The lower triangle of the diff matrix is filled. This is because
// the code used to generate phylogenetic tree needs to lower triangle
//

#include <string>
#include <cassert>
#include "Constants.h"
#include "Globals.h"
#include "Set.h"

using namespace std;

double GetRawBasedDiff(int i, int j, int diffIndex)
{
    double res = 0.0;
    char strFileName1[MAX_PATH], strFileName2[MAX_PATH];
    Set raw1, raw2;

    assert(i >= 0 && i < sizeof(g_strSpeciesShortName));
    assert(j >= 0 && j < sizeof(g_strSpeciesFullName));
    
    //
    // Make the file name from the gene indices
    //
    sprintf(
        strFileName1, 
        "%s\\%s\\%s_%s.raw.txt",
        g_strDataDir,
        g_strSpeciesFullName[i], 
        g_strSpeciesShortName[i], 
        g_strSpeciesFullName[j]
        );
    
    sprintf(
        strFileName2,
        "%s\\%s\\%s_%s.raw.txt",
        g_strDataDir,
        g_strSpeciesFullName[j],
        g_strSpeciesShortName[j],
        g_strSpeciesFullName[i]
        );
    
    raw1 = Set::CreateFromFile(strFileName1);
    raw2 = Set::CreateFromFile(strFileName2);

    if (diffIndex == RAW_LWI)
    {
        res = 0.5 * (raw1.LengthWeightedIndex() + raw2.LengthWeightedIndex());
    }
    else if (diffIndex == RAW_GCC)
    {
        res = 0.5 * (raw1.GCContent() + raw2.GCContent());
    }

    return res;
}

int runRaw(double diffMatrix[][NUM_GENE], int diffIndex)
{
    int i, j;

    if (diffIndex < RAW_LWI || diffIndex > RAW_GCC)
        return -1;

    for (i = 0; i < g_numGenes; i++)
    {
        for (j = 0; j < i; j++)
        {
            diffMatrix[i][j] = GetRawBasedDiff(i, j, diffIndex);
        }
    }

    return 0;
}