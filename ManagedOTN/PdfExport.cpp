#include <sccda.h>
#include <sccex.h>
#include <vcclr.h>
#include "PdfExport.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ManagedOTN
{
    bool PdfExport::Initialize()
    {
        this->lastErrorCode = DAInitEx(DATHREAD_INIT_NATIVETHREADS, OI_INIT_DEFAULT | OI_INIT_NOLOADOPTIONS | OI_INIT_NOSAVEOPTIONS);

        if (this->lastErrorCode != DAERR_OK)
            return false;

        return true;
    }

    bool PdfExport::DeInitialize()
    {
        this->lastErrorCode = DADeInit();

        if (this->lastErrorCode != DAERR_OK)
            return false;

        return true;
    }

    bool PdfExport::CloseDocument(int handle)
    {
        this->lastErrorCode = DACloseDocument(handle);

        if (this->lastErrorCode != DAERR_OK)
            return false;

        return true;
    }

    bool PdfExport::CloseExport(int handle)
    {
        this->lastErrorCode = EXCloseExport(handle);

        if (this->lastErrorCode != SCCERR_OK)
            return false;

        return true;
    }

    bool PdfExport::RunExport(int handle)
    {
        this->lastErrorCode = EXRunExport(handle);

        if (this->lastErrorCode != SCCERR_OK)
            return false;

        return true;
    }

    int PdfExport::OpenDocument(String^ path)
    {
        // convert the string to a c string point
        pin_ptr<const wchar_t> cpath = PtrToStringChars(path);

        // the output document handle
        VTHDOC documentHandle = 0;

        // open the source document for conversion
        this->lastErrorCode = DAOpenDocument(&documentHandle, IOTYPE_UNICODEPATH, (VTLPVOID)cpath, 0);

        if (this->lastErrorCode != DAERR_OK)
            return 0;

        if (documentHandle > 0)
        {
            // set document options
            this->ApplyOptions(documentHandle);
        }

        return (int)documentHandle;
    }

    int PdfExport::OpenExport(int handle, String^ path)
    {
        // conver the string to a c string pointer
        pin_ptr<const wchar_t> cpath = PtrToStringChars(path);

        // the output export handle
        VTHEXPORT exportHandle = 0;

        // open the source document for writing
        this->lastErrorCode = EXOpenExport(handle, FI_PDF, IOTYPE_UNICODEPATH, (VTLPVOID)cpath, 0, 0, NULL, 0, &exportHandle);

        if (this->lastErrorCode != SCCERR_OK)
            return 0;

        return exportHandle;
    }

    int PdfExport::GetLastErrorCode()
    {
        return this->lastErrorCode;
    }

    bool PdfExport::Convert(String^ source, String^ destination)
    {
        bool result = false;

        if (this->Initialize())
        {
            int documentHandle = this->OpenDocument(source);

            if (documentHandle > 0)
            {
                int exportHandle = this->OpenExport(documentHandle, destination);

                if (exportHandle > 0)
                {
                    if (this->RunExport(exportHandle))
                    {
                        result = true;
                    }

                    this->CloseExport(exportHandle);
                }

                this->CloseDocument(documentHandle);
            }

            this->DeInitialize();
        }

        return result;
    }

    void PdfExport::ApplyOptions(int handle)
    {
        if (this->EnableWatermark == true)
        {
            bool toggle = true;
            this->lastErrorCode = DASetOption(handle, SCCOPT_ENABLEWATERMARK, &toggle, sizeof(bool));

            if (this->WatermarkImagePath != nullptr && this->WatermarkImagePath->Length > 0)
            {
                // set user-defined watermark path
                IntPtr p = Marshal::StringToHGlobalAnsi(this->WatermarkImagePath);
                char* z = static_cast<char*>(p.ToPointer());

                WATERMARKIO wio = {};
                WATERMARKPATH wpath = {};

                // set watermark path
                wpath.dwMaxSize = SCCUT_FILENAMEMAX;
                strncpy_s(wpath.szWaterMarkPath, z, SCCUT_FILENAMEMAX);

                // set io structure
                wio.Path = wpath;
                wio.dwType = IOTYPE_ANSIPATH;

                this->lastErrorCode = DASetOption(handle, SCCOPT_WATERMARKIO, &wio, sizeof(WATERMARKIO));

                Marshal::FreeHGlobal(p);
            }
        }
        else
        {
            bool toggle = false;
            this->lastErrorCode = DASetOption(handle, SCCOPT_ENABLEWATERMARK, &toggle, sizeof(bool));
        }

        if (this->FontDirectory == nullptr || this->FontDirectory->Length > 0)
        {
            String^ directory = Environment::GetFolderPath(Environment::SpecialFolder::Fonts);

            // if no directory set, default to system-defined directory
            IntPtr p = Marshal::StringToHGlobalAnsi(directory);
            char* z = static_cast<char*>(p.ToPointer());

            this->lastErrorCode = DASetOption(handle, SCCOPT_FONTDIRECTORY, (VTLPVOID)z, sizeof(char) * directory->Length);

            Marshal::FreeHGlobal(p);
        }
        else
        {
            // set to user-defined directory
            IntPtr p = Marshal::StringToHGlobalAnsi(this->FontDirectory);
            char* z = static_cast<char*>(p.ToPointer());

            // set font directory
            this->lastErrorCode = DASetOption(handle, SCCOPT_FONTDIRECTORY, (VTLPVOID)z, sizeof(char) * this->FontDirectory->Length);

            Marshal::FreeHGlobal(p);
        }
    }

    String^ PdfExport::GetErrorMessage(int code)
    {
        char buffer[256];

        // get the message for the given error code
        DAGetErrorString(code, &buffer, 256);

        return gcnew String(buffer);
    }
}