#include <MainApplication.hpp>

// Implement all the layout/application functions here

Layout1::Layout1(){
    // Create the textblock with the text we want
    this->helloText = new pu::ui::elm::TextBlock(300, 300, "AISFLOW - PRACTICA!!! (pulsa X para continuar)");
    // Add the textblock to the layout's element container. IMPORTANT! this MUST be done, having them as members is not enough (just a simple way to keep them)
    this->Add(this->helloText);
}

MainApplication::MainApplication(){
    // Create the layout (calling the constructor above)
    this->layout1 = new Layout1();
    // Load the layout. In applications layouts are loaded, not added into a container (you don't select a added layout, just load it from this function)
    this->LoadLayout(this->layout1);
    // Set a function when input is caught. This input handling will be the first one to be handled (before Layout or any Elements)
    // Using a lambda function here to simplify things
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
