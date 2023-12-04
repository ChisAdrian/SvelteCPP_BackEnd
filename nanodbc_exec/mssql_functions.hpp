#ifndef MSSQL_FUNCTIONS_HPP_INCLUDED
#define MSSQL_FUNCTIONS_HPP_INCLUDED


/**
 * Executes a SELECT query on an MSSQL database and returns the result as a string.
 *
 * @param queryText The SELECT query to be executed.
 * @param conn The ODBC connection string to the MSSQL database.
 * @return The result of the SELECT query as a string.
 *
 * This function takes a SELECT query and an ODBC connection string to an MSSQL database.
 * It executes the query using the nanodbc library and retrieves the result.
 * The result is then concatenated into a string and returned.
 * If any exceptions occur during the execution, the function catches them and returns the exception message.
 */
std::string mssql_select(std::string queryText, std::string conn)
{
    std::string msg = "";
    try
    {
        auto const connstr = NANODBC_TEXT(conn); // an ODBC connection string to your database
        nanodbc::connection conn(connstr);

        auto result = nanodbc::execute(conn, NANODBC_TEXT(queryText));
        while (result.next())
        {
            msg += result.get<std::string>(0, "null");
        }
        return msg;
    }
    catch (std::exception& e)
    {
        return e.what();
    }
}



/**
 * Execute a SELECT query on an MSSQL database and return the results as a vector of vectors of strings.
 *
 * The function takes the following parameters:
 * - SEL_STR: The SELECT query string.
 * - CONN_STR: The connection string to the MSSQL database.
 * - col_header: A boolean flag indicating whether to include column headers in the result.
 *
 * The function performs the following steps:
 * - Creates a nanodbc connection to the MSSQL database using the provided connection string.
 * - Prepares and executes the SELECT query using a nanodbc statement.
 * - Retrieves the number of columns in the result set.
 * - If col_header is true, it retrieves the column names and adds them as the first row in the result vector.
 * - Iterates over the result set and retrieves the values for each column in each row.
 * - Adds each row as a vector of strings to the result vector.
 * - If any exception occurs during the execution of the query, it catches the exception, adds the error message to the error vector, and returns the error vector.
 * - If no exception occurs, it returns the result vector.
 *
 * The result vector is a vector of vectors of strings, where each inner vector represents a row in the result set, and each string represents a value in a column.
 *
 * Note: This function uses the nanodbc library for interacting with the MSSQL database.
 *
 * You can use the returned result vector to process and manipulate the query results as per your requirements.
 */
std::vector<std::vector<std::string>> mssql_select_vector(std::string SEL_STR, std::string CONN_STR, bool col_header)
{
    std::vector<std::vector<std::string>> ret_ok;
    std::vector<std::vector<std::string>> errors_Catch;
    std::vector<std::string> errors_Catch_row;
    try
    {
        nanodbc::result results;
        nanodbc::connection connection(CONN_STR);
        nanodbc::statement statement(connection);
        prepare(statement, SEL_STR);
        results = execute(statement);
        int columns = results.columns();

        if (col_header == true)
        {
            std::vector<std::string> header_Vector;
            for (short col = 0; col < columns; ++col)
                header_Vector.push_back(results.column_name(col));

            ret_ok.push_back(header_Vector);
        }

        while (results.next())
        {
            std::vector<std::string> rowVector;
            for (short col = 0; col < columns; ++col)
                rowVector.push_back(results.get<std::string>(col, "null"));

            ret_ok.push_back(rowVector);
        }
    }
    catch (const std::exception &e)
    {
        std::string for_errors_Catch = e.what();
        errors_Catch_row.push_back(for_errors_Catch);
        errors_Catch.push_back(errors_Catch_row);

        return errors_Catch;
    }

    return ret_ok;
}



#endif // MSSQL_FUNCTIONS_HPP_INCLUDED
