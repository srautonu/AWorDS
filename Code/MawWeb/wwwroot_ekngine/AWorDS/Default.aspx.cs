
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
    //
    // Debug hooks. All these must be set to false before publishing the project
    //
    #region Debuggin Hooks
    bool testing = false;
    bool bypassExpCreation = false;
    #endregion

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
        if (bypassExpCreation)
        {
            ExpName = "Maw_RC";
            ExpPath = @"C:\gitHub\AWorDS\Code\MawWeb\wwwroot_ekngine\AWorDS\data\" + ExpName;
        }

        this.msg1.Visible = !String.IsNullOrEmpty(this.ExpName);
        this.msg1.Text = "Experiment name:" + this.ExpName;

         if (testing)
            LaunchCommandLineMAWapp();
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

                using (ZipArchive archive = ZipFile.OpenRead(Path.Combine(this.ExpPath, fileName)))
                {
                    ZipFileExtensions.ExtractToDirectory(archive, ExpPath);
                }
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
    private void LaunchCommandLineMAWapp()
    {
        try
        {
            List<string> seqFullNames = new List<string>();
            List<string> seqShortNames = new List<string>();

            if (this.ExpPath == "")
                this.ExpPath = @"E:\Ekngine\ekngine.com\wwwroot_ekngine\AWorDS\data\www";
            string SpeciesOrderPath = Path.Combine(ExpPath, "SpeciesOrder.txt");
            if (!File.Exists(SpeciesOrderPath) && !testing)
            {
                this.LabelMAWRes.Visible = true;
                this.LabelMAWRes.Text = "File SpeciesOrder.txt does not exists!";
                return;
            }
            if (!testing)
            {
                string[] SpeciesArray = File.ReadAllLines(SpeciesOrderPath);
                foreach (string s in SpeciesArray)
                {
                    string[] temp = s.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
                    seqFullNames.Add(temp[0]);
                    seqShortNames.Add(temp[1]);
                }
            }

            int absWordType = 1;
            int diffIndex = 1;
            string indexType = "";

            string wordType = this.DropDownListWordType.SelectedValue;
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

            string outputType = this.DropDownListOutputType.SelectedValue;

            diffIndex = int.Parse(indexType);
            double[,] diffMatrixLocal = new double[InteropMAW.NUM_GENE, InteropMAW.NUM_GENE];
            int[,] rank = new int[InteropMAW.NUM_GENE, InteropMAW.NUM_GENE];

            StringBuilder talbeSB = new StringBuilder();
            int ret = 0;
            if (!testing)
                 ret = InteropMAW.Initialize(seqFullNames.ToArray(), seqShortNames.ToArray(), seqFullNames.Count, ExpPath);

            if (outputType == "Distance_Matrix")
            {
                if (!testing)
                    InteropMAW.getDiffMatrix(diffMatrixLocal, absWordType, diffIndex);

                #region format the output (Diff Matrix) as table
                
                talbeSB.Append("<table class=\"table1\">");
                talbeSB.Append("<thead>");
                talbeSB.Append("<tr>");
                talbeSB.Append("<th></th>");
                for (int i = 0; i < seqFullNames.Count; i++)
                {
                    talbeSB.Append(string.Format("<th scope = \"col\" abbr=\"Starter\">{0}</th>", seqShortNames[i]));
                }
                talbeSB.Append("</tr>");
                talbeSB.Append("</thead>");
                talbeSB.Append("<tbody>");
                for (int i = 0; i < seqFullNames.Count; i++)
                {
                    talbeSB.Append("<tr>");
                    talbeSB.Append(string.Format("<th scope=\"row\">{0}</th>", seqShortNames[i]));
                    for (int j = 0; j <= i; j++)
                    {
                        talbeSB.Append("<td></td>");
                    }

                    for (int j = i + 1; j < seqFullNames.Count; j++)
                    {
                        //talbeSB.Append(string.Format("<td>{0}, {1}</td>", i, j));
                        talbeSB.Append(string.Format("<td>{0}</td>", Math.Round((double)diffMatrixLocal.GetValue(i, j), 2)));
                    }
                    talbeSB.Append("</tr>");
                }
                talbeSB.Append("</tbody>");
                talbeSB.Append("</table>");
                #endregion
            }
            else if (outputType ==  "Sorted_Difference_Tables")
            {
                if (!testing)
                    InteropMAW.getRanks(rank, absWordType, diffIndex);

                #region format the output (Species Distance Matrix) as table

                talbeSB.Clear();
                talbeSB.Append("<br \">");
                talbeSB.Append("<table class=\"table1\">");
                talbeSB.Append("<thead>");
                talbeSB.Append("<tr>");
                talbeSB.Append("<th></th>");
                //for (int i = 0; i < SeqNames.Count; i++)
                //{
                //    talbeSB.Append(string.Format("<th scope = \"col\" abbr=\"Starter\">{0}</th>", SeqNames.Values.ElementAt(i)));
                //}
                talbeSB.Append("</tr>");
                talbeSB.Append("</thead>");
                talbeSB.Append("<tbody>");
                for (int i = 0; i < seqFullNames.Count; i++)
                {
                    talbeSB.Append("<tr>");
                    talbeSB.Append(string.Format("<th scope=\"row\">{0}</th>", seqShortNames[i]));
                    for (int j = 1; j < seqFullNames.Count; j++)
                    {
                        talbeSB.Append(string.Format("<td>{0}</td>", seqShortNames[(int)rank.GetValue(i, j)]));
                    }
                    talbeSB.Append("</tr>");
                }
                talbeSB.Append("</tbody>");
                talbeSB.Append("</table>");
                
                #endregion
            }

            LabelMAWRes.Text = "Dissimilarity Index Used: ";
            if (wordType == "1")
            {
                LabelMAWRes.Text += DropDownListIndexTypeMAW.SelectedItem.Text;
            }
            else if (wordType == "2")
            {
                LabelMAWRes.Text += DropDownListIndexTypeRAW.SelectedItem.Text;
            }
            LabelMAWRes.Text += "<br />";

            LabelMAWRes.Text += talbeSB.ToString();
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
        string path = Server.MapPath("~/awords/data") + "\\" + expName;

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
            catch (System.Exception ex)
            {
                msg1.Text = "Error";
            }

        }

    }
}
    


 
