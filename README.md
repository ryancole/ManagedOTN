ManagedOTN provides a C++/CLI wrapper around Oracle's [Outside-In](http://www.oracle.com/us/technologies/embedded/025613.htm) libraries.

![Godzilla](http://i.imgur.com/U33qoR2.png "Godzilla")

## Compiling

Compiling ManagedOTN requires that you can link to the Outside In libraries, and include their headers. You can download their various products, for free, from [their website](http://www.oracle.com/technetwork/middleware/content-management/downloads/oit-dl-otn-097435.html). Once downloaded, you need to add `sccda.lib` and `sccex.lib` as additional linker input dependencies within the ManagedOTN project. You also need to add the `sdk\common` directory, within the Outside In directory, to the ManagedOTN project's list of additional include directories. With these settings in place, and .NET 4.5 installed, you should be able to compile and run the included C# application, ManagedOTNTest.

## Example

```csharp
var temporary = Path.GetTempFileName();

using (var exporter = new PdfExport())
{
    exporter.Convert(temporary, Path.ChangeExtension(temporary, "pdf"));
}
```

## ManagedOTN::PdfExport Methods

#### bool Convert(string source, string destination)

The `Convert` function is a convenience method that encapsulates the complete conversion process. It makes calls to the other functions provided by `PdfExport`. The function takes a `source` parameter, converts it to a PDF document and finally saves it to the `destination` path. `Convert` returns a boolean indicating success (`true`) or failure (`false`).

When using the `Convert` function, it is not necessary to call any of the other functions, such as `Initialize` or `DeInitialize`.

#### bool Initialize()

The `Initialize` function simply initializes the underlying Outside In engine. It returns a boolean indicating success (`true`) or failure (`false`). `Initialize` must be called before making calls to any subsequent `PdfExport` functions, unless you're using the `Convert` function.

#### bool DeInitialize()

The `DeInitialize` function cleans up and disposes of the underyling Outside In engine. It returns a boolean indicating success (`true`) or failure (`false`). `DeInitialie` must be called when the `PdfExport` is no longer needed, unless you're using the `Convert` function.

#### int OpenDocument(string path)

The `OpenDocument` function opens the source document for reading. A source document must be opened before you can export a PDF. `OpenDocument` returns an integer indicating the opened document's handle. The document handle is used by other functions, such as `OpenExport`. The document handle will have a positive value if the `OpenDocument` function succeeded, otherwise the returned document handle will be zero.

#### bool CloseDocument(int handle)

The `CloseDocument` function closes an open document for the given `handle`. It returns a boolean indicating success (`true`) or failure (`false`). You must close documents when you are finished with them.

#### int OpenExport(int handle, string path)

The `OpenExport` function, given an open document `handle`, opens the output destination file, at `path`, for writing. A destination document must be opened before you can export a PDF. `OpenExport` returns an integer indicating the opened export's handle. The export handle is used by the `RunExport` function. The export handle will have a positive value if the `OpenExport` function succeeded, otherwise the returned export handle will be zero.

#### bool CloseExport(int handle)

The `CloseExport` function closes an open export for the given `handle`. It returns a boolean indicating success (`true`) or failure (`false`). You must close exports when you are finished with them.

#### bool RunExport(int handle)

The `RunExport` function, given an open export `handle`, will export a PDF of the opened document for the given export `handle`. It returns a boolean indicating success (`true`) or failure (`false`).

#### int GetLastErrorCode()

Returns an integer containing the last error code. So if another function fails, this code should reflect the error that occurred.

#### string GetErrorMessage(int code)

Convert a given error `code` to an actual error message.

## ManagedOTN::PdfExport Properties

#### string FontDirectory

Gets and sets the directory in which the desired font files are located. This defaults to the system-defined fonts directory.
