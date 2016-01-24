<%@ WebHandler Language="C#" Class="UploadHandler" %>

using System;
using System.Web;

public class UploadHandler : IHttpHandler {

    public void ProcessRequest(HttpContext context)
	{
		HttpFileCollection files = context.Request.Files;
		foreach (string key in files)
		{
			HttpPostedFile file = files[key];
			string fileName = file.FileName;
			fileName = context.Server.MapPath("~/SimpliSMS/data/" + fileName);
			file.SaveAs(fileName);
		}
		context.Response.ContentType = "text/plain";
		context.Response.Write("File uploaded successfully!");
	}

    public bool IsReusable
    {
        get
        {
            return false;
        }
    }
}