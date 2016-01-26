//
// This file defines entry point functions of the MAW DLL.
//
// Initialize() must be called before any other function is called.
// It can be called as many times as needed, with different data sets
//

#include <string.h>

#include "Constants.h"

extern int runMaw(double diffMatrix[][NUM_GENE], int diffIndex);
extern int runRaw(double diffMatrix[][NUM_GENE], int diffIndex);
extern void getRanks(double diffMatrix[][NUM_GENE], int rank[][NUM_GENE]);

extern "C" __declspec(dllexport) int Initialize(
    char **geneFullNames,
    char **geneShortNames,
    int nGenes,
    char *dataDir
    )
{
    if (!geneFullNames || !geneShortNames || !dataDir)
    {
        return -1;
    }

    if (nGenes <= 0)
    {
        return -1;
    }

    for (int i = 0; i < nGenes; i++)
    {
        if (!geneShortNames[i] || !geneFullNames[i])
            return -1;
    }

    int i;

    g_numGenes = nGenes;

    for (i = 0; i < nGenes; i++)
    {
        strcpy(g_strSpeciesShortName[i], geneShortNames[i]);
        strcpy(g_strSpeciesFullName[i], geneFullNames[i]);
    }

    i = strlen(dataDir);
    if (i == 0)
    {
        strcpy(g_strDataDir, ".");
    }
    else
    {
        strcpy(g_strDataDir, dataDir);
        if (g_strDataDir[i - 1] == '\\')
        {
            g_strDataDir[i - 1] = '\0';
        }
    }

    return 0;
}

extern "C" __declspec(dllexport) int getDiffMatrix(
    double diffMatrix[][NUM_GENE],
    int absWordType,
    int diffIndex
    )
{
    int ret = 0;

    if (absWordType != MAW && absWordType != RAW)
        return -1;

    if (absWordType == RAW)
    {
        ret = runRaw(diffMatrix, diffIndex);
    }
    else if (absWordType == MAW)
    {
        ret = runMaw(diffMatrix, diffIndex);
    }
    
    return 0;
}

extern "C" __declspec(dllexport) int getRanks(int rank[][NUM_GENE], int absWordType, int diffIndex)
{
    double diffMatrix[NUM_GENE][NUM_GENE];
    int ret = 0;

    ret = getDiffMatrix(diffMatrix, absWordType, diffIndex);
    if (ret == 0)
    {
        getRanks(diffMatrix, rank);
    }

    return ret;
}
