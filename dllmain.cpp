#include "framework.h"
#include "headers/runtime/RuntimeHandler.h"

/**
 *
 *   ---------------- o
 * | How it's works ? |
 * o ----------------
 *
 *                           |---------------|
 *                    +++++> |  Relocations  | ======+
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 * | Segment | =======+                              -======> | Reconstruct hotpoints with new base addr  | ======> | OWN FUNCTIONS | ====> | Call Original entry point |
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 *                    +++++> |    Imports    | ======+
 *                           |---------------|
 *
 */

//Scary but necessary.
DWORD Segment::UnsafeAllocatedPointer = 0x0;
DWORD Segment::UnsafeLibraryPointer = 0x0;
SegmentFramework::oVirtualFunctionCaller SegmentFramework::OriginalVirtualCaller = 0x0;

BOOL APIENTRY DllMain(HMODULE module, DWORD callReason, LPVOID lpReserved) {

    //ALL DOCS INSIDE FUNCTIONS, AND HEADERS.

    if (callReason == DLL_PROCESS_ATTACH) {

        Segment segment;
        Logger logger (Logger::LoggerType::CONSOLE);
        RuntimeHandler runtime (segment);

        PanicUtils::SetImportant (&Segment::UnsafeLibraryPointer, reinterpret_cast<DWORD> (module));

        //Logo. 
        logger.Info("     ▄████████    ▄███████▄    ▄████████    ▄████████    ▄████████ ████████▄ ");
        logger.Info("    ███    ███   ███    ███   ███    ███   ███    ███   ███    ███ ███   ▀███");
        logger.Info("    ███    █▀    ███    ███   ███    ███   ███    █▀    ███    ███ ███    ███");
        logger.Info("    ███          ███    ███  ▄███▄▄▄▄██▀  ▄███▄▄▄       ███    ███ ███    ███");
        logger.Info("  ▀███████████ ▀█████████▀  ▀▀███▀▀▀▀▀   ▀▀███▀▀▀     ▀███████████ ███    ███");
        logger.Info("           ███   ███        ▀███████████   ███    █▄    ███    ███ ███    ███");
        logger.Info("     ▄█    ███   ███          ███    ███   ███    ███   ███    ███ ███   ▄███");
        logger.Info("  ▄████████▀   ▄████▀        ███    ███   ██████████   ███    █▀  ████████▀  ");


        logger.Space ();

        logger.Info ("Welcome to Spreadware Loader :D");

        logger.Space (2);

        logger.Info ("| [~] Extracting segment to memory....");

        runtime.ExtractSegment();
        
        logger.Info ("| [~] Reconstructing hot-points...");

        runtime.ReconstructHotPoints();
        
        logger.Info ("| [+] Wait until the framework complete routine work...");
        logger.Info ("| [~] Filling the dependency table... (~7-15 sec)");

        segment.GetFramework().CreateDependencyTable ();

        logger.Info ("| [~] Updating netvars...");

        segment.GetFramework().UpdateNetVars();

        logger.Info ("| [~] Creating hook for internal function...");

        segment.GetFramework().CreateHook();

        logger.Info ("| [~] Installing spreadware...");

        //TODO: Waiting your beatiful name.
        //README: !!getenv it's a function!!. Please read docs before edit and ask questions.
        segment.GetFramework().UpdateWatermark ("crack user", "missed shot due to spread");
        segment.GetFramework().UpdateMenuWatermark ("spreadware");

        logger.Info ("| [~] Invoking OEP...");
       
        //Make segment alive.
        runtime.InvokeOEP();

        //Hide menu for better log look.
        segment.GetFramework().SetMenuStatus (false);

        logger.Info ("| [+] spreadware installed");

        logger.Space ();
       
        logger.Info ("+--------------------------------------------+");
        logger.Info ("| spreadware.dll                        -  × |");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("|                                            |");
        logger.Info ("| [onetap] missed shot due to spread         |");
        logger.Info ("| [onetap] missed shot due to spread         |");
        logger.Info ("| [onetap] missed shot due to spread         |");
        logger.Info ("|                                            |");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("                                              ");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("| credits.php                           -  × |");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("|                                            |");
        logger.Info ("| ascii text generator : http://patorjk.com/ |");
        logger.Info ("| src : https://github.com/0x000cb/otc       |");
        logger.Info ("| build by bun : https://discord.gg/KSydV4c  |");
        logger.Info ("|                                            |");
        logger.Info ("|--------------------------------------------|");


        logger.Space (2);

    }

    return TRUE;
}