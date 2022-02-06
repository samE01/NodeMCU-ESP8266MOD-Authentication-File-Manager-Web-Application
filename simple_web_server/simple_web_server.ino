//Class: CY320-740
//Team FrostByte
//Author: Samuel Elfrink
//Date: 10/14/2021
//Purpose: Webserver that host file managment webpages

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <LittleFS.h>

ESP8266WebServer server;

char* ssid = "********"; //Enter the SSID of YOUR CURRENT CONNECTED WIFI
char* password = "**********";//Enter the PASSWORD that you use to connect to YOUR CURRENT CONNECTED WIFI

static const char TEXT_PLAIN[] PROGMEM = "text/plain";
static const char FS_INIT_ERROR[] PROGMEM = "FS INIT ERROR";
static const char FILE_NOT_FOUND[] PROGMEM = "FileNotFound";

//basic html for Login Failed Error
const char MAIN_page[] PROGMEM = R"=====(
      <html>
        <head>
          <title>Login Failed</title>
        </head>
        <body>
          <p>Login credential invalid, please return to the home page and try again</p>
          <form method="get" action="index.php">
            <button type="submit">Home Page</button>
          </form>
        </body>
      </html>
    )=====";

//basic html for registration Failed Error
const char MAINS_page[] PROGMEM = R"=====(
      <html>
        <head>
          <title>Registration Failed</title>
        </head>
        <body>
          <p>Registration username credential already used, please return to the home page and try again</p>
          <form method="get" action="index.php">
            <button type="submit">Home Page</button>
          </form>
        </body>
      </html>
    )=====";

//setup the server for listening
void setup()
{
  LittleFS.begin();
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);  
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());

  //server authentication
  server.on("/", serveIndexFile);
  server.on("/index.php", handleIndex);
  server.on("/registration.php", handleRegistration);
  server.on("/login.php", handleLogin);
  server.on("/welcome.php", handleWelcomePage);
  server.on("/handleWelcome", handleWelcome);
  server.on("/handleRegistration", handleRegistrationForm);
  server.on("/handleLogin", handleLogin);

  //serving file managment pages
  server.on("/filepage.php", handleFilePage);
  server.on("/createfile.php", handleCreateFilePage);

  //serving file managment actions
  server.on("/readFile", handleFileReading);
  server.on("/createFile", handleFileCreating);
  server.on("/editFile", handleFileEditing);
  server.on("/executeFile", handleFileExecuting);
  server.on("/deleteFile", handleFileDeleting);
  server.on("/listFile", handleFileList);
  server.on("/submitEditFile", handleSubmitEdit);

  //diplay username and password lists for debugging purposes
  //removed for security
  //server.on("/usernamelist.txt", handleUser);
  //server.on("/userpasswordlist.txt", handlePass);
  server.begin();
  
}

//-------------------------------------------------
// Debugging Methods
//-------------------------------------------------
void replyServerError(String msg) {
  Serial.println(msg);
  server.send(500, FPSTR(TEXT_PLAIN), msg + "\r\n");
}

void replyBadRequest(String msg) {
  Serial.println(msg);
  server.send(400, FPSTR(TEXT_PLAIN), msg + "\r\n");
}

//-------------------------------------------------
// Methods to access/dispaly HTML Pages
//-------------------------------------------------
//serves the home page
void serveIndexFile()
{
  File file = LittleFS.open("/index.php", "r");
  server.streamFile(file, "text/html");
  file.close();
}

//handles events for returning to the home page
void handleIndex()
{
  File file = LittleFS.open("/index.php", "r");
  server.streamFile(file, "text/html");
  file.close();
}

//displays the registration page on the server
void handleRegistration()
{
  File file = LittleFS.open("/registration.php", "r");
  server.streamFile(file, "text/html");
  file.close();
}

//displays the login page on the server
void handleLogin()
{
  File file = LittleFS.open("/login.php", "r");
  server.streamFile(file, "text/html");
  file.close();
}

//displays the welcome page on the server
void handleWelcomePage()
{
    File file = LittleFS.open("/welcome.php", "r");
    server.streamFile(file, "text/html");
    file.close();
}

//display the usernamelist on the server
void handleUser()
{
  File file = LittleFS.open("/usernamelist.txt", "r");
  server.streamFile(file, "text/plain");
  file.close();
}

//displays the password list on the server
void handlePass()
{
  File file = LittleFS.open("/userpasswordlist.txt", "r");
  server.streamFile(file, "text/plain");
  file.close();
}

//displays the file page on the server
void handleFilePage()
{
  File file = LittleFS.open("/filepage.php", "r");
  server.streamFile(file, "text/html");
  file.close();
}

//displays the file creation page on the server
void handleCreateFilePage()
{
  File file = LittleFS.open("/createfile.php", "r");
  server.streamFile(file, "text/html");
  file.close();
}

//-------------------------------------------------
// Methods for file operations
//-------------------------------------------------
//handles create files
void handleFileCreating()
{
    //recieves filename and contents from server
    String filename = server.arg("Filename");
    String fileContents = server.arg("contents");

    File test = LittleFS.open(filename, "r");

    if(test)
    {
      return replyServerError(F("ERROR: FILE ALREADY EXISTS"));
    }
    test.close();
    //recieves permissions entered by the user 
    String readUsers = server.arg("readUsers");
    String writeUsers = server.arg("writeUsers");
    String executeUsers = server.arg("executeUsers");
  
    File currentUser = LittleFS.open("currentUser.txt", "r");
    String currentUserName = currentUser.readStringUntil('\n');
  
    //makes a unquire ACL file for the file
    String aclFilename = filename + "ACL";
  
    if (filename.isEmpty())
    {
      return replyBadRequest(F("PATH ARG MISSING"));
    }
  
    //create both files
    File file = LittleFS.open(filename, "w");
    File aclFile = LittleFS.open(aclFilename, "w");

    //if the files exist, write the ACL
    if (file && aclFile)
    {
      file.print(fileContents);
      file.close();
      aclFile.print("Owner,");
      aclFile.print(currentUserName + ",\n");
       aclFile.print("Write,");
      aclFile.print(writeUsers + "," + currentUserName + ",\n");
      aclFile.print("Read,");
      aclFile.print(readUsers + "," + currentUserName + ",\n");
      aclFile.print("Execute,");
      aclFile.print(executeUsers + "," + currentUserName + ",\n");
      aclFile.close();
    }
    else
    {
      return replyServerError(F("CREATE FAILED"));
    }
    Serial.println("\n-----------------------------------------------------");
    Serial.println("New File Created:" + filename);
    readFile(filename.c_str());
    Serial.println("\n-----------------------------------------------------");
    handleFilePage();
}

//handles the deleting of a file
void handleFileDeleting()
{
    String filename = server.arg("FilenameDelete");
    
    if (filename.isEmpty())
    {
       return replyBadRequest(F("PATH ARG MISSING"));
    }
    
    File aclFile = LittleFS.open(filename+"ACL", "r");
    if(aclFile)
    {
          
        File currentUser = LittleFS.open("currentUser.txt", "r");
    
        String currentUserName = currentUser.readStringUntil('\n');
        Serial.println("\n-----------------------------------------------------");
        Serial.println("Attempting to Delete File: " + filename);
        Serial.println("Current User:" + currentUserName);
        Serial.println("File ACL contents:");
        readFile((filename+"ACL").c_str());
        String aclCheck;
        
       while(aclFile.available())
       {
        Serial.println("Checking current user to ACL:");
      
        aclCheck = aclFile.readStringUntil(',');
        
        Serial.println(aclCheck);
        Serial.println(currentUserName);
      
        //compare the current username to the aclList
        if(aclCheck == currentUserName)
        {
          Serial.println("Permission Granted.");
          
          File file = LittleFS.open(filename, "r");
          if (file)
          {
            deleteFile(filename.c_str());
            deleteFile((filename+"ACL").c_str());
            handleFilePage();
            aclFile.close();
            currentUser.close();
            Serial.println("\n-----------------------------------------------------");
            return;
          }
          else
          {
            return replyServerError(F("FILE NOT FOUND"));
          }
        }
        //if the file gets to the read line, print an error
        if(aclCheck == "\nWrite")
        {
          aclFile.close();
          currentUser.close();
          return replyServerError(F("ERROR: YOU ARE NOT THE OWNER OF THE FILE, YOU DO NOT HAVE DELETE PERMISSION"));
        }
       }
    }
    else
    {
      return replyServerError(F("ERROR: FILE DOES NOT HAVE A ACL, CANNOT PERFORM ACTION"));
    }
}


//handles the editing of a file
void handleFileEditing()
{
    //recieves filename and contents from server
    String filename = server.arg("Filename");
    //String fileContents = server.arg("contents");
  
    if (filename.isEmpty())
    {
         return replyBadRequest(F("PATH ARG MISSING"));
    }
      File aclFile = LittleFS.open(filename+"ACL", "r");
      File currentUser = LittleFS.open("currentUser.txt", "r");
      
      if(aclFile)
      {
        String currentUserName = currentUser.readStringUntil('\n');
        Serial.println("\n-----------------------------------------------------");
        Serial.println("Attempting to Write File: " + filename);
        Serial.println("Current User:" + currentUserName);
 
        readFile((filename+"ACL").c_str());
        String aclCheck;
        Serial.println();
        while(aclFile.available())
        {
          Serial.println("Checking current user to ACL: ");
        
          aclCheck = aclFile.readStringUntil(',');
          
          Serial.println("ACL:" + aclCheck);
          Serial.println("Current user:" + currentUserName + "\n");
        
          //compare the current username to the aclList
          if(aclCheck == currentUserName)
          {
            Serial.println("Write permission granted.");
            Serial.println("\n-----------------------------------------------------");
            
            //File file = LittleFS.open(filename, "w");
            File file = LittleFS.open(filename, "r");
            if (file)
            {
              String fileContents;
              while(file.available())
              {
                fileContents = fileContents + char(file.read());
              }
              String content = "<html><head><meta charset='utf-8'><meta name='viewport' content='width=device-width'><style>h1 {text-align: center;}body {background-color: lightblue};</style>";
              content += "<title>FrostByte CY320 Edit File</title></head>";
              content += "<body><h1>FrostByte CY320 Edit File Page</h1><hr  size='3' width='100%' color='black'>";
              content += "<form method='post' action='submitEditFile'><label><b>File Name: " + filename + "</b></label><input type='hidden' name='Filename' id='Filename' value='" + filename + "'>";
              content += "<br><br>Edit file contents here:<br><textarea rows = '12' cols = '100' name = 'contents' id ='contents' placeholder ='contents'>" + fileContents + "</textarea>";
              content += "<br><input type = 'submit' value = 'submit' /></form><br><hr><form action ='deleteFile' method ='post'><label><b>Enter File you would like to delete (ex: test.txt):</b></label>";
              content += "<input type='text' name='FilenameDelete' id='FilenameDelete' placeholder='FilenameDelete'><input type = 'submit' value = 'submit' /></form><br><form method='post' action='listFile'>";
              content += "<button type='submit'>List Files</button></form><br><hr><form method='get' action='filepage.php'><button type='submit'>File Management Page</button></form>";
              content += "<!--user option to go back--><br><form method='get' action='welcome.php'><button type='submit'>Welcome Page</button></form><br><form method='get' action='index.php'>";
              content += "<button type='submit'>Return Home</button></form></body></html>";
              server.send(200, "text/html", content);
              return;
            }
            else
            {
              return replyServerError(F("FILE NOT FOUND"));
            }
          }
          //if the file gets to the read line, print an error
          if(aclCheck == "\nRead")
          {
            aclFile.close();
            currentUser.close();
            return replyServerError(F("ERROR: YOU DO NOT HAVE WRITE PERMISSION"));
          }
        }
    }
    else
    {
       return replyServerError(F("ERROR: FILE IS NOT AVAILABLE OR DOES NOT HAVE A ACL, CANNOT PERFORM ACTION"));
    }
}

