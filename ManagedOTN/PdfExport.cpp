#include <sccda.h>
#include <sccex.h>
#include <vcclr.h>
#include "PdfExport.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ManagedOTN
{
    bool PdfExport::SetFontDirectory(int handle, String^ path)
    {
        IntPtr p = Marshal::StringToHGlobalAnsi(path);
        char* z = static_cast<char*>(p.ToPointer());

        this->lastErrorCode = DASetOption(handle, SCCOPT_FONTDIRECTORY, (VTLPVOID)z, sizeof(char) * path->Length);

        Marshal::FreeHGlobal(p);

        if (this->lastErrorCode != DAERR_OK)
            return false;

        return true;
    }

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
}