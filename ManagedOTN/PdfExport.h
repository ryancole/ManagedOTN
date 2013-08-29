#include <Windows.h>

using namespace System;

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
            bool Convert(String^ source, String^ destination);
            bool RunExport(int handle);
            bool Initialize();
            bool CloseExport(int handle);
            bool DeInitialize();
            bool CloseDocument(int handle);
            int OpenExport(int handle, String^ path);
            int GetLastErrorCode();
            int OpenDocument(String^ path);
            String^ GetErrorMessage(int code);

            // public properties
            property String^ FontDirectory;
            property bool EnableWatermark;
            property String^ WatermarkImagePath;
    };
}