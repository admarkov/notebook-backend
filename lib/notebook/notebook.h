#pragma once

#include "block.h"

#include <string>
#include <string_view>
#include <vector>

#include <json.hpp>

namespace NotebookBackend {

    using std::string;
    using std::string_view;
    using std::vector;
    using std::shared_ptr;
    using nlohmann::json;

    class Notebook {
    public:

        Notebook(string_view _id = "TODO: UUID4")
            : id_(_id)
            , name_("notebook")
        {

        }

        ~Notebook() = default;

        string id() const {
            return id_;
        }

        string name() const {
            return name_;
        }

        Notebook& setName(string_view n) {
            name_ = n;
            return *this;
        }

        json toJSON() const {
            json j;
            j["id"] = id_;
            j["name"] = name_;
            j["blocks"] = json::array();
            for (BlockPtr b: blocks_) {
                if (b->content()->type() != DELETED) {
                    j["blocks"].push_back(b->toJSON());
                }
            }
            return j;
        }

        string serialize() {
            return toJSON().dump();
        }

        void addBlock(BlockPtr b) {
            blocks_.push_back(b);
            blocks_.back()->setIdx(blocks_.size() - 1);
        }

        bool deleteBlock(int i) {
            if (i < 0 || i >= blocks_.size()) {
                return false;
            }
            if (blocks_[i]->content()->type() == DELETED) {
                return false;
            }
            blocks_[i]->deleteself();
            return true;
        }

    private:
        string id_;
        string name_;
        vector<BlockPtr> blocks_;
    };

}