using System;
using System.IO;
using System.Reflection;
using ManagedOTN;

namespace ManagedOTNTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var exporter = new PdfExport();

            // use a watermark image
            exporter.EnableWatermark = true;
            exporter.WatermarkImagePath = @"C:\Users\Ryan\Pictures\oracle.png";

            // convert the document
            if (!exporter.Convert(@"E:\Documents\Backup\foo.txt", @"c:\users\ryan\desktop\foo.pdf"))
            {
                int code = exporter.GetLastErrorCode();
                Console.WriteLine(exporter.GetErrorMessage(code));
            }
        }
    }
}
