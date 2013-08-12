#include <Windows.h>

namespace ManagedOTN
{
    public ref class PdfExport
    {
        private:

            // private variables
            int lastErrorCode;

            // private methods
            void SetOptions(int handle);

        public:

            // public methods
            bool Initialize();
            bool DeInitialize();
            bool CloseDocument(int handle);
            bool CloseExport(int handle);
            bool RunExport(int handle);
            int OpenDocument(System::String^ path);
            int OpenExport(int handle, System::String^ path);
            int GetLastErrorCode();
            bool Convert(System::String^ source, System::String^ destination);

            // public properties
            property System::String^ FontDirectory;
    };
}