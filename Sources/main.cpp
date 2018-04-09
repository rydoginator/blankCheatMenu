#include "CTRPluginFramework.hpp"
#include "cheats.hpp"

// Will exit the plugin
void    abort(void);

namespace CTRPluginFramework
{
    union TitleID
    {
        u64  full;
        u32  half[2];
    };

    // This function is called before main
    void    PatchProcess(FwkSettings &settings)
    { 
        // This can be used to patch code.bin before the plugin is loaded to disable the home menu or other various patches that you want to create.
    }

    #define MAJOR_VERSION       3
    #define MINOR_VERSION       1
    #define REVISION_VERSION    0
    #define STRINGIFY(x)        #x
    #define TOSTRING(x)         STRINGIFY(x)
    #define STRING_VERSION      std::string("[" TOSTRING(MAJOR_VERSION) "." TOSTRING(MINOR_VERSION) "." TOSTRING(REVISION_VERSION) "]")


    void    InitMenu(PluginMenu &menu)
    {
        // Create your entries here, or elsewhere
        // You can create your entries whenever/wherever you feel like it
    }

    int     main(void)
    {
        extern  Region   g_region; ///< AutoRegion.cpp
        
        // Get current process title id
        TitleID tid = { Process::GetTitleID() };

        // Check lower half of the title id and if it's not one we want to support, abort the plugin
        if (tid.half[0] == 0x113100)
            g_region = EUR;
        else if (tid.half[0] == 0x113200)
            g_region = USA; // g_region can be used to set offset varaibles in order to have region free codes
        else
            OSD::Notify("Don't forget to add your own TID or else the plugin won't run!");
            abort();
        PluginMenu *menu = new PluginMenu("My plugin", MAJOR_VERSION, MINOR_VERSION, REVISION_VERSION, 
                                            "A little text to explain this plugin or show some credits... Or nothing useful like this text.");

        // Synnchronize the menu with frame event
        menu->SynchronizeWithFrame(true);

        // Init our menu entries & folders
        InitMenu(*menu);

        // Launch menu and mainloop
        menu->Run();

        // Exit plugin
        return (0);
    }
}
