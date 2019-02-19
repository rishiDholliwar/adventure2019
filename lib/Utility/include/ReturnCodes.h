#ifndef ALTERSPACE_RETURNCODES_H
#define ALTERSPACE_RETURNCODES_H

enum class ReturnCode {

    USER_ACTIVE,      // User is currently logged in
    LOGIN_SUCCESS,    // User login authenticated
    LOGOUT_SUCCESS,   // User logout success
    LOGOUT_FAIL,      // User attempting logout is not active
    SAVE_SUCCESS,     // Succesfully saved character data before logout
    SAVE_FAIL,        // Unable to save character data
    PASSWORD_FAIL,    // Password incorrect (does not match username)
    USERNAME_EXISTS,  // Cannot create a user with this username; username taken
    USERNAME_FAIL,    // Account (Username.json) does not exist for this username
    CREATE_SUCCESS,   // User creation was success
};

namespace Return
{

    static const std::unordered_map<ReturnCode, std::string>
    ReturnCodeResponses = {
        { ReturnCode::USER_ACTIVE,    "User is active" },
        { ReturnCode::LOGIN_SUCCESS,  "Logged in succesfully" },
        { ReturnCode::LOGOUT_SUCCESS, "Logged out succesfully" },
        { ReturnCode::LOGOUT_FAIL,    "Failed to logout" },
        { ReturnCode::SAVE_SUCCESS,   "Saved succesfully" },
        { ReturnCode::SAVE_FAIL,      "Failed to save" },
        { ReturnCode::PASSWORD_FAIL,  "Incorrect password" },
        { ReturnCode::USERNAME_EXISTS, "Username already taken" },
        { ReturnCode::USERNAME_FAIL,  "Username does not exist" },
        { ReturnCode::CREATE_SUCCESS, "Succesfully created character"}
    };

    inline std::string ReturnCodeToString( ReturnCode rc )
    {
        if( ReturnCodeResponses.find(rc) == ReturnCodeResponses.end() )
        {
            return "Unknown response";
        }
        return ReturnCodeResponses.at(rc);
    }
}

#endif //ALTERSPACE_RETURNCODES_H
