/*! \file auth.cpp
    \brief Implementation for user authentiation with email and password.
*/
#include "auth.h"
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "resthandler.h"

using namespace std;

/*! \brief Constructor
	\param[in]  rest pointer to a IRESTHandler
*/
Auth::Auth(IRESTHandler *rest)
: rest(rest) 
{}

/*! \brief Method to sign in user.
	\param[in]  cfg a FirebaseConfig containing credentials.
	\param[out] authToken This variable is set.
	\returns 0 on success and 1 otherwise.
*/
uint8_t Auth::signInWithEmailAndPassword(const FirebaseConfig cfg, char *authToken) {
  string tmp = "curl https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key="+string(cfg.apiKey)+" -H 'Content-Type: application/json' --data-binary '{\"email\":\""+string(cfg.email)+"\",\"password\":\""+string(cfg.password)+"\",\"returnSecureToken\":true}'";
 
  const char* signInCommand = tmp.c_str();
  char msg[2048];

  rest->executeRequest(signInCommand, msg);

  cJSON *root = cJSON_Parse(msg);

  cJSON *dbReply =  cJSON_GetObjectItemCaseSensitive(root, "idToken");

  if (dbReply == NULL) {
    return 1;
  }

  printf("Firebase auth key:\n %s\n\n", dbReply->valuestring);

  char *reply = cJSON_Print(dbReply);

  // Copy auth token into return variable. Disregard the leading and trailing quotes
  // and null-terminate the string
  memcpy(authToken, &reply[1], AUTHTOKEN_LENGTH);
  authToken[AUTHTOKEN_LENGTH] = '\0';

  // Clean up
  delete  reply;
  cJSON_Delete(root);

  return 0;
}
