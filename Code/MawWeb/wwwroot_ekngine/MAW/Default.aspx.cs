
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Net.Mail;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Web;
using System.Web.Services;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;

 
 
public partial class Default : System.Web.UI.Page
{
    string ExpName
    {
        get
        {
            if (Session["ExpName"] == null)
                return "";
            return (string)this.Session["ExpName"];
        }
        set
        {
            this.Session["ExpName"] = value;
        }
    }
    string ExpPath
    {
        get
        {
            if (Session["ExpPath"] == null)
                return "";
            return (string)this.Session["ExpPath"];
        }
        set
        {
            this.Session["ExpPath"] = value;
        }
    }

    List<string> SequenceNames
    {
        get
        {
            if (Session["SequenceNames"] == null)
                return new List<string>();
            return (List<string>)this.Session["SequenceNames"];
        }
        set
        {
            this.Session["SequenceNames"] = value;
        }

    }
    
    protected void Page_Load(object sender, EventArgs e)
    {
        this.msg1.Visible= !String.IsNullOrEmpty(this.ExpName);
        this.msg1.Text = "Experiment name:" + this.ExpName;
    }
 
    protected void uploadFiles()
    {
        this.txtCaptcha.Text = "";
        bool dataOkay = false;
         
        dataOkay = this.FileUpload1.HasFile;
        if (dataOkay)
        {
           
            try
            {
                string fileName = this.FileUpload1.FileName;
                //this.SequenceNames.Add();
                this.FileUpload1.SaveAs(Path.Combine(this.ExpPath, fileName));

                ZipArchive archive = ZipFile.OpenRead(Path.Combine(this.ExpPath, fileName));
                ZipFileExtensions.ExtractToDirectory(archive, ExpPath);
                    
                this.msg2.Visible = true;
                this.msg2.Text = "Files uploaded successfully.";
                 
                
            }
            catch (System.Exception)
            {
                this.msg2.Visible = true;
                this.msg2.Text = "Error uploading files.";
            }
        }   
    }

    protected void ValidateCaptcha(object sender, ServerValidateEventArgs e)
    {

        Captcha1.ValidateCaptcha(txtCaptcha.Text.Trim());
        e.IsValid = Captcha1.UserValidated;
        if (e.IsValid)
        {
            this.uploadFiles();
        }
        else
        {
            this.txtCaptcha.Text = "";
            this.CustomValidator1.Text = "Captcha mismatch.";
           
        }
    }
 
    protected void Button1_Click(object sender, EventArgs e)
    {
        LaunchCommandLineMAWapp();
    }
    protected void Page_PreRender(object sender, EventArgs e)
    {
        
    }
    private  void LaunchCommandLineMAWapp()
    {

        try
        {
            string path = Server.MapPath("~/maw/dll/");

            Dictionary<string, string> SeqNames = new Dictionary<string, string>();
            if (this.ExpPath =="")
                this.ExpPath = @"E:\Ekngine\ekngine.com\wwwroot_ekngine\MAW\data\www";


            string SpeciesOrderPath = Path.Combine(ExpPath, "SpeciesOrder.txt");
            if (!File.Exists(SpeciesOrderPath))
            {
                this.LabelMAWRes.Visible = true;
                this.LabelMAWRes.Text = "File SpeciesOrder.txt does not exists!";
                return;
            }
            string[] SpeciesArray = File.ReadAllLines(SpeciesOrderPath);

            foreach(string s in SpeciesArray)
            {
                string[] temp = s.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
                SeqNames.Add(temp[0], temp[1]);
            }



            #region old code
            //string[] arr = Directory.GetFiles(ExpPath, "*.fasta.out");
            //Process p = new Process();
            //p.StartInfo.UseShellExecute = false;
            //p.StartInfo.RedirectStandardOutput = true;
            //p.StartInfo.FileName = path + @"\maw.exe";
            //"\"MAW_TVD\" \"MAW\" \"E:\Ekngine\ekngine.com\wwwroot_ekngine\MAW\data\exp1972"";
            //mawObject.computeDiffMatrix();
            //p.StartInfo.Arguments = String.Format("\"{0}\" \"{1}\" \"{2}\" \"{3}\" ", indexType, wordType, ExpPath, arr.Length);
            //bool render = false;
            //bool allOkay = true;
            //if (allOkay)
            //{
            //    p.Start();
            //    string output = p.StandardOutput.ReadToEnd();
            //    p.WaitForExit();
            //    string br = "<br />";
            //    LabelMAWRes.Text = output.Replace("\r\n", br);

            //    this.LabelMAWRes.Visible = true;
            //    //this.dirTree.Visible = true;
            //}
            #endregion

            int absWordType = 1;
            int diffIndex = 1;
            string wordType = this.DropDownListWordType.SelectedValue;
            string indexType = "";
            if (wordType == "1")
            {
                absWordType = 1;
                indexType = this.DropDownListIndexTypeMAW.SelectedValue;
            }
            else if (wordType == "2")
            {
                absWordType = 2;
                indexType = this.DropDownListIndexTypeRAW.SelectedValue;
            }

            diffIndex = int.Parse(indexType);
            
            // call C# methods of the mawObject here 
            int ret = InteropMAW.Initialize(SeqNames.Keys.ToArray(), SeqNames.Values.ToArray(), SeqNames.Count, ExpPath);
            double[,] diffMatrixLocal = new double[SeqNames.Count, SeqNames.Count];
            InteropMAW.getDiffMatrix(diffMatrixLocal, absWordType, diffIndex);

            //
            // display the result in the existing (less appealing) format
            // TODO: Ali, perhaps the data could be represented in tabular fashion, now that
            // you have the actual matrix
            //
            string strDisplay = "";
            for (int i = 0; i < SeqNames.Count; i++)
            {
                strDisplay += "{ ";
                for (int j = 0; j < i; j++)
                {
                    strDisplay += diffMatrixLocal.GetValue(i, j);
                    strDisplay += (j == i - 1) ? "" : ", ";
                }

                strDisplay += " }";
                if (i != SeqNames.Count - 1)
                    strDisplay += ",";
                strDisplay += "<br />";
            }

            LabelMAWRes.Text = strDisplay;
            LabelMAWRes.Visible = true;
        }
        catch (System.Exception ex)
        {
            string err = ex.Message;
            this.LabelMAWRes.Visible = true;
            this.LabelMAWRes.Text = err;
        }
    }

    protected void ButtonCreateExp_Click(object sender, EventArgs e)
    {
        string expName = this.TextBoxExpName.Text.Trim();
        string path = Server.MapPath("~/maw/data") + "\\" + expName;
        
        msg1.Visible = true;
        if (Directory.Exists(path))
        {
            msg1.Text = "The name is already in use, please choose different name";
        }
        else
        {
            try
            {
                Directory.CreateDirectory(path);
                this.ExpPath = path;
                ExpName = expName;
                msg1.Text = "New experiment has been created successfully";
            }
            catch(System.Exception ex)
            {
                msg1.Text = "Error";
            }
        
        }

    }
}
    