//write the edited contents to the file
void handleSubmitEdit()
{
  //recieves filename and contents from server
    String filename = server.arg("Filename");
    String fileContents = server.arg("contents");

    if (filename.isEmpty())
    {
      return replyBadRequest(F("PATH ARG MISSING"));
    }
  
    //create both files
    File file = LittleFS.open(filename, "w");
    
    if (file)
    {
      file.print(fileContents);
      file.close();
    }
    else
    {
      return replyServerError(F("EDIT FAILED"));
    }
    Serial.println("\n-----------------------------------------------------");
    Serial.println("File Edited:" + filename);
    readFile(filename.c_str());
    Serial.println("\n-----------------------------------------------------");
    handleFilePage();
}



//handles the reading of a file
void handleFileReading()
{
      String filename = server.arg("Filename"); 
      if (filename.isEmpty())
      {
         return replyBadRequest(F("PATH ARG MISSING"));
      }
      File aclFile = LittleFS.open(filename+"ACL", "r");
      File currentUser = LittleFS.open("currentUser.txt", "r");
      if(aclFile)
      {
        String currentUserName = currentUser.readStringUntil('\n');
        Serial.println("\n-----------------------------------------------------");
        Serial.println("Attempting to Read File: " + filename);
        Serial.println("Current User:" + currentUserName);
 
        readFile((filename+"ACL").c_str());
        String aclCheck;
        Serial.println();
        while(aclFile.available())
        {
          Serial.println("Checking current user to ACL: ");
        
          aclCheck = aclFile.readStringUntil(',');
          
          Serial.println("ACL:" + aclCheck);
          Serial.println("Current user:" + currentUserName + "\n");
        
          //compare the current username to the aclList
          if(aclCheck == currentUserName)
          {
            Serial.println("Read permission granted.");
            
            File file = LittleFS.open(filename, "r");
            if (file)
            {
              server.streamFile(file, "text/plain");
              file.close();
              aclFile.close();
              currentUser.close();
              Serial.println("\n-----------------------------------------------------");
              return;
            }
            else
            {
              return replyServerError(F("FILE NOT FOUND"));
            }
          }
          //if the file gets to the write line, print an error
          if(aclCheck == "\nExecute")
          {
            aclFile.close();
            currentUser.close();
            return replyServerError(F("ERROR: YOU DO NOT HAVE READ PERMISSION"));
          }
        }
    }
    else
    {
       return replyServerError(F("ERROR: FILE IS NOT AVAILABLE OR DOES NOT HAVE A ACL, CANNOT PERFORM ACTION"));
    }
}

//send a list of all current files to the webpage
void handleFileList()
{
  File root = LittleFS.open("/", "r");
 
  File file = root.openNextFile();

  File fileList = LittleFS.open("fileList.txt", "w");
  Serial.print("HANDLE FILE LIST CALLED");
 
  while(file)
  {
      Serial.print("File: ");
      fileList.print("FILE: ");
      String name = file.name();
      fileList.print(name + "\n");
      Serial.println(name);
      file = root.openNextFile();
  }
  fileList.close();
  File fileListSend = LittleFS.open("fileList.txt", "r");
  server.streamFile(fileListSend, "text/plain");
  file.close();
  root.close();
  fileListSend.close();
}

//current assignment doesn't require executing, placeholder for future development
void handleFileExecuting()
{
  return replyServerError(F("Executing not currently implemented for this assignment."));
}



