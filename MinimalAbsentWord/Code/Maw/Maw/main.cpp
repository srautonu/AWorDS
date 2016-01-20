//
// This file contains the main function of the project
//

#include <cstdio>
#include <cassert>
#include "Set.h"
#include "Tests.h"
#include "Constants.h"

extern void runMaw(double diffMatrix[NUM_GENE][NUM_GENE]);
extern void runRaw(double diffMatrix[NUM_GENE][NUM_GENE]);

extern int AnalyzeSpeciesRelations();

void PrintDiffMatrix(double diffMatrix[NUM_GENE][NUM_GENE])
{
    int i, j;

    for (i = 0; i < NUM_GENE; i++)
    {
        printf("{ ");

        for (j = 0; j < i; j++)
        {
            printf("%8.5lf", diffMatrix[i][j]);
            printf("%s", (j == i - 1) ? "" : ", ");
        }

        printf(" }%s\n", (i == NUM_GENE - 1) ? "" : ",");
    }

}

int main()
{
    double diffMatrix[NUM_GENE][NUM_GENE] = {0};

    AnalyzeSpeciesRelations();
    return 0;

    //
    // Sanity check
    //
    assert(DIFF_INDEX / 100 == ABSENT_WORD_TYPE);

#if ABSENT_WORD_TYPE == RAW
    runRaw(diffMatrix);
#elif ABSENT_WORD_TYPE == MAW
    runMaw(diffMatrix);
#endif

    PrintDiffMatrix(diffMatrix);
    
    return 0;
}