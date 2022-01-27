#include "OdbcEasyLibrary.h"




namespace odbc {

    //params done
    void initialise(SQLHANDLE& hEnvironment, SQLHANDLE& hConnection)
    {
        if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnvironment))
        {
            std::cout << "yes\n";
        }
        if (SQL_SUCCESS == SQLSetEnvAttr(hEnvironment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        {
            std::cout << "yes\n";
        }
        if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_DBC, hEnvironment, &hConnection))
        {
            std::cout << "yes\n";
        }


    }



    SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
    //params done
    void connect(SQLHANDLE& hConnection, SQLWCHAR* conn)
    {
        switch (SQLDriverConnect(hConnection,
            NULL,
            conn,
            SQL_NTS,
            retconstring,
            1024,
            NULL,
            SQL_DRIVER_NOPROMPT))
        {
        case SQL_SUCCESS:
            std::cout << "Successfully connected to SQL Server(1)";
            std::cout << "\n";
            break;
        case SQL_SUCCESS_WITH_INFO:
            std::cout << "Successfully connected to SQL Server(2)";
            std::cout << "\n";
            break;
        case SQL_INVALID_HANDLE:
            std::cout << "Could not connect to SQL Server(1)";
            std::cout << "\n";
            break;
        case SQL_ERROR:
            std::cout << "Could not connect to SQL Server(2)";
            std::cout << "\n";
            break;
        case SQL_NO_DATA:
            std::cout << "No data";
            std::cout << "\n";
            break;
        case SQL_STILL_EXECUTING:
            std::cout << "Still connecting";
            std::cout << "\n";
            break;
        default:
            break;
        }

    }




    //params done
    void rcCheck(RETCODE& retcode)
    {
        switch (retcode) {
        case SQL_SUCCESS:
            std::cout << "SQL_SUCCESS(1)";
            std::cout << "\n";
            break;
        case SQL_SUCCESS_WITH_INFO:
            std::cout << "SQL_SUCCESS_WITH_INFO(2)";
            std::cout << "\n";
            break;
        case SQL_INVALID_HANDLE:
            std::cout << "SQL_INVALID_HANDLE(1)";
            std::cout << "\n";
            break;
        case SQL_ERROR:
            std::cout << "SQL_ERROR(2)";
            std::cout << "\n";
            break;
        default:
            std::cout << "default";
            std::cout << "\n";
            break;
            break;
        }
    }



    //params done
    void getDiagRec(SQLSMALLINT handleType, SQLHANDLE& hStatement, SQLSMALLINT record)
    {
        SQLWCHAR diagn[6]{};
        SQLINTEGER* nativ{};
        SQLWCHAR msg[255]{};
        SQLSMALLINT* length{};

        rc = SQLGetDiagRec(/*SQL_HANDLE_STMT*/handleType, hStatement, /*1*/record, diagn, nativ, msg, 255, length);

        std::wcout << diagn << "\n";
        std::wcout << msg << "\n";
    }



    //params done
    void initiateStatement(SQLHANDLE& hConnection, SQLHANDLE& hStatement)
    {
        rc = SQLAllocHandle(SQL_HANDLE_STMT, hConnection, &hStatement);
    }



    //params done
    void directExecute(SQLHANDLE& hStatement, SQLWCHAR* Statement)
    {
        rc = SQLExecDirect(hStatement, Statement, SQL_NTS);
    }



    //SQLINTEGER cbValue = SQL_NTS;
    //SQLINTEGER cbValue2 = SQL_NTS;
    //SQLINTEGER cbValue3 = SQL_NTS;
    //SQLINTEGER cbValue4 = SQL_NTS;
    //void prepareParam()
    //{
    //    SQLCHAR* fName = (SQLCHAR*)"kaoof";
    //    SQLCHAR* lName = (SQLCHAR*)"koof";
    //    SQLCHAR* email = (SQLCHAR*)"lukefo.com";
    //    SQLCHAR* phone = (SQLCHAR*)"101010";
    //
    //    rc = SQLBindParameter(hStatement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 30, 0, fName, 0, &cbValue);
    //    rc = SQLBindParameter(hStatement, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 30, 0, lName, 0, &cbValue2);
    //    rc = SQLBindParameter(hStatement, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, email, 0, &cbValue3);
    //    rc = SQLBindParameter(hStatement, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, phone, 0, &cbValue4);
    //}



    //params
    // not needed
    //void bindParameter(int column, SQLSMALLINT input, SQLSMALLINT cType, SQLSMALLINT sqlType, SQLPOINTER* container, SQLINTEGER pcbValue)
    //{
    //
    //    rc = SQLBindParameter(hsta, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 30, 0, &container, 0, &pcbValue);
    //}



    //params
    //TODO: need to look at how it gets data specifically
    void getColInfo(SQLHANDLE& hStatement, int colPos)
    {
        //// (OPTIONAL) Find col details, name and type, used if not known internally (like if making independent code).
    // Establish variables
        SQLWCHAR colName[20]{};
        SQLWCHAR* colNameptr{ colName };
        //Buffer length
        SQLSMALLINT nameLengthBuffer{ 20 };
        SQLSMALLINT dataType{}; // "enum style".
        SQLULEN dataSize{}; // size like char[5].
        SQLSMALLINT decimalDigits{}; // Floating value related, how many digits past the decimal.
        SQLSMALLINT isNull{}; // if col can have null.
        SQLDescribeCol(hStatement, colPos, colName, 20, &nameLengthBuffer, &dataType, &dataSize, &decimalDigits, &isNull);

        //TODO: sqlchar* wouldn't work with sqlwchar because its 16bit and so the next address is terminating symbol /0
        std::wcout << "|name: " << colName << " |namelen: " << nameLengthBuffer << " |datatype: " << dataType << " |datasize: " << dataSize << " |decimal digits: " << decimalDigits << " |isnull: " << isNull << '\n';
    }



    //params
    void getColNumber(SQLHANDLE& hStatement)
    {
        SQLSMALLINT result{ 5 };
        //SQLSMALLINT* resultptr{&result};
        SQLNumResultCols(hStatement, &result);
        std::wcout << "col: " << result << '\n';
    }



    //params
    void prepareColContainer(SQLHANDLE& hStatement, SQLCHAR& container, int colPos, SQLSMALLINT sqlType, SQLINTEGER bufferLength)
    {
        SQLBindCol(hStatement, colPos, sqlType, &container, bufferLength, nullptr);
    }



    //params
    void prepareColContainer(SQLHANDLE& hStatement, SQLINTEGER* container, int colPos, SQLSMALLINT sqlType)
    {
        SQLBindCol(hStatement, colPos, sqlType, container, sizeof(&container), nullptr);

    }



    //params
    void fetchCol(SQLHANDLE& hStatement)
    {
        SQLFetch(hStatement);
    }



    //params
    void  freeStatement(SQLHANDLE& hStatement)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, hStatement); // Disconnects statement, for further statements

    }



    //params
    void  disconnect(SQLHANDLE& hConnection)
    {
        SQLDisconnect(hConnection); // Disconnect from connected database

    }



    //params
    void  freeConnection(SQLHANDLE& hConnection)
    {
        SQLFreeHandle(SQL_HANDLE_DBC, hConnection); // Free driver from current connection string

    }



    //params
    void  freeEnv(SQLHANDLE& hEnvironment)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnvironment); // Don't remember

    }
}