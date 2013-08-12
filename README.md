ManagedOTN provides a C++/CLI wrapper around Oracle's [Outside-In](http://www.oracle.com/us/technologies/embedded/025613.htm) libraries.

![Godzilla](http://i.imgur.com/U33qoR2.png "Godzilla")

I don't know how to explain the install process, yet.

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
