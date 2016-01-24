//
// This file contains different constant definitions.
//

#pragma once

//
// Disable warning generated due to using depricated (unsafe) functions such as
// freopen, sprintf etc.
//
#pragma warning(disable:4996)

//
// Maximum number of genes that can be used in experiment
//
#define NUM_GENE 11

//
// Maximum length of a species name Number of genes used in experiment
//

#define MAX_SPECIES_NAME_LEN 41

//
// Maximum possible length of an absent word. To be safe this should be set to
// a length that is greater than the longest gene used in experiment.
// Since we use a gene with maximum length of 105, and concatenate reverse
// complement, so the size can be 210. So, choosing limit accordingly
//
#define MAX_WORD_LEN 256

//
// Maximum length of a file location
//
#define MAX_PATH 256

#define MAW     1   // Minimum abset word
#define RAW     2   // Relative absent word

//
// Defined constants for different MAW based similarity matrices
//
#define MAW_LWI_SDIFF       ((MAW * 100) + 1)  // Length weighted index of symmetric difference
#define MAW_LWI_INTERSECT   ((MAW * 100) + 2)  // Length weighted index of intersection
#define MAW_GCC_SDIFF       ((MAW * 100) + 3)  // GC content of symmetric difference
#define MAW_GCC_INTERSECT   ((MAW * 100) + 4)  // GC content of intersection
#define MAW_JD              ((MAW * 100) + 5)  // Jaccard Distance
#define MAW_TVD             ((MAW * 100) + 6)  // Jaccard Distance

//
// Defined constants for different RAW based similarity matrices
//
#define RAW_LWI            ((RAW * 100) + 1)   // Length weighted index
#define RAW_GCC            ((RAW * 100) + 2)   // GC content

//
// Global variables
//

//
// Total number of genes/species
//
extern __declspec(selectany) int g_numGenes;

//
// Short name code used for each species. 
// (Used in generating the filename for Raw/Maw sets for respective species)
//
extern __declspec(selectany) char g_strSpeciesShortName[NUM_GENE][MAX_SPECIES_NAME_LEN];

//
// Full name of each species. 
//
extern __declspec(selectany) char g_strSpeciesFullName[NUM_GENE][MAX_SPECIES_NAME_LEN];

//
// Location of the folder that contains necessary data files
//
extern __declspec(selectany) char g_strDataDir[MAX_PATH];
