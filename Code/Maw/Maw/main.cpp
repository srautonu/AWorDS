//
// This file contains the main function of the project
//

#include <cstdio>
#include <cassert>
#include "Set.h"
#include "Tests.h"
#include "Constants.h"
#include "Globals.h"

extern "C" __declspec(dllexport) int Initialize(
    char **geneFullNames,
    char **geneShortNames,
    int nGenes,
    char *dataDir
    );

extern "C" __declspec(dllexport) int getDiffMatrix(
    double diffMatrix[][NUM_GENE],
    int absWordType,
    int diffIndex
    );

extern "C" __declspec(dllexport) int getRanks(
    int rank[][NUM_GENE],
    int absWordType,
    int diffIndex
    );

void PrintSpeciesRelations(int ranks[][NUM_GENE])
{
    int i, j;

    for (i = 0; i < g_numGenes; i++)
    {
        printf("%7s:", g_strSpeciesFullName[i]);

        for (j = 0; j < g_numGenes; j++)
        {
            printf("%7s%c", g_strSpeciesFullName[ranks[i][j]], (j == g_numGenes-1 ? '\n' : ' '));
        }
    }
}

void PrintDiffMatrix(double diffMatrix[][NUM_GENE])
{
    int i, j;

    for (i = 0; i < g_numGenes; i++)
    {
        printf("{ ");

        for (j = 0; j < i; j++)
        {
            printf("%5.2lf", diffMatrix[i][j]);
            printf("%s", (j == i - 1) ? "" : ", ");
        }

        printf(" }%s\n", (i == g_numGenes - 1) ? "" : ",");
    }

}

int main()
{
    //
    // Change the following 2 variables to run with different
    // absent word type (RAW) and diff indices.
    //
    //int absWordType = RAW;
    //int diffIndex = RAW_LWI;

    int absWordType = MAW;
    int diffIndex = MAW_JD;

    //
    // Change the following variable to change the data folder location
    //
    //char *strDataDir = ".";
    //char *strDataDir = "C:\\Users\\mrahman\\Desktop\\Masters Material\\Data\\Input\\Raw_NoRC";
    char *strDataDir = "C:\\Users\\mrahman\\Desktop\\Masters Material\\Data\\Input\\Maw_RC";

    //
    // Change the following variables for running a different set of species/gene sequences
    //
    
    //int nGenes = 11;
    int nGenes = 7;

    //
    // Short name code used for each species. 
    char* strSpeciesShortName[] = {
        "hu",
        "gt",
        "op",
        "ga",
        "le",
        "mo",
        //"rb",
        //"rt",
        //"gr",
        //"bv",
        "ch"
    };

    //
    // Full name of each species. 
    char* strSpeciesFullName[] = {
        "human",
        "goat",
        "opossum",
        "gallus",
        "lemur",
        "mouse",
        /*"rabbit",
        "rat",
        "gorilla",
        "bovine",*/
        "chimp"
    };

    double diffMatrix[NUM_GENE][NUM_GENE] = {0};
    int rank[NUM_GENE][NUM_GENE] = {0};

    Initialize(strSpeciesFullName, strSpeciesShortName, nGenes, strDataDir);

    //getDiffMatrix(diffMatrix, absWordType, diffIndex);
    //PrintDiffMatrix(diffMatrix);

    getRanks(rank, absWordType, diffIndex);
    PrintSpeciesRelations(rank);
    
    return 0;
}