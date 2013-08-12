#include <Windows.h>

namespace ManagedOTN
{
    public ref class PdfExport
    {
        private:

            int lastErrorCode;

        public:

            bool Initialize();
            bool DeInitialize();
            bool CloseDocument(int handle);
            bool CloseExport(int handle);
            bool RunExport(int handle);
            bool SetFontDirectory(int handle, System::String^ path);
            int OpenDocument(System::String^ path);
            int OpenExport(int handle, System::String^ path);
            int GetLastErrorCode();
    };
}