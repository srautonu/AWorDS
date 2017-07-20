<%@ Page Language="C#" AutoEventWireup="true" MaintainScrollPositionOnPostback="true" CodeFile="Default.aspx.cs" Inherits="Default" %>

<%@ Register Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" TagPrefix="asp"  %>

<%@ Register Assembly="MSCaptcha" Namespace="MSCaptcha" TagPrefix="cc1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Absent words and the (dis)similarity analysis of DNA sequences: An Experimental Study</title>
    <link rel="stylesheet" type="text/css" href="http://fonts.googleapis.com/css?family=Tangerine&amp;v1" />
    <link rel="stylesheet" type="text/css" href="http://fonts.googleapis.com/css?family=Yanone+Kaffeesatz" />
    <script type="text/javascript" src="jquery.min.js"></script>
    <script src="jquery-ui.js" type="text/jscript"></script>
    <link href="jquery-ui.css" rel="stylesheet" />
    <link href="common.css" rel="stylesheet" />
    <link href="justified-nav.css" rel="stylesheet"/>
      <link rel="stylesheet" href="/style/table.css" type="text/css" media="screen"/>
    <!-- jit -->
    <link type="text/css" href="jit/css/base.css" rel="stylesheet" />
    <link type="text/css" href="jit/css/Spacetree.css" rel="stylesheet" />
    <!--[if IE]><script language="javascript" type="text/javascript" src="jit/Extras/excanvas.js"></script><![endif]-->

    <!-- JIT Library File -->
    <script language="javascript" type="text/javascript" src="jit/jit.js"></script>

    <!-- Example File -->
    
    <script type="text/jscript">
        function ValidateUploadFileType() {
            if (document.getElementById("<%=txtCaptcha.ClientID%>").value == "") {
                alert("Please fill the box.");
                return false;
            }

            if (document.getElementById("<%=FileUpload1.ClientID%>").value == "") {
                alert("Please select the file to upload.");
                return false;
            }
            else {
                var value = document.getElementById("<%=FileUpload1.ClientID%>").value,
                ext = value.split(".").pop();
                var filesize = document.getElementById("<%=FileUpload1.ClientID%>");
                if ( ext == "zip" ) {
                    if (filesize.files[0].size > 1073741824/5) {
                        alert("File size is greater than 10 MB. ");
                        return false;
                    }
                    return true;
                }
                else //if (ext == "exe" || ext == "rar" || ext == "zip" || ext == "hex")
                {
                    alert("Please select a valid file format.");
                    return false;
                }

            }
        }
        function ShowProgress() {
            setTimeout(function () {
                var modal = $('<div />');
                modal.addClass("modal");
                $('body').append(modal);
                var loading = $(".loading");
                loading.show();
                var top = Math.max($(window).height() / 2 - loading[0].offsetHeight / 2, 0);
                var left = Math.max($(window).width() / 2 - loading[0].offsetWidth / 2, 0);
                loading.css({ top: top, left: left });
            }, 300);
        }
        $('form').live("submit", function () {
            ShowProgress();
        });
    </script>

</head>

