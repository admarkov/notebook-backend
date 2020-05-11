#pragma once

#include "../block.h"

#include <string>

namespace NotebookBackend {

    using std::string;

    class TextContent: public IBlockContent {
    public:
        TextContent(string_view text = "Стандартный текст")
            : text_(text)
        {

        }

        ~TextContent() = default;

        TextContent& setText(string_view text) {
            text_ = text;
            return *this;
        }

        string text() const {
            return text_;
        }

        json toJSON() const override {
            json j;
            j["text"] = text_;
            return j;
        }

        EBlockType type() const override {
            return TEXT;
        }

    private:
        string text_;
    };

}