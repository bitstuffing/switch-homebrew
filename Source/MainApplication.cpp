#include <MainApplication.hpp>
#include <settings/settings.hpp>
#include <network/network.hpp>

#include <malloc.h>    // for mallinfo()
#include <cstdio> //sprintf
#include <string> //std::string

//using namespace settings; //GetString and pSettings
//using namespace network; //RetrieveContent

Layout1::Layout1(){

    try{

        //init settings
        settings::Settings pSettings;

        this->console = new pu::ui::elm::TextBlock(0, 0, "(AISFLOW push X button). Instancing settings...");
        this->Add(this->console);

        this->optionMenu = new pu::ui::elm::Menu(0, 160, 1280,pu::ui::Color::FromHex("#EEEEEE") ,60,3);
        this->console = new pu::ui::elm::TextBlock(0, 30, "instancing menu item...");

        std::string content = network::RetrieveContent("http://hora.roa.es:13/","application/json");

        this->firstOption = new pu::ui::elm::MenuItem(content);
        this->Add(this->console);
        this->console = new pu::ui::elm::TextBlock(0, 60, settings::GetString(1));
        this->optionMenu->AddItem(this->firstOption);

        char string[200];
        sprintf(string,"Memory: %d %d %d", mallinfo().arena, mallinfo().uordblks, mallinfo().fordblks);

        this->secondOption = new pu::ui::elm::MenuItem(string);

        this->optionMenu->AddItem(this->secondOption);
        this->Add(this->console);

        this->Add(this->optionMenu);

    }catch(std::exception& e){
      this->console = new pu::ui::elm::TextBlock(300, 300, e.what());
      this->Add(this->console);
    }

}

MainApplication::MainApplication(){
    this->layout1 = new Layout1();

    this->LoadLayout(this->layout1);

    this->SetOnInput([&](u64 Down, u64 Up, u64 Held, bool Touch){
        if(Down & KEY_X){ // If X is pressed, start with our dialog questions!
            int opt = this->CreateShowDialog("Pregunta", "¿Has practicado?", { "¡Sí!", "No...", "Cancelar" }, true); // (using latest option as cancel option)
            if((opt == -1) || (opt == -2)){ // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
                this->CreateShowDialog("Cancelar", "La pregunta fue cancelada", { "Ok" }, true);
            }else{
                switch(opt){
                    case 0: // "Yes" was selected
                        this->CreateShowDialog("Respuesta", "¿De verdad? ¡Yo también practico!", { "Ok" }, true);
                        break;
                    case 1: // "No" was selected
                        this->CreateShowDialog("Respuesta", "Ah... Así que no lo has hecho...", { "(mierda, me has pillado)" }, true);
                        break;
                }
            }
        }
    });
}
