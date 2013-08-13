#include <Windows.h>

namespace ManagedOTN
{
    public ref class PdfExport
    {
        private:

            // private variables
            int lastErrorCode;

            // private methods
            void ApplyOptions(int handle);

        public:

            // public methods
            bool Convert(System::String^ source, System::String^ destination);
            bool RunExport(int handle);
            bool Initialize();
            bool CloseExport(int handle);
            bool DeInitialize();
            bool CloseDocument(int handle);
            int OpenExport(int handle, System::String^ path);
            int GetLastErrorCode();
            int OpenDocument(System::String^ path);
            System::String^ GetErrorMessage(int code);

            // public properties
            property System::String^ FontDirectory;
    };
}