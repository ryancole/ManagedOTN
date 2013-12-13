#ifndef WINDOWS
	#define WIN32
	#define WINDOWS
#endif

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
			bool Initialize();
			bool DeInitialize();
            void ApplyOptions(int handle);

        public:

			PdfExport();
			~PdfExport();

            // public methods
			int OpenExport(int handle, String^ path);
			int OpenDocument(String^ path);
			int GetLastErrorCode();
            bool Convert(String^ source, String^ destination);
            bool RunExport(int handle);
            bool CloseExport(int handle);
            bool CloseDocument(int handle);
            String^ GetErrorMessage(int code);

            // public properties
			property bool EnableWatermark;
			property bool UseDefaultPageSettings;
			property float PageWidth;
			property float PageHeight;
            property String^ FontDirectory;
            property String^ WatermarkImagePath;
    };
}
