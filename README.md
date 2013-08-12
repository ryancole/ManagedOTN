ManagedOTN provides a C++/CLI wrapper around Oracle's [Outside-In](http://www.oracle.com/us/technologies/embedded/025613.htm) libraries.

![Godzilla](http://i.imgur.com/U33qoR2.png "Godzilla")

## Compiling

Compiling ManagedOTN requires that you can link to the Outside In libraries, and include their headers. You can download their various products, for free, from [their website](http://www.oracle.com/technetwork/middleware/content-management/downloads/oit-dl-otn-097435.html). Once downloaded, you need to add `sccda.lib` and `sccex.lib` as additional linker input dependencies within the ManagedOTN project. You also need to add the `sdk\common` directory, within the Outside In directory, to the ManagedOTN project's list of additional include directories. With these settings in place, and .NET 4.5 installed, you should be able to compile and run the included C# application, ManagedOTNTest.

## Examples

```csharp
var exporter = new PdfExport();

// set options
exporter.FontDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Fonts);

// convert document
if (!exporter.Convert(@"foo.txt", @"foo.pdf"))
{
    Console.WriteLine(exporter.GetLastErrorCode());
}
```
