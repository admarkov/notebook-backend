#pragma once

#include <json.hpp>
#include <string>

namespace NotebookBackend {

    using nlohmann::json;
    using std::string;
    using std::shared_ptr;

    enum EBlockType {
        TEXT,
        CODE,
        DELETED
    };

    string EBlockTypeSerialization[] = {
            "TEXT",
            "CODE",
            "DELETED"
    };

    class IBlockContent {
    public:
        IBlockContent() = default;
        virtual ~IBlockContent() = default;

        virtual json toJSON() const = 0;
        virtual EBlockType type() const = 0;
    };

    class DeletedContent: public IBlockContent {
    public:
        DeletedContent() = default;

        ~DeletedContent() = default;

        json toJSON() const override {
            return "DELETED";
        }

        EBlockType type() const override {
            return DELETED;
        }
    };

    class Block {
    public:
        Block(IBlockContent*&& cont)
            : content_(cont)
        {

        }

        ~Block() = default;

        Block& setIdx(int i) {
            idx_ = i;
            return *this;
        }

        int idx() const {
            return idx_;
        }

        json toJSON() const {
            json j;
            j["idx"] = idx_;
            j["type"] = EBlockTypeSerialization[content_->type()];
            j["content"] = content_->toJSON();
            return j;
        }

        IBlockContent* content() const {
            return content_.get();
        }

        void deleteself() {
            content_.reset(new DeletedContent());
        }

    private:
        int idx_;
        std::unique_ptr<IBlockContent> content_;
    };
    using BlockPtr = shared_ptr<Block>;

}