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
// Number of genes used in experiment
//
#define NUM_GENE 11

//
// Maximum possible length of an absent word. To be safe this should be set to
// a length that is greater than the longest gene used in experiment.
// Since we use a gene with maximum length of 105, and concatenate reverse
// complement, so the size can be 210. So, choosing limit accordingly
//
#define MAX_WORD_LEN 256

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
// Which type of absent word (Maw/Raw) to use
//
#define ABSENT_WORD_TYPE    MAW

//
// Which index to use?
//
#define DIFF_INDEX          MAW_TVD

//
// Short name code used for each species. 
// (Used in generating the filename for Raw/Maw sets for respective species)
//
extern __declspec(selectany) char* g_strSpeciesShortName[NUM_GENE] = {
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
// Note: chimpanzee is shortened to chimp to reduce space consumption in the
// printouts to console/file
//
extern __declspec(selectany) char* g_strSpeciesFullName[NUM_GENE] = {
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
