#include "../include/text.hpp"

ECS::Text::Text(std::string &text) noexcept : _text(text) {}
ECS::Text::Text(const Text& text) noexcept : _text(text.getText()){}

std::string ECS::Text::getText() const noexcept {return _text;}
void ECS::Text::setText(const std::string &text) noexcept {_text = text;}