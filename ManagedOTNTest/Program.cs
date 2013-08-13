using System;
using ManagedOTN;

namespace ManagedOTNTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var exporter = new PdfExport();

            if (!exporter.Convert(@"E:\Documents\Backup\foo.txt", @"c:\users\ryan\desktop\foo.pdf"))
            {
                int code = exporter.GetLastErrorCode();
                Console.WriteLine(exporter.GetErrorMessage(code));
            }
        }
    }
}
