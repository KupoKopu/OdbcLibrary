#ifndef ODBCFUNCTIONS
#define ODBCFUNCTIONS

#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

namespace odbc {
#define SQL_RETURN_CODE_LEN 1024

    RETCODE rc;

    void initialise(SQLHANDLE& hEnvironment, SQLHANDLE& hConnection);


    void connect(SQLHANDLE& hConnection, SQLWCHAR* conn);

    void rcCheck(RETCODE& retcode);

    void getDiagRec(SQLSMALLINT handleType, SQLHANDLE& hStatement, SQLSMALLINT record);

    void initiateStatement(SQLHANDLE& hConnection, SQLHANDLE& hStatement);

    void directExecute(SQLHANDLE& hStatement, SQLWCHAR* Statement);

    //TODO: need to look at how it gets data specifically
    void getColInfo(SQLHANDLE& hStatement, int colPos);

    void getColNumber(SQLHANDLE& hStatement);

    void prepareColContainer(SQLHANDLE& hStatement, SQLCHAR& container, int colPos, SQLSMALLINT sqlType, SQLINTEGER bufferLength);

    void prepareColContainer(SQLHANDLE& hStatement, SQLINTEGER* container, int colPos, SQLSMALLINT sqlType);

    void fetchCol(SQLHANDLE& hStatement);

    void  freeStatement(SQLHANDLE& hStatement);

    void  disconnect(SQLHANDLE& hConnection);

    void  freeConnection(SQLHANDLE& hConnection);

    void  freeEnv(SQLHANDLE& hEnvironment);
}

#endif // !ODBCFUNCTIONS