<body   >
    <form id="form1" runat="server">
        <div id="main">
            <div id="header" style=" background-color :Black">
              <div id="logo" style="padding-top:10px;"> 
              <h1 >AWorDS  &nbsp;</h1>
              <br />
              </div>
              <br />
            </div>
        </div>
        <div id="site_content" style="margin-top:0px;" >
            <div id="sidebar_container" >
           
                 <!--
                    <div class="sidebar">
                    <h3>Navigation</h3>
                        <ul>
                        <li><a class="nav" href="Default.aspx">Home</a></li>
                        <li><a class="nav" href="App.aspx">Demo</a></li>
                        </ul>
                        </div>
                     -->
                <div class="sidebar">
                    <h3>Contact Details</h3>
                    <p>Mohammad Saifur Rahman<br />
                    Department of CSE, BUET<br />
                    <a href="#">mrahman[@]cse.buet.ac.bd</a></p>
                    <!--
                    <h4>Last updated on</h4>
                    <h5>22nd December 2014</h5>
                    <p>
                    Department of Informatics, 
                    King's College London,
                    Strand,<br /> 
                    London <br /> 
                    WC2R 2LS,<br />  
                    UK.<br />
                    <a href="#">ali.alatabbi(at)kcl.ac.k </a></p>
                    -->
                </div>
                
            </div>
            <div id="content">
                <div class="sidebar" style=" width:97%; float:left;">
                    <br />
                    <h1>Absent Word Based (Dis)similarity analysis of Sequences</h1>
                    <h5> By; Mohammad Saifur Rahman, Ali Alatabbi, Tanver Athar, Maxime Crochemore, M. Sohel Rahman</h5>
                    <hr />
                    <h2>AWorDS</h2>
                    <br />
                    <p>
                        Welcome to the <b>A</b>bsent <b>Wor</b>d Based (<b>D</b>is)similarity analysis of <b>S</b>equences;
                        <b>AWorDS</b> in short. (Pronounced like "Awards"). This tool takes the set of Minimal Absent Words (MAW) or
                        Relative Absent Words (RAW) of several sequences and produces the distance matrix based on a number of
                        indices. 
                        <br />
                        The distance matrix can be used to demonstrate relative closeness of the sequences. It can also be used
                        to produce phylogenetic trees using a number of known algorithms.
                    </p>
					
				    <h4>Acknowledgements</h4>
                    <p>
                        Partially supported by the INSPIRE Strategic Partnership Award, administered by the British Council, Bangladesh for the project titled "Advances in Algorithms for Next Generation Biological Sequences".
                    </p>

                    <!-- <hr />
                    <h2>Future Direction </h2>
                    <p> <</p>-->
                    <br />
                    <hr />
                    <h2>Try it Out!</h2>
                    <p  style="font-size:15px; font-weight:bold; color:red;">Step 1: Create new experiment</p>
                    <asp:Label ID="Label3" runat="server" >Give your experiment a name and click the create button</asp:Label>
                    <br /><br />
                     
                    
                    <asp:TextBox ID="TextBoxExpName" style="font-size:20px;" runat="server"></asp:TextBox>
                     <br />
                     <br />
                    <asp:Button ID="ButtonCreateExp" class="buttonstyleCss" runat="server" Text="Create" OnClick="ButtonCreateExp_Click" />
                     <br />
                   
                   <br />
                    <asp:Label style="font-size:12px; border:1px solid #CBD1D2; background-color:#bef4ec; color:#151813; padding:5px; width:585px;" ID="msg1" runat="server" Width="100%" Visible="false"></asp:Label>
                      <br />  <br />

                         <!-- upload -->
                    <p  style="font-size:15px; font-weight:bold; color:red;">Step 2: Upload data</p>
                    <div id="DivownMotif" runat="server">
                        <p style="font-size:13px; font-weight:bold; margin:2px;">Important:</p>
                        <p style="font-size:12px; margin:1px;">1. Upload a single .zip file containing all your data files.</p>
                        <p style="font-size:12px; margin:1px;">2. See the ReadMe.txt file at <a href='http://github.com/srautonu/AWorDS/tree/master/Data/Input'>http://github.com/srautonu/AWorDS/tree/master/Data/Input</a> for exact composition that your .zip file should have.</p>
                        <p style="font-size:12px; margin:1px;">3. Sample .zip files are available in the above location as well. These were used during our experimenal studies.</p>
                        <p style="font-size:12px; margin:1px;">4. The size of each absent word (MAW or RAW) file  must be less than 10MB.</p>
                        <p style="font-size:12px; margin:1px;">5. Your uploaded file will be deleted at the end of the session.</p>
                        <br />
                        <p style="font-size:13px; font-weight:bold; margin:2px;">Select your zip archive then click upload</p>
                        <asp:FileUpload ID="FileUpload1" runat="server" class="fileUpload"/>
                         
                        <br /> 
                        
                        <br />
                        <div class="loading" align="center">
                            Processing. Please wait...<br /><br />
                            <img src="loader.gif" alt="" style="width:30px;height:30px;"/>
                        </div>
                        <br /><br />
                        <div id="CaptchaBox">
                            <table border="0" cellpadding="3" cellspacing="0" style="border:1px solid #CBD1D2; padding:10px; width:200px;">
                                    <tr>
                                        <td colspan="2">
                                            <cc1:CaptchaControl ID="Captcha1" runat="server" CaptchaBackgroundNoise="Low" CaptchaLength="6"
                                                CaptchaHeight="32" CaptchaWidth="150" CaptchaMinTimeout="5" CaptchaMaxTimeout="240"
                                                FontColor="Blue" NoiseColor="#B1B1B1" />
                                        </td>
                                        <td>
                                            <asp:ImageButton ID="ImageButton1" ImageUrl="~/refresh.png" runat="server" CausesValidation="false" />
                                        </td>
                                    </tr>
                                    <tr>
                                        <td style="font-size:14px;">
                                            Enter Text :
                                        </td>
                                        <td colspan="2">
                                        </td>
                                    </tr>
                                    <tr>
                                        <td colspan="2">
                                            <asp:TextBox ID="txtCaptcha" runat="server" EnableViewState="false" style="height:25px; font-size:13px;"></asp:TextBox>
                                        </td>
                                        <td>
                                        
                                        </td>
                                    </tr>
                                    <tr>
                                        <td colspan="3">
                                            <asp:CustomValidator ID="CustomValidator1" style="color:red;" ErrorMessage=""  OnServerValidate="ValidateCaptcha" runat="server" />
                                        </td>
                                    </tr>
                            </table>
                        
                            <asp:Label ID="msg2" style="font-size:12px; border:1px solid #CBD1D2; background-color:#bef4ec; color:#151813; padding:5px; width:585px;"  runat="server" Width="100%" Visible="false"></asp:Label>
                            <br /> 
                            <asp:Button ID="upAndSearch" runat="server" Text="Upload" OnClientClick="javascript:return ValidateUploadFileType();" class="buttonstyleCss"/>  

                        </div>
                        
                    </div>

                    
                    <br />
                    <p  style="font-size:15px; font-weight:bold; color:red;">Step 3: Select the experiment configuration</p>

                      <asp:Label ID="Label2" runat="server"  >Select type of absent word</asp:Label>
                     <br /><br />
                    <asp:DropDownList ID="DropDownListWordType"   style="font-size:16px;height:20px" runat="server">
                        <asp:ListItem Text="MAW - Minimum abset word" Value="1"/>
                        <asp:ListItem Text="RAW - Relative absent word" Value="2"/> 
                    </asp:DropDownList> 
                     <br /><br />
                     <asp:Label ID="Label1" runat="server">Select MAW based dissimilarity index.</asp:Label>
                     <br /><br />
                    <asp:DropDownList ID="DropDownListIndexTypeMAW" style="font-size:16px; height:20px;" runat="server">
                           <asp:ListItem Text="MAW_LWI_SDIFF - Length weighted index of symmetric difference of MAW sets" Value="1"/>
                           <asp:ListItem Text="MAW_LWI_INTERSECT - Length weighted index of intersection of MAW sets" Value="2"/>
                           <asp:ListItem Text="MAW_GCC_SDIFF - GC content of symmetric difference of MAW sets" Value="3"/>
                           <asp:ListItem Text="MAW_GCC_INTERSECT - GC content of intersection of MAW sets" Value="4"/>
                           <asp:ListItem Text="MAW_JD - Jaccard Distance of MAW sets" Value="5"/>
                           <asp:ListItem Text="MAW_TVD - Total Variation Distance of MAW sets" Value="6"/>
                    </asp:DropDownList>
                      <br /><br />
                    <asp:Label ID="Label5" runat="server">Select RAW based dissimilarity index</asp:Label>
                     <br /><br />
                    <asp:DropDownList ID="DropDownListIndexTypeRAW" style="font-size:16px; height:20px;" runat="server">
                           <asp:ListItem Text="RAW_LWI - Length weighted index of RAW set" Value="1"/>
                           <asp:ListItem Text="RAW_GCC - GC content of RAW set" Value="2"/>
                    </asp:DropDownList>
                     <br /><br />
                      <asp:Label ID="Label4" runat="server"  >Select output type</asp:Label>
                     <br /><br />
                    <asp:DropDownList ID="DropDownListOutputType"   style="font-size:16px;height:20px" runat="server">
                        <asp:ListItem Text="Distance Matrix" Value="Distance_Matrix"/>
                        <asp:ListItem Text="Sorted Difference Tables" Value="Sorted_Difference_Tables"/>
                    </asp:DropDownList>     
                     
                    <br /><br />
                
                    <p id="P3" style="font-size:15px; font-weight:bold; color:red;">Step 4: Run the experiment</p>
                    
                   <asp:Button ID="Button1"  class="buttonstyleCss" runat="server" onclick="Button1_Click" Text="&nbsp;&nbsp;Run&nbsp;&nbsp;" />
                    <br />  <br />
                      <hr />                       
                    </div>

                 <div runat="server" id="dirTree" visible="true">
                 <div id="res" >
               
                 <h2>Results </h2>
                       <br /> 
                      <asp:Label ID="LabelMAWRes" style="padding:5px; "  runat="server" Width="100%" ></asp:Label>
                 </div>     
                        <hr />
                        <p>&nbsp;</p>
                        <br />
               </div>
                <div id="footer">   
                </div>
            </div>
        </div> 
    </form>
</body>
</html>

