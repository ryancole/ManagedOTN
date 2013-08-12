using System;
using ManagedOTN;

namespace ManagedOTNTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var exporter = new PdfExport();

            // set options
            exporter.FontDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Fonts);

            // convert document
            if (exporter.Convert(@"E:\Documents\Backup\foo.txt", @"c:\users\ryan\desktop\foo.pdf"))
            {
                Console.WriteLine("good");
            }
            else
            {
                Console.WriteLine(exporter.GetLastErrorCode());
            }
        }
    }
}
