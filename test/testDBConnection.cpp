#include "../src/DB/DBConnection.h"
#include "../src/DB/QueryResult.h"

#include <iostream>

int main()
{
    DBConnection & dbCon = DBConnection::getInstance();
    QueryResult * result = 0;
    bool ok;
    
    result = dbCon.query("SELECT nombre, apellido from Persona;");
    while (result->next()) {
        std::cout << result->value(0).toString().toStdString() << " "
                  << result->value(1).toString().toStdString() << std::endl;
    }
    delete result;
    
    ok = dbCon.nonQuery("INSERT INTO Persona (nombre, apellido) VALUES "
                        "(\'Daniel\', \'Iturbide\');");
    std::cout << ok << std::endl;
    
    result = dbCon.query("SELECT nombre, apellido from Persona;");
    while (result->next()) {
        std::cout << result->value(0).toString().toStdString() << " "
                  << result->value(1).toString().toStdString() << std::endl;
    }
    delete result;
    
    ok = dbCon.nonQuery("DELETE FROM Persona where nombre=\'Daniel\' and "
                        "apellido=\'Iturbide\';");
    std::cout << ok << std::endl;
    
    return 0;
}
