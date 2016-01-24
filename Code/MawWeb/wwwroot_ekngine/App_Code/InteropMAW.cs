using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Web;

/// <summary>
/// Summary description for InteropMAW
/// </summary>
public class InteropMAW
{
    public InteropMAW()
    {
        //
        // TODO: Add constructor logic here
        //
    }

    //
    // Importing relevant methods from the native code project
    //

    #region extertnal methods
    [DllImport(@"MAW.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int Initialize(String[] geneFullNames, String[] geneShortNames, int nGenes, String dataDir);

    [DllImport(@"MAW.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void getDiffMatrix([Out] double[,] diffMatrix, int absWordType, int diffIndex);

    [DllImport(@"MAW.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void printMatrix(double[,] diffMatrix);

    #endregion

    #region C# methods
    public int Init (string[] geneFullNames, string[] geneShortNames, int nGenes, string dataDir)
    {
        // make the call to the pInvoke  method here
        return 0;         
    }

    public void computeDiffMatrix(out  double[,] diffMatrix, int absWordType, int diffIndex)
    {
        // make the call to the pInvoke  method here
        double[,] diffMatrixLocal = new double[10, 10];
        diffMatrix = diffMatrixLocal;
    }

    public void formatMatrix(double[,] diffMatrix)
    {
        // make the call to the pInvoke  method here
        double[,] diffMatrixLocal = new double[10, 10];
        diffMatrix = diffMatrixLocal;
    }
    #endregion

}