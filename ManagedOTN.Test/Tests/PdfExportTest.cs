using System;
using System.IO;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ManagedOTN;

namespace ManagedOTN.Test
{
    [TestClass]
    public class PdfExportTests
    {
        #region Methods

        [TestMethod]
        public void CanPdfDocument()
        {
            var temporary = Path.GetTempFileName();

            using (var exporter = new PdfExport())
            {
                Assert.IsTrue(exporter.Convert(temporary, Path.ChangeExtension(temporary, "pdf")));
            }
        }

        #endregion
    }
}
