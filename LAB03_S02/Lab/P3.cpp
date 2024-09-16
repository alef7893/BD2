
/*
Recordemos que clustered significa que el índice mantiene el mismo orden que los archivos físicos. En este caso buscar cuesta 'X' bloques dónde X es la altura del árbol (tenemos que ir hasta un nodo hoja para obtener el bloque de tuplas que queremos) y luego, dependiendo el tipo de búsqueda, si es clave candidata o no etc la cantidad de tuplas que hay matchean nuestra búsqueda.
*/

// Función para buscar un rango de claves en el índice B+ Tree
void BPlusTree::RangeSearch(const std::string& key1, const std::string& key2, std::ostream& outputFile) {
    // Verificar si el árbol está vacío
    if (root == nullptr) {
        outputFile << "Null" << std::endl;
        return;
    }

    // Paso 1: Encontrar el nodo hoja que contiene o es mayor o igual a key1
    Node* leafNode = FindLeafNodeFromDisk(key1);
    if (leafNode == nullptr) {
        outputFile << "Null" << std::endl;
        return;
    }

    // Variable para verificar si al menos una clave ha sido encontrada en el rango
    bool firstKeyFound = false;

    // Mientras haya nodos hoja para procesar
    while (leafNode != nullptr) {
        // Leer el nodo hoja desde el disco
        ReadNodeFromDisk(leafNode);

        // Obtener las claves y valores del nodo
        std::vector<std::string> keys = leafNode->GetKeys();
        std::vector<std::vector<std::string>> values = leafNode->GetValues();

        // Iterar sobre todas las claves en el nodo
        for (size_t i = 0; i < keys.size(); ++i) {
            // Si la clave actual es mayor que key2, hemos terminado
            if (keys[i] > key2) {
                if (firstKeyFound) {
                    outputFile << std::endl;
                }
                return;
            }

            // Si la clave está dentro del rango [key1, key2]
            if (keys[i] >= key1 && keys[i] <= key2) {
                // Si no es la primera clave encontrada, agregar una coma
                if (firstKeyFound) {
                    outputFile << ",";
                } else {
                    // Marcar que hemos encontrado la primera clave
                    firstKeyFound = true;
                }

                // Escribir los valores asociados con la clave
                for (size_t j = 0; j < values[i].size(); ++j) {
                    outputFile << "(" << keys[i] << "," << values[i][j] << ")";
                    if (j < values[i].size() - 1) {
                        outputFile << ",";
                    }
                }
            }
        }

        // Mover al siguiente nodo hoja
        leafNode = leafNode->GetNext();
    }

    // Si no se encontró ninguna clave en el rango, escribir "Null"
    if (!firstKeyFound) {
        outputFile << "Null" << std::endl;
    }
}

// Función para encontrar el nodo hoja desde el disco dado una clave
Node* BPlusTree::FindLeafNodeFromDisk(const std::string& key) {
    // Implementación para localizar y leer el nodo hoja desde el disco
    // ...
}

// Función para leer un nodo específico desde el disco
void BPlusTree::ReadNodeFromDisk(Node* node) {
    // Implementación para leer el nodo desde el disco
    // ...
}
