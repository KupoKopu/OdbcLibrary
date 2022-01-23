#ifndef ODBCCONTROLLER
#define ODBCCONTROLLER

#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

class OdbcController
{
private:
    RETCODE m_rc{};
    SQLHANDLE m_hEnvironment{};
    SQLHANDLE m_hConnection{};
    SQLHSTMT m_hStatement{};
    // Should Handles be pointers or not

#define SQL_RETURN_CODE_LEN 1024
    SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

    void initialise(SQLHANDLE& hEnvironment, SQLHANDLE& hConnection)
    {
        if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnvironment))
        {
            std::cout << "Success\n";
        }
        if (SQL_SUCCESS == SQLSetEnvAttr(hEnvironment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        {
            std::cout << "Success\n";
        }
        if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_DBC, hEnvironment, &hConnection))
        {
            std::cout << "Success\n";
        }


    }

public:
    OdbcController()
    {
        initialise(m_hEnvironment, m_hConnection);
    }

    void connect(SQLHANDLE& hConnection, SQLWCHAR* conn)
    {
        switch (SQLDriverConnect(hConnection,
            NULL,
            conn,
            SQL_NTS,
            retconstring,
            SQL_RETURN_CODE_LEN,
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

    void initiateStatement(SQLHANDLE& hConnection, SQLHANDLE& hStatement)
    {
        m_rc = SQLAllocHandle(SQL_HANDLE_STMT, hConnection, &hStatement);
    }

    void directExecute(SQLHANDLE& hStatement, SQLWCHAR* Statement)
    {
        m_rc = SQLExecDirect(hStatement, Statement, SQL_NTS);
    }

    void  freeStatement(SQLHANDLE& hStatement)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, hStatement); // Disconnects statement, for further statements

    }

    void  disconnect(SQLHANDLE& hConnection)
    {
        SQLDisconnect(hConnection); // Disconnect from connected database

    }

    void  freeConnection(SQLHANDLE& hConnection)
    {
        SQLFreeHandle(SQL_HANDLE_DBC, hConnection); // Free driver from current connection string

    }

    void  freeEnv(SQLHANDLE& hEnvironment)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnvironment); // Don't remember


    }

    void bindParam(SQLUSMALLINT column, SQLCHAR* input, SQLUINTEGER input_size)
    {
        m_rc = SQLBindParameter(m_hStatement, column, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, input_size, 0, input, 0, nullptr);
    }
};


#endif // !ODBCCONTROLLER