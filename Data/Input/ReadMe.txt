This file describes how the data should be stored in the .zip file (i.e. what would be the folder structure inside the archieve, what would be the different file names etc.)
MAW files:

SpeciesOrder.txt:
 - Sequence Full name, Sequence short name

For each sequence there should be one file. The file name should be <sequence full name>.maw.txt

In this file each line represents a minimal absent word

RAW files:

SpeciesOrder.txt:
 - Sequence Full name, Sequence short name

For each sequence there should be a folder named <sequence full name>. Within this folder there should be n-1 files - each representing relative absent words between this sequence and another sequence. Within the file, each line represents a relative absent word.

In total there are n folders, each containing n-1 files. 
