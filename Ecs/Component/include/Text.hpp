#ifndef _TEXT
#define _TEXT

#include "IComp.hpp"
#include <string>

namespace ECS {

    class Text : public IComp {
        public:
            explicit Text(std::string) noexcept;
            Text(const Text& text) noexcept;
            explicit Text(Text&&) noexcept = delete;
            ~Text() noexcept override = default;

            Text &operator=(const Text&) const noexcept = delete;
            Text &operator=(Text&&) const noexcept = delete;

            void setText(const std::string &text) noexcept;
            [[nodiscard]]std::string getText() const noexcept;

        private:
            std::string _text;
    };

};

#endif