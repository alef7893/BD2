#ifndef LAB_B_TREEFILE_H
#define LAB_B_TREEFILE_H

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <stack>
#include "Record.h"
#include "Page.h"

class BPlusTreeFile {
    private:
        std::string fileName;
        Page* root;
        PageLeaf* first;
    public:
        explicit BPlusTreeFile(std::string f): fileName(std::move(f)), root(nullptr), first(nullptr) {
            std::ifstream file(fileName, std::ios::binary);
            if (file.is_open()) {
                int posFile = -1;
                Record record{};
                file.seekg(0, std::ios::beg);
                while(file.peek() != EOF) {
                    posFile++;
                    file.read((char*) &record, sizeof(Record));
                    this->insert(posFile, record);
                    print();
                }
            }
            file.close();
        };

        void insert(int& posFile, Record& record) {
            if (root != nullptr) {
                std::stack<Page*> father;
                Page* node = root;
                while (!node->isLeaf()) {
                    father.push(node);
                    node = node->find(record.code);
                }

                if (!node->insert(record.code, posFile)) {
                    Page* nodeFather = nullptr;
                    Page* nodeFather = (!father.empty()) ? father.top() : nullptr;
                    father
                    std::cout << "\nContenedor desbordado, se requiere subir un nuevo nivel.";
                }
            } else {
                first = new PageLeaf;
                first->insert(record.code, posFile);
                root = first;
            }
        };

        void print() {
            PageLeaf* leaf = first;
            while(leaf != nullptr) {
                leaf->printKeys();
                leaf = leaf->next;
            }
        };
};

#endif //LAB_B_TREEFILE_H
