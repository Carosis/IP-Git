#include "Database.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>

sqlite3* Database::dbConnection;
vector<vector<string>> Database::dbResults;
char* Database::errorMessage;

// Function to format a timestamp for SQLite insertion
std::string formatTimestamp(time_t timestamp) {
	std::stringstream ss;
	ss << timestamp;
	return ss.str();
}

// method to connect to the database and initialize tables in the database
void Database::initialize() {
	// open a database connection and store the pointer into dbConnection
	sqlite3_open("database.db", &dbConnection);

	// drop the existing users table (if any)
	string dropUsersTableSQL = "DROP TABLE IF EXISTS users";
	sqlite3_exec(dbConnection, dropUsersTableSQL.c_str(), NULL, 0, &errorMessage);

	// drop the existing passwords table (if any)
	string dropPassTableSQL = "DROP TABLE IF EXISTS passwords";
	sqlite3_exec(dbConnection, dropPassTableSQL.c_str(), NULL, 0, &errorMessage);
	
	// drop the existing requests table (if any)
	string dropRequestsTableSQL = "DROP TABLE IF EXISTS requests";
	sqlite3_exec(dbConnection, dropRequestsTableSQL.c_str(), NULL, 0, &errorMessage);

	// create a users table
	string createUsersTableSQL = "CREATE TABLE users ("
		"user_id INTEGER PRIMARY KEY, "
		"username VARCHAR(255), "
		"password VARCHAR(255), "
		"email VARCHAR(255), "
		"admin_role BOOLEAN, "
		"created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
		"password_expire TIMESTAMP, "
		"account_lock BOOLEAN, "
		"last_login TIMESTAMP);";
	sqlite3_exec(dbConnection, createUsersTableSQL.c_str(), NULL, 0, &errorMessage);

	// create a passwords table
	string createPassTableSQL = "CREATE TABLE passwords ("
		"password_id INTEGER PRIMARY KEY, "
		"user_id INTEGER, "
		"used_password VARCHAR(255), "
		"FOREIGN KEY (user_id) REFERENCES users(user_id));";

	sqlite3_exec(dbConnection, createPassTableSQL.c_str(), NULL, 0, &errorMessage);

	// create a requests table
	string createRequestsTableSQL = "CREATE TABLE requests ("
		"request_id INTEGER PRIMARY KEY, "
		"url VARCHAR(255), "
		"user_id INTEGER, "
		"raise_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
		"status VARCHAR(50), "
		"FOREIGN KEY (user_id) REFERENCES users(user_id));";

	sqlite3_exec(dbConnection, createRequestsTableSQL.c_str(), NULL, 0, &errorMessage);

	// initialize the result vector
	dbResults = vector<vector<string>>();

}

// method to close the database connection
void Database::close() {
	sqlite3_close(dbConnection);
}

// method to insert user into the database
void Database::insertUser(string username, string password, string email) {
	// Check if the database connection is valid
	if (!dbConnection) {
		cerr << "Database connection is invalid." << endl;
		return;
	}

	// Get the current timestamp
	time_t current_time = time(nullptr);

	// Calculate the timestamp for password expiration (3 months later)
	time_t password_expire_time = current_time + (3 * 30 * 24 * 60 * 60); // 3 months in seconds

	// Format the timestamps for SQLite insertion
	stringstream created_at_ss, password_expire_ss;
	created_at_ss << current_time;
	password_expire_ss << password_expire_time;


	// SQL query for inserting a new user with default values
	string insertUserSQL = "INSERT INTO users (username, password, email, admin_role, created_at, password_expire, account_lock, last_login) VALUES ("
		"'" + username + "', '" + password + "', '" + email + "', 0"
		+ ", " + created_at_ss.str() + ", '" + password_expire_ss.str() + "', 0, NULL);";

	// Execute the SQL query
	sqlite3_exec(dbConnection, insertUserSQL.c_str(), NULL, 0, &errorMessage);

	// Check for errors
	if (errorMessage) {
		cerr << "Error inserting user: " << errorMessage << endl;
		sqlite3_free(errorMessage);
	}
}
// method to insert used password into the database
void Database::insertPassword(int user_id, string used_password) {
	// Check if the database connection is valid
	if (!dbConnection) {
		cerr << "Database connection is invalid." << endl;
		return;
	}

	// Format the timestamp for SQLite insertion
	time_t current_time = time(nullptr);
	stringstream used_password_ss;
	used_password_ss << current_time;

	// = SQL query for inserting a new password
	string insertPasswordSQL = "INSERT INTO passwords (user_id, used_password) VALUES ("
		+ to_string(user_id) + ", '" + used_password + "');";

	// Execute the SQL query
	sqlite3_exec(dbConnection, insertPasswordSQL.c_str(), NULL, 0, &errorMessage);

	// Check for errors
	if (errorMessage) {
		cerr << "Error inserting password: " << errorMessage << endl;
		sqlite3_free(errorMessage);
	}
}
// method to overwrite the old password (Used when change password)
void Database::overwritePassword(int user_id, string used_password) {
	// Check if the database connection is valid
	if (!dbConnection) {
		cerr << "Database connection is invalid." << endl;
		return;
	}

	// Check the number of existing password records for the user
	string countPasswordSQL = "SELECT COUNT(*) FROM passwords WHERE user_id = " + to_string(user_id) + ";";
	int existingPasswordCount = 0;

	sqlite3_stmt* countStatement;
	if (sqlite3_prepare_v2(dbConnection, countPasswordSQL.c_str(), -1, &countStatement, 0) == SQLITE_OK) {
		if (sqlite3_step(countStatement) == SQLITE_ROW) {
			existingPasswordCount = sqlite3_column_int(countStatement, 0);
		}
		sqlite3_finalize(countStatement);
	}

	// If the user has 5 or more existing records, delete the oldest one
	if (existingPasswordCount >= 5) {
		string deleteOldestPasswordSQL = "DELETE FROM passwords WHERE user_id = " + to_string(user_id) +
			" ORDER BY password_id ASC LIMIT 1;";
		sqlite3_exec(dbConnection, deleteOldestPasswordSQL.c_str(), NULL, 0, &errorMessage);

		if (errorMessage) {
			cerr << "Error deleting oldest password record: " << errorMessage << endl;
			sqlite3_free(errorMessage);
			return;
		}
	}

	// Insert the new password
	insertPassword(user_id, used_password);
}
// method to insert requests into the database
void Database::insertRequest(string url, string username) {
	// Check if the database connection is valid
	if (!dbConnection) {
		cerr << "Database connection is invalid." << endl;
		return;
	}

	// Get the user_id associated with the provided username
	int userId = getUserIdByUsername(username);

	// Check if the username exists
	if (userId == -1) {
		cerr << "Username does not exist." << endl;
		return;
	}

	// SQL query for inserting a new request with default values
	string insertRequestSQL = "INSERT INTO requests (url, user_id, status) VALUES ('"
		+ url + "', " + to_string(userId) + ", 'Pending');";

	// Execute the SQL query
	sqlite3_exec(dbConnection, insertRequestSQL.c_str(), NULL, 0, &errorMessage);

	// Check for errors
	if (errorMessage) {
		cerr << "Error inserting request: " << errorMessage << endl;
		sqlite3_free(errorMessage);
	}
}




// get method
int Database::getUserIdByUsername(const string& username) {
	// Check if the database connection is valid
	if (!dbConnection) {
		cerr << "Database connection is invalid." << endl;
		return -1; // Return -1 to indicate an error
	}

	// Your SQL query for retrieving user_id based on the username
	string getUserIdSQL = "SELECT user_id FROM users WHERE username = '" + username + "';";

	// Execute the SQL query
	sqlite3_stmt* statement;
	int result = sqlite3_prepare_v2(dbConnection, getUserIdSQL.c_str(), -1, &statement, nullptr);

	if (result != SQLITE_OK) {
		cerr << "Error preparing SQL statement: " << sqlite3_errmsg(dbConnection) << endl;
		return -1; // Return -1 to indicate an error
	}

	// Execute the statement
	result = sqlite3_step(statement);

	if (result == SQLITE_ROW) {
		// Retrieve the user_id from the query result
		int userId = sqlite3_column_int(statement, 0);

		// Finalize the statement
		sqlite3_finalize(statement);

		return userId;
	}
	else {
		cerr << "Error executing SQL statement: " << sqlite3_errmsg(dbConnection) << endl;

		// Finalize the statement
		sqlite3_finalize(statement);

		return -1; // Return -1 to indicate an error
	}
}

// setter
void Database::changePassword(const string& username, const string& newPassword) {
	// Check if the database connection is valid
	if (!dbConnection) {
		cerr << "Database connection is invalid." << endl;
		return;
	}

	// Get the user_id associated with the provided username
	int userId = getUserIdByUsername(username);

	// Check if the username exists
	if (userId == -1) {
		cerr << "Username does not exist." << endl;
		return;
	}

	// Get the current timestamp
	time_t current_time = time(nullptr);

	// Calculate the timestamp for password expiration (3 months later)
	time_t password_expire_time = current_time + (3 * 30 * 24 * 60 * 60); // 3 months in seconds

	// Format the timestamps for SQLite insertion
	std::stringstream password_expire_ss;
	password_expire_ss << std::put_time(std::localtime(&password_expire_time), "%Y-%m-%d %H:%M:%S");

	// Update the password and password_expire in the 'users' table
	string updatePasswordSQL = "UPDATE users SET password = '" + newPassword + "', password_expire = '" + password_expire_ss.str() + "' WHERE user_id = " + to_string(userId) + ";";

	int result = sqlite3_exec(dbConnection, updatePasswordSQL.c_str(), NULL, 0, &errorMessage);

	// Check for errors
	if (result != SQLITE_OK) {
		cerr << "Error updating password: " << errorMessage << endl;
		sqlite3_free(errorMessage);
		return;
	}

	// Insert the old password into the 'passwords' table
	overwritePassword(userId, newPassword);
}




// callback method to put one row of results from the database into the dbResults vector
// This method is called each time a row of results is returned from the database
int Database::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	NotUsed = 0;
	vector<string> dbRow;

	// argc is the number of columns for this row of results
	// argv contains the values for the columns
	// Each value is pushed into a vector.
	for (int i = 0; i < argc; i++) {
		dbRow.push_back(argv[i]);
	}

	// The row is pushed to the vector for storing all rows of results 
	dbResults.push_back(dbRow);

	return 0;
}
