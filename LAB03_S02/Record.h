#ifndef LAB_RECORD_H
#define LAB_RECORD_H

#include <iostream>
#include <string>
#include <cstring>
#include <utility>

struct Record {
    char code[4];
    char name[20];
    short cycle;

    void print_data() {
        std::cout << "\nDatos del Registro:";
        std::cout << "\n  - Codigo: " << code;
        std::cout << "\n  - Nombre: " << name;
        std::cout << "\n  - Ciclo:  " << cycle;
        std::cout << '\n';
    }

    bool operator == (const Record& other) const {
        bool result = (strcmp(this->code, other.code) == 0);
        result = result && (strcmp(this->name, other.name) == 0);
        result = result && (this->cycle == other.cycle);
        return result;
    }

    Record& operator=(const Record& other) {
        if (this == &other)
            return *this;
        strcpy(this->code, other.code);
        strcpy(this->name, other.name);
        this->cycle = other.cycle;
        return *this;
    }
};

#endif //LAB_RECORD_H
