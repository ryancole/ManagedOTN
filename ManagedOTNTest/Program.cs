using System;
using ManagedOTN;

namespace ManagedOTNTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var exporter = new PdfExport();

            if (exporter.Initialize())
            {
                int documentHandle = exporter.OpenDocument(@"E:\Documents\Backup\foo.txt");

                if (documentHandle > 0)
                {
                    if (exporter.SetFontDirectory(documentHandle, Environment.GetFolderPath(Environment.SpecialFolder.Fonts)))
                    {
                        int exportHandle = exporter.OpenExport(documentHandle, @"c:\users\ryan\desktop\foo.pdf");

                        if (exportHandle > 0)
                        {
                            if (exporter.RunExport(exportHandle) == false)
                            {
                                Console.WriteLine("wtfx0r");
                                Console.WriteLine(exporter.GetLastErrorCode());
                            }

                            exporter.CloseExport(exportHandle);
                        }
                    }

                    exporter.CloseDocument(documentHandle);
                }

                exporter.DeInitialize();
            }
        }
    }
}
