#pragma once
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

public:
    void initialise()
    {
        if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnvironment))
        {
            std::cout << "ENV: Success\n";
        }
        if (SQL_SUCCESS == SQLSetEnvAttr(m_hEnvironment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        {
            std::cout << "ver: Success\n";
        }
        if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_DBC, m_hEnvironment, &m_hConnection))
        {
            std::cout << "Success\n";
        }


    }

    //params done
    void connect(SQLWCHAR* conn = (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=tcp:192.168.1.14, 1433;DATABASE=Customer Registry;UID=tester;PWD=tester123;")
    {
        switch (SQLDriverConnect(m_hConnection,
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

    void rcCheck()
    {
        switch (m_rc) {
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

    void initiateStatement()
    {
        m_rc = SQLAllocHandle(SQL_HANDLE_STMT, m_hConnection, &m_hStatement);
    }

    void directExecute(SQLWCHAR* Statement)
    {
        m_rc = SQLExecDirect(m_hStatement, Statement, SQL_NTS);
    }

    //params
    void  freeStatement()
    {
        SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement); // Disconnects statement, for further statements

    }

    //params
    void  disconnect()
    {
        SQLDisconnect(m_hConnection); // Disconnect from connected database

    }

    //params
    void  freeConnection()
    {
        SQLFreeHandle(SQL_HANDLE_DBC, m_hConnection); // Free driver from current connection string

    }

    //params
    void  freeEnv()
    {
        SQLFreeHandle(SQL_HANDLE_ENV, m_hEnvironment); // Don't remember


    }

    void bindParam(SQLUSMALLINT column, SQLCHAR* input, SQLUINTEGER input_size)
    {
        m_rc = SQLBindParameter(m_hStatement, column, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, input_size, 0, input, 0, nullptr);
    }

    //params
    void prepareColContainer(SQLCHAR& container, int colPos, SQLINTEGER bufferLength)
    {
        SQLBindCol(m_hStatement, colPos, SQL_CHAR, &container, bufferLength, nullptr);
    }

    void fetchCol()
    {
        SQLFetch(m_hStatement);
    }

    //params
    void prepareColContainer(SQLINTEGER* container, int colPos)
    {
        SQLBindCol(m_hStatement, colPos, SQL_INTEGER, container, sizeof(&container), nullptr);

    }

    OdbcController()
    {
        initialise();
    }
};