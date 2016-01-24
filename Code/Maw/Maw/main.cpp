//
// This file contains the main function of the project
//

#include <cstdio>
#include <cassert>
#include "Set.h"
#include "Tests.h"
#include "Constants.h"

extern "C" __declspec(dllexport) int Initialize(
    char **geneFullNames,
    char **geneShortNames,
    int nGenes,
    char *dataDir
    );


extern void runMaw(double diffMatrix[][NUM_GENE], int diffIndex);
extern void runRaw(double diffMatrix[][NUM_GENE], int diffIndex);

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
    //
    // Change the following 2 variables to run with different
    // absent word type (RAW) and diff indices.
    //
    int absWordType = MAW;
    int diffIndex = MAW_LWI_SDIFF;

    //
    // Change the following variable to change the data folder location
    //
    char *strDataDir = ".";

    //
    // Change the following variables for running a different set of species/gene sequences
    //
    
    int nGenes = 11;

    //
    // Short name code used for each species. 
    char* strSpeciesShortName[NUM_GENE] = {
        "hu",
        "gt",
        "op",
        "ga",
        "le",
        "mo",
        "rb",
        "rt",
        "gr",
        "bv",
        "ch"
    };

    //
    // Full name of each species. 
    char* strSpeciesFullName[NUM_GENE] = {
        "human",
        "goat",
        "opossum",
        "gallus",
        "lemur",
        "mouse",
        "rabbit",
        "rat",
        "gorilla",
        "bovine",
        "chimp"
    };

    double diffMatrix[NUM_GENE][NUM_GENE] = {0};
    int i;

    Initialize(strSpeciesFullName, strSpeciesShortName, nGenes, strDataDir);

    if (absWordType == RAW)
    {
        runRaw(diffMatrix, diffIndex);
    }
    else if (absWordType == MAW)
    {
        runMaw(diffMatrix, diffIndex);
    }

    PrintDiffMatrix(diffMatrix);
    
    return 0;
}