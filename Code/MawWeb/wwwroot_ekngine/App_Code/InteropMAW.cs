using System;
using System.Runtime.InteropServices;

/// <summary>
/// Summary description for InteropMAW
/// </summary>
public class InteropMAW
{
    //
    // Copied from constants.h file of MAW native code project. 
    // The values here must be in sync. with that file.
    //
    public const int NUM_GENE = 11;


    //
    // Importing relevant methods from the native code project
    //

    //
    // Importing relevant methods from the native code project
    //

    #region extertnal methods
    [DllImport(@"C:\gitHub\MAW\Code\MawWeb\wwwroot_ekngine\Bin\maw.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int Initialize(String[] geneFullNames, String[] geneShortNames, int nGenes, String dataDir);

    [DllImport(@"C:\gitHub\MAW\Code\MawWeb\wwwroot_ekngine\Bin\maw.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int getDiffMatrix([Out] double[,] diffMatrix, int absWordType, int diffIndex);

    [DllImport(@"C:\gitHub\MAW\Code\MawWeb\wwwroot_ekngine\Bin\maw.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int getRanks([Out] int[,] rank, int absWordType, int diffIndex);
    #endregion
}