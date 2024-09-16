#include <iostream>
#include <vector>
#include <fstream>
#include "Record.h"
#include "B+TreeFile.h"

void create_file(const std::string& fileName) {
    std::vector<Record> listRecord;
    listRecord.push_back(Record{"G7L", "Ana Garcia", 9});
    listRecord.push_back(Record{"Z8R", "Juan Perez", 7});
    listRecord.push_back(Record{"1JQ", "Maria Lopez", 1});
    listRecord.push_back(Record{"H2K", "Luis Martinez", 3});
    std::ofstream file(fileName, std::ios::binary | std::ios::trunc);
    if (file.is_open()) {
        file.seekp(0, std::ios::beg);
        for(auto& record: listRecord)
            file.write(reinterpret_cast<const char*>(&record), sizeof(Record));
    }
    file.close();
}

void read_file(const std::string& fileName) {
    Record record{};
    std::ifstream file(fileName, std::ios::binary);
    if (file.is_open()) {
        file.seekg(0, std::ios::beg);
        while(file.peek() != EOF) {
            file.read((char*) &record, sizeof(Record));
            record.print_data();
        }
    }
    file.close();
}


int main() {
    create_file("test.dat");
    BPlusTreeFile file("test.dat");
    file.print();
    return 0;
}