#include <settings/Settings.hpp>
//#include <fs/fs_Explorer.hpp>

extern settings::Settings psettings;

namespace settings{

    std::string GetString(unsigned int){
        return "ok";//MainDictionary.Strings[Index].get<std::string>();
    }

    std::string GetError(unsigned int){
        return "ko";//Errors.Strings[Index].get<std::string>();
    }

    std::string Settings::PathForResource(std::string Path){
        std::string outres = "romfs:" + Path;
        if(!this->Statics.empty())
        {
            std::string tmpres = this->Statics + "/" + Path;
            if(fs::IsFile(tmpres)) outres = tmpres;
        }
        return outres;
    }

    Settings ProcessSettings(){

    }

    bool Exists(){
        return fs::IsFile(SettingsFile);
    }

    void Initialize(){
        std::string pdict;
        switch(psettings.CustomLanguage){
            case Language::English:
                pdict = "en";
                break;
            case Language::Spanish:
                pdict = "es";
                break;
        }
        pdict += ".json";
        std::ifstream ifs(psettings.PathForResource("/Language/Strings/" + pdict));
        MainDictionary.DictLanguage = psettings.CustomLanguage;
        MainDictionary.Strings = JSON::parse(ifs);
        ifs.close();
        ifs.open(psettings.PathForResource("/Language/Errors/" + pdict));
        Errors.DictLanguage = psettings.CustomLanguage;
        Errors.Strings = JSON::parse(ifs);
        ifs.close();
    }


}
