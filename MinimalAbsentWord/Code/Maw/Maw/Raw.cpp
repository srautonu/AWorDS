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
#include "Set.h"

using namespace std;

double GetRawBasedDiff(int i, int j)
{
    double res = 0.0;
    char strFileName1[50], strFileName2[50];
    Set raw1, raw2;

    assert(i >= 0 && i < sizeof(g_strSpeciesShortName));
    assert(j >= 0 && j < sizeof(g_strSpeciesFullName));
    
    //
    // Make the file name from the gene indices
    //
    sprintf(
        strFileName1, 
        "%s\\%s_%s.fasta",
        g_strSpeciesFullName[i], 
        g_strSpeciesShortName[i], 
        g_strSpeciesFullName[j]
        );
    
    sprintf(
        strFileName2,
        "%s\\%s_%s.fasta",
        g_strSpeciesFullName[j],
        g_strSpeciesShortName[j],
        g_strSpeciesFullName[i]
        );
    
    raw1 = Set::CreateFromFile(strFileName1);
    raw2 = Set::CreateFromFile(strFileName2);

#if DIFF_INDEX == RAW_LWI
    res = 0.5 * (raw1.LengthWeightedIndex() + raw2.LengthWeightedIndex());
#elif DIFF_INDEX == RAW_GCC
    res = 0.5 * (raw1.GCContent() + raw2.GCContent());
#endif

    return res;
}

void runRaw(double diffMatrix[NUM_GENE][NUM_GENE])
{
    int i, j;

    for (i = 0; i < NUM_GENE; i++)
    {
        for (j = 0; j < i; j++)
        {
            diffMatrix[i][j] = GetRawBasedDiff(i, j);
        }
    }
}