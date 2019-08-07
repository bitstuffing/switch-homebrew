#pragma once
#include <pu/Plutonium>

#include <json.hpp>

static const std::string Practicator = "switch/practicator";

using JSON = nlohmann::json; //library

struct ColorScheme{
    pu::ui::Color Background;
    pu::ui::Color Base;
    pu::ui::Color BaseFocus;
    pu::ui::Color Text;
};

enum class Language{
    English,
    Spanish,
};
