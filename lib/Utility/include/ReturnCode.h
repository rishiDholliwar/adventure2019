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

//when main works, maybe try changing this to enum class ReturnCode : bool?