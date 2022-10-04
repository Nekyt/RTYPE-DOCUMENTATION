#ifndef _TEXT
#define _TEXT

#include "IComp.hpp"
#include <string>
#include <Text.hpp>
#include "../../Graphics/InitSfml.hpp"

namespace ECS {

    class Text : public IComp {
        public:
            explicit Text(std::string&, int, sf::Font&) noexcept;
            Text(const Text& text) noexcept;
            explicit Text(Text&&) noexcept = delete;
            ~Text() noexcept override = default;

            Text &operator=(const Text&) const noexcept = delete;
            Text &operator=(Text&&) const noexcept = delete;

            void setSentence(const std::string &text) noexcept;
            [[nodiscard]]std::string getSentence() const noexcept;
            void setSizeText(int) noexcept;
            [[nodiscard]]int getTextSize() const noexcept;
            [[nodiscard]]sf::Text &getText() noexcept;
            [[nodiscard]]sf::Font getFont() const noexcept;

        private:
            sf::Font _font;
            std::string _sentence;
            int _size;
            sf::Text _text;
    };

};

#endif