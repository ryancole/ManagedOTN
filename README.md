ManagedOTN provides a C++/CLI wrapper around Oracle's [Outside-In](http://www.oracle.com/us/technologies/embedded/025613.htm) libraries.

![Godzilla](http://i.imgur.com/U33qoR2.png "Godzilla")

## Compiling

Compiling ManagedOTN requires that you can link to the Outside In libraries, and include their headers. You can download their various products, for free, from [their website](http://www.oracle.com/technetwork/middleware/content-management/downloads/oit-dl-otn-097435.html). Once downloaded, you need to add `sccda.lib` and `sccex.lib` as additional linker input dependencies within the ManagedOTN project. You also need to add the `sdk\common` directory, within the Outside In directory, to the ManagedOTN project's list of additional include directories. With these settings in place, and .NET 4.5 installed, you should be able to compile and run the included C# application, ManagedOTNTest.

## Example

```csharp
var exporter = new PdfExport();

if (!exporter.Convert(@"foo.xls", @"foo.pdf"))
{
    int error = exporter.GetLastErrorCode();
    Console.WriteLine(exporter.GetErrorMessage(error));
}
```

## ManagedOTN::PdfExport

### bool Convert(string source, string destination)

The `Convert` function is a convenience method that encapsulates the complete conversion process. It makes calls to the other functions provided by `PdfExport`. The function takes a `source` parameter, converts it to a PDF document and finally saves it to the `destination` path. `Convert` returns a boolean indicating success (`true`) or failure (`false`).

When using the `Convert` function, it is not necessary to call any of the other functions, such as `Initialize` or `DeInitialize`.

### bool Initialize()

The `Initialize` function simply initializes the underlying Outside In engine. It returns a boolean indicating success (`true`) or failure (`false`). `Initialize` must be called before making calls to any subsequent `PdfExport` functions, unless you're using the `Convert` function.

### bool DeInitialize()

The `DeInitialize` function cleans up and disposes of the underyling Outside In engine. It returns a boolean indicating success (`true`) or failure (`false`). `DeInitialie` must be called when the `PdfExport` is no longer needed, unless you're using the `Convert` function.

### int OpenDocument(string path)

The `OpenDocument` function opens the source document for reading. A source document must be opened before you can export a PDF. `OpenDocument` returns an integer indicating the opened document's handle. The document handle is used by other functions, such as `OpenExport`. The document handle will have a positive value if the `OpenDocument` function succeeded, otherwise the returned document handle will be zero.

### bool CloseDocument(int handle)

The `CloseDocument` function closes an open document for the given `handle`. It returns a boolean indicating success (`true`) or failure (`false`). You must close documents when you are finished with them.
