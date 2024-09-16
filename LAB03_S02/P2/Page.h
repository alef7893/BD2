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
        virtual Page* nextPage(char key[4]) = 0;
        virtual int search(char key[4]) = 0;
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

        bool isLeaf() override {return false;};

        Page* nextPage(char key[4]) override {
            for(short index = 0; index < size; index++)
                if (key < arrayKey[index]) return arrayNode[index];
            return arrayNode[size];
        };

        int search(char key[4]) override {return -1;};
};

class PageLeaf : public Page {
    private:
        int arrayPosFile[fb];
    public:
        PageLeaf* next;

        PageLeaf(int posFile): next(nullptr) { size = 0; };

        ~PageLeaf() override = default;

        bool isLeaf() override {return true;};

        Page* nextPage(char key[4]) override { return nullptr; };

        int search(char key[4]) override {
            for(short index = 0; index < size; index++)
                if (std::strncmp(&key[0], &arrayKey[index][0], 4) == 0) return arrayPosFile[index];
            return -1;
        };
};

/*
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
 * */

#endif //LAB_PAGE_H
