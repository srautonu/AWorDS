using System;
using System.Runtime.InteropServices;

/// <summary>
/// Summary description for InteropMAW
/// </summary>
public class InteropMAW
{
    //
    // Copied from constants.h file of MAW native code project. 
    // IMPPORTANT: THE VALUE HERE MUST BE EXACTLY SAME AS THAT
    // IN THE NATIVE PROJECT. OTHERWISE, THINGS WOULD BREAK!!!
    //
    public const int NUM_GENE = 20;

    //
    // Importing relevant methods from the native code project
    //

    //
    // Importing relevant methods from the native code project
    //

    #region extertnal methods
    [DllImport(@"C:\gitHub\AWorDS\Code\MawWeb\wwwroot_ekngine\Bin\maw.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int Initialize(String[] geneFullNames, String[] geneShortNames, int nGenes, String dataDir);

    [DllImport(@"C:\gitHub\AWorDS\Code\MawWeb\wwwroot_ekngine\Bin\maw.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int getDiffMatrix([Out] double[,] diffMatrix, int absWordType, int diffIndex);

    [DllImport(@"C:\gitHub\AWorDS\Code\MawWeb\wwwroot_ekngine\Bin\maw.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int getRanks([Out] int[,] rank, int absWordType, int diffIndex);

    #endregion
}