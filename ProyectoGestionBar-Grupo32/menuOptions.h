#include <iostream>

enum class OPC{
    OPCION_NULL = 0,
    OPCION1 = 1,
    OPCION2 = 2,
    OPCION3 = 3,
    OPCION4 = 4,
    OPCION5 = 5,
    OPCION6 = 6,
    OPCION7 = 7,
    OPCION8 = 8
};

class MenuOption{
public:
    static void siguienteOpcion(OPC& opcion){
        int opcionActual, nuevaOpcion;

        opcionActual = static_cast<int>(opcion);
        if(opcionActual < 8) {
            nuevaOpcion = opcionActual + 1;
            opcion = static_cast<OPC>(nuevaOpcion);
        }
    }

    static void anteriorOpcion(OPC& opcion){
        int opcionActual, nuevaOpcion;

        opcionActual = static_cast<int>(opcion);
        if(opcionActual > 1) {
            nuevaOpcion = opcionActual - 1;
            opcion = static_cast<OPC>(nuevaOpcion);
        }
    }
};

