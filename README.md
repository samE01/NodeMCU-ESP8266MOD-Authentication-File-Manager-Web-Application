# NodeMCU-ESP8266MOD-Authentication-File-Manager-Web-Application
This application has three main components:  
- Registration 
- Authentication 
- File Manager 

Once a user registers via an online sign up page, they are directed to a login page where they can login into the application's file management system. The system allows users to create, read, edit, and delete files on the server. Then a file is created, the owner sets the read and write privilege's given to other users. The privileges are based on a whitelist, so only the users listed have access to the privilege. While the authentication, file ACLs, and rigorous system logs provide some security to the application, the security can still be improved. One potential exploit is an attacker using the "list files" option on the server to ascertain the name of the password list file. Then, they could create a fake ACL list for the password file and gain access to it. The purpose of this project was to learn how backend code interacts with front-end code on a server, and to gain an appreciation for the challenges regarding authentication and ACL security implementations
