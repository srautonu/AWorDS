This file describes how the absent word data is stored in the .zip files (i.e. what is the folder structure inside the archieve, what would be the different file names etc.)

Maw_NoRC.zip and Maw_RC.zip
===========================
Both these archieves contain MAW data for different species. Following files are present in each of these:

SpeciesOrder.txt: For each species (sequence), a line contains a full name followed by a 2 letter short name. The full and short names are comma separated. The species names are mentioned in the order in which we would like to see the distance table after computations.

For each species (sequence) there is a file representing the minimal absent word (MAW) set of that sequence. The file name is "<sequence full name>.maw.txt". In this file each line represents a minimal absent word.

All the files are located at the root of the archieve.

Raw_NoRC.zip and Raw_RC.zip
===========================
Both these archieves contain RAW data for different species. Following files and folders are present in each of these:

SpeciesOrder.txt: This file is located at the root of the archieve. In this file, for each species (sequence), a line contains a full name followed by a 2 letter short name. The full and short names are comma separated. The species names are mentioned in the order in which we would like to see the distance table after computations.

For each species (sequence) there is a folder, named after the sequence's full name. Within this folder there are n-1 files, where n is the total number of sequences. Each such file represents relative absent word (RAW) set between this sequence and another sequence. Within the file, each line represents a relative absent word. The file is named as "<seq#1 short name>_<seq#2 full name>.raw.txt"

In total there are n folders, each containing n-1 files.

NOTE
====
The AWorDS tool, located at http://www.ekngine.com/awords/, requires a single zip archieve to be uploaded. The uploaded file *must* adhere to the composition specified above. 

For MAW based analysis, the input .zip file composition should be exactly like that of Maw_NoRC.zip or Maw_RC.zip

For RAW based analysis, the input .zip file composition should be exactly like that of Raw_NoRC.zip and Raw_RC.zip
