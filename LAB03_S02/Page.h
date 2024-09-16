#ifndef LAB_PAGE_H
#define LAB_PAGE_H

#include <string>
#include <cstring>
#include <iostream>

const short fb = 3;

class Page {
    protected:
        char arrayKey[fb][4] {};
        short size;
    public:
        Page() = default;
        virtual ~Page() = 0;
        virtual bool isLeaf() = 0;
        virtual Page* find(char key[4]) = 0;
};
Page::~Page() = default;

class PageInternal : public Page {
    private:
        Page* arrayNode[fb+1] {};
    public:
        PageInternal() {
            std::fill(std::begin(arrayNode), std::end(arrayNode), nullptr);
        };
        ~PageInternal() override = default;

        bool insert(char key[4], Page* first, Page* second) {
            if (size < fb) {
                for (short index = 0; index < size; index++) {
                    if (std::strncmp(&key[0], &arrayKey[index][0], 4) < 0) {
                        for(int c=0; c<4; c++)
                            std::swap(arrayKey[index][c], key[c]);
                        std::swap(arrayNode[index],first);
                        std::swap(first, second);
                        first = second;
                    }
                }
                std::strncpy(arrayKey[size], key, 4);
                arrayPosFile[size] = posFile;
                size++;
                return true;
            }
            return false;
        };

        bool isLeaf() override {return false;};

        Page* find(char key[4]) override {
            for(short index = 0; index < size; index++)
                if (key < arrayKey[index]) return arrayNode[index];
            return arrayNode[size];
        };
};

class PageLeaf : public Page {
    private:
        int arrayPosFile[fb] {};
    public:
        PageLeaf* next;

        PageLeaf(): next(nullptr) {
            size = 0;
            std::fill(std::begin(arrayPosFile), std::end(arrayPosFile), -1);
        };

        ~PageLeaf() override = default;

        bool insert(char key[4], int &posFile) {
            if (size < fb) {
                for (short index = 0; index < size; index++) {
                    if (std::strncmp(&key[0], &arrayKey[index][0], 4) < 0) {
                        for(int c=0; c<4; c++)
                            std::swap(arrayKey[index][c], key[c]);
                        std::swap(arrayPosFile[index],posFile);
                    }
                }
                std::strncpy(arrayKey[size], key, 4);
                arrayPosFile[size] = posFile;
                size++;
                return true;
            }
            return false;
        };

        bool isLeaf() override {return true;};

        Page* find(char key[4]) override { return nullptr; };

        void printKeys() {
            std::cout << "\nImprimiendo datos de la pagina: ";
            for(short index = 0; index < size; index++)
                std::cout << "\n - " << arrayKey[index] << " - " << arrayPosFile[index];
        }
};

#endif //LAB_PAGE_H
