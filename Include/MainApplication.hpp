#pragma once
#include <pu/Plutonium>

//layout to be included in MainApplication
class Layout1 : public pu::ui::Layout{
    public:
        Layout1();
    private:
        // An easy way to keep objects is to have them as private pointer members
        pu::ui::elm::TextBlock *console;
        pu::ui::elm::Menu *optionMenu;
        pu::ui::elm::MenuItem *firstOption;
        pu::ui::elm::MenuItem *secondOption;
};

//application class definition
class MainApplication : public pu::ui::Application{
    public:
        MainApplication();
    private:
        // Layout instance
        Layout1 *layout1;
};
