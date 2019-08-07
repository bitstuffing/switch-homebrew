#include <settings/settings.hpp>

extern settings::Settings psettings;

namespace settings{

    std::string GetString(unsigned int index){
        return "ok";//MainDictionary.Strings[index].get<std::string>(); //TODO
    }

    std::string GetError(unsigned int index){
        return "ko";//Errors.Strings[index].get<std::string>(); //TODO
    }

    std::string Settings::PathForResource(std::string path){
        std::string outres = "romfs:" + path;
        //TODO
        return outres;
    }

    Settings ProcessSettings(){

    }

    bool Exists(){
        //TODO
        return true;
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
