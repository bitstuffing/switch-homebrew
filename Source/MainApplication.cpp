#include <MainApplication.hpp>
#include <settings/settings.hpp>
#include <cstdio>
#include <string>
#include <curl/curl.h>
#include <malloc.h>    // for mallinfo()

// Implement all the layout/application functions here

using namespace settings; //GetString

Layout1::Layout1(){

    try{

        this->console = new pu::ui::elm::TextBlock(0, 0, "(AISFLOW push X button)\tInstancing settings...");
        this->Add(this->console);

        //init settings
        Settings pSettings;

        this->optionMenu = new pu::ui::elm::Menu(0, 160, 1280,pu::ui::Color::FromHex("#EEEEEE") ,60,3);
        this->console = new pu::ui::elm::TextBlock(0, 30, "instancing menu item...");
        this->firstOption = new pu::ui::elm::MenuItem("hola, soy el primer elemento");
        this->Add(this->console);
        this->console = new pu::ui::elm::TextBlock(0, 60, "adding menu item to menu");
        this->optionMenu->AddItem(this->firstOption);

        char string[200];
        sprintf(string,"Memory: %d %d %d\n", mallinfo().arena, mallinfo().uordblks, mallinfo().fordblks);

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
