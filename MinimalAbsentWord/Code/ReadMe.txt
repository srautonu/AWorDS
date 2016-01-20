Java Code
=========

The Match7.java code has be copied from http://www.itu.dk/~sestoft/bsa/Match7.java. Then some modifications were made to it for customizing the rendering and printing of the phylogenetic tree. The algorithms to construct the tree have not been modified in any ways.

C++ Code
========

The code was compiled using Visual Studio 2010 Express edition. The experiments were run on a Windows 7 Home Premium 64-bit (Service Pack 1) system with processor Intel(R) Core(TM) i3 CPU M370 @ 2.40GHz (4 CPUs) and 4GB RAM.

Here is a short description of each code file in the solution:

constants.h
-----------
This file contains different constant definitions. You need to modify the values of ABSENT_WORD_TYPE and DIFF_INDEX to run different methods of difference matrix calculation. For example, to apply GC content method on the Relative Absent Word set, use the following setting:

	#define ABSENT_WORD_TYPE    RAW
	#define DIFF_INDEX          RAW_GCC

You can change the value of NUM_GENE to experiment with more/less genes. But, you then also need to update g_strSpeciesShortName and g_strSpeciesFullName accordingly.

set.h/cpp
---------
This file contains declaration of the Set class. This class is used extensively in different set operations used in difference matrix calculations.

main.cpp
--------
This file contains the main function of the project

maw.cpp
-------
This file contains necessary code for Minimal Absent Word (MAW) based difference matrix calculation
The lower triangle of the diff matrix is filled. This is because the code used to generate phylogenetic tree needs to lower triangle.

raw.cpp
-------
This file contains necessary code for Relative Absent Word (RAW) based difference matrix calculation
The lower triangle of the diff matrix is filled. This is because the code used to generate phylogenetic tree needs to lower triangle

Tests.h/cpp
-----------
This file contains several functions to test the Set class.

RCMerger.cpp
------------
This file contains code for editing and merging some intermediate files. This file is not used in diff matrix calculations.

DiffMatrixSorted.cpp
--------------------
This file contains code for analyzing relation between species based on difference matrix(AnalyzeSpeciesRelations). To do so, for each species, we sort the relation with other species based
on different matrix values. Then we can analyze which species is closest (furthest) to this species

In addition, this file contains a method PrintDiffMatrix_LatexFormat that was used to suitably format the difference matrix into latex style table (with higher triangle). This file is not used in diff matrix calculations.
