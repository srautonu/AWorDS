//
// This file contains code for analyzing relation between species
// based on difference matrix (AnalyzeSpeciesRelations).
// To do so, for each species, we sort the relation with other species based
// on different matrix values. Then we can analyze which species is closest
// (furthest) to this species
//
// In addition, this file contains a method PrintDiffMatrix_LatexFormat
// that was used to suitably format the difference matrix into latex style
// table (with higher triangle)
//
// This file is not used in diff matrix calculations.
//

#include <cstdio>
#include <algorithm>
#include <numeric>
#include "Constants.h"

using namespace std;

class IndexComparer
{
protected:
    double *m_pVal;
    
public:
    IndexComparer(double *pVal)
        : m_pVal(pVal)
    {
    }

    bool operator() (size_t lindex, size_t rindex)
    {
        return m_pVal[lindex] < m_pVal[rindex];
    }
};

void PrintDiffMatrix_LatexFormat(double diffMatrix[NUM_GENE][NUM_GENE])
{
    int i, j;

    printf("\\hline\n");
    printf("Species");
    for (i = 0; i < NUM_GENE; i++)
    {
        printf(" & %7s", g_strSpeciesFullName[i]);
    }
    printf("\\\\ \\hline\n");

    
    for (i = 0; i < NUM_GENE; i++)
    {
        printf("%7s", g_strSpeciesFullName[i]);
        for (j = 0; j <= i; j++)
        {
            printf(" &        ");
        }

        for (; j < NUM_GENE; j++)
        {
            printf(" & %7.2lf", diffMatrix[i][j]);
        }
        printf("\\\\\n");
    }

    printf("\\hline\n");
}

int AnalyzeSpeciesRelations()
{
    int i, j;
    double diffMatrix[NUM_GENE][NUM_GENE] = {0};
    int sortedIndex[NUM_GENE][NUM_GENE];

    //
    // Read the difference matrix from console
    //
    for (i = 0; i < NUM_GENE; i++)
    {
        scanf("%*s");

        for (j = 0; j < i; j++)
        {
            scanf("%lf%*c", &diffMatrix[i][j]);
            diffMatrix[j][i] = diffMatrix[i][j];
        }

        scanf("%*s");
    }

    PrintDiffMatrix_LatexFormat(diffMatrix);
    return 0;

    for (i = 0; i < NUM_GENE; i++)
    {
        iota(sortedIndex[i], sortedIndex[i] + NUM_GENE, 0);
        sort(sortedIndex[i], sortedIndex[i] + NUM_GENE, IndexComparer(diffMatrix[i]));
    }

    for (i = 0; i < NUM_GENE; i++)
    {
        printf("%7s:", g_strSpeciesFullName[i]);

        for (j = 0; j < NUM_GENE; j++)
        {
            printf("%7s%c", g_strSpeciesFullName[sortedIndex[i][j]], (j == NUM_GENE-1 ? '\n' : ' '));
        }
    }

    return 0;
}