#pragma once
#include <switch.h>
#include <types.hpp>

namespace settings{

    std::string GetString(unsigned int index);
    std::string GetError(unsigned int Index);

    struct WebBookmark{
        std::string Name;
        std::string URL;
    };

    struct Settings{
        Language CustomLanguage;
        std::string KeysPath;
        std::string Statics;
        ColorScheme CustomScheme;
        u32 MenuItemSize;
        bool IgnoreRequiredFirmwareVersion;
        std::vector<WebBookmark> Bookmarks;

        std::string PathForResource(std::string Path);

    };



    static const std::string SettingsFile = "sdmc:/" + Practicator + "/settings.json";

    Settings ProcessSettings();
    bool Exists();

    struct Dictionary{
        Language DictLanguage;
        JSON Strings;
    };

    static Dictionary MainDictionary;
    static Dictionary Errors;

    void Initialize();

}