//-------------------------------------------------
// Methods to handle user registration and login
//-------------------------------------------------

//handles the user input for registration
void handleRegistrationForm() 
{
 String username = server.arg("Username"); 
 String password = server.arg("Password"); 

File usernameFile = LittleFS.open("/usernamelist.txt", "r");

 //log activity on serial monitor
 Serial.println("\n-----------------------------------------------------");
 Serial.println("New User Attempting to Register:" + username);

 Serial.println("Password: " + password);
 
 //declare an error variable to check existing usernames
 int error = 0;
 
 String usernamelist;

 Serial.println("Checking current username list...");
 while(usernameFile.available())
 {
    usernamelist = usernameFile.readStringUntil('\n');
    Serial.println(usernamelist);
  if(usernamelist == username)
  {
    Serial.print("ERROR: Username already exists");
    error = 1;
    break;
  }
}
  if (error != 1){
    //write the credentials to corresponding files
    appendFile("/usernamelist.txt", username.c_str());
    appendFile("/userpasswordlist.txt", password.c_str());
    Serial.print("New user is registered. Credentials saved to ACL");
    Serial.println("\n-----------------------------------------------------");

    //return to index page
    File file = LittleFS.open("/index.php", "r");
    server.streamFile(file, "text/html");
    file.close();
  }
  else {
    Serial.print("ELSE");
    String m = MAINS_page;
    server.send(200, "text/html", m);
    usernameFile.close();
  }
}

//handles the user login information
void handleWelcome()
{
 String username = server.arg("Username"); 
 String password = server.arg("Password"); 

 File usernameFile = LittleFS.open("/usernamelist.txt", "r");
 File passwordFile = LittleFS.open("/userpasswordlist.txt", "r");

 //log activity on serial monitor
 Serial.println("\n-----------------------------------------------------");
 Serial.println("User Attempting to login:" + username);

 String usernamelist;
 String passwordlist;
 Serial.println("Checking credentials...");
 while(usernameFile.available() && passwordFile.available())
 {
  usernamelist = usernameFile.readStringUntil('\n');
  passwordlist = passwordFile.readStringUntil('\n');
  Serial.println(usernamelist);
  Serial.println(passwordlist + "\n");
  if(usernamelist == username && passwordlist == password)
  {
    Serial.println("Login Successful: ");
    //create a file to keep track of the current user    
    File currentUserFile = LittleFS.open("currentUser.txt", "w");
    if (currentUserFile)
    {
      currentUserFile.print(username+"\n");
      currentUserFile.close();
    }
    else
    {
      return replyServerError(F("CURRENT USER ESTABLISHMENT FAILED"));
    }
    File file = LittleFS.open("/welcome.php", "r");
    server.streamFile(file, "text/html");
    file.close();
    Serial.println("-----------------------------------------------------");
    return; 
  }
 }
 Serial.println("Login Failed");
 Serial.println("\n-----------------------------------------------------");
 String s = MAIN_page;
 server.send(200, "text/html", s);
 usernameFile.close();
 passwordFile.close();
}

//-------------------------------------------------
// File System Methods with serial Monitor output
// Taking from LittleFS example on IDE
//-------------------------------------------------
void readFile(const char * path) {
  Serial.printf("Reading file: %s\n", path);

  File file = LittleFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: \n");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void writeFile(const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  delay(2000); // Make sure the CREATE and LASTWRITE times are different
  file.close();
}

void appendFile(const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = LittleFS.open(path, "a");
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    file.print("\n");
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void renameFile(const char * path1, const char * path2) {
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (LittleFS.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void deleteFile(const char * path) {
  Serial.printf("Deleting file: %s\n", path);
  if (LittleFS.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

//-------------------------------------------------
// Setup and loop section
//-------------------------------------------------

void loop()
{
  server.handleClient();
}
