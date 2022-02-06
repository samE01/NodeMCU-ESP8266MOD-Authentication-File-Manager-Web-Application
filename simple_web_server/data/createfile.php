<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width">
    
    <style>
      h1 {text-align: center;}
      body {background-color: lightblue};
    </style> 

    <title>FrostByte CY320 File Management Page (Create File)</title>

  </head>

   <body>

    <h1>FrostByte CY320 Create A File Page</h1>
    <hr size="3" width="100%" color="black">

      <form action = "createFile" method = "post" id="fileform">
          <label>
          <b>Enter full file name (ex: test.txt):</b>    
          </label>    
          <input type="text" name="Filename" id="Filename" placeholder="Filename">    
          <br>
          <label>
          <b>Enter users with read permissions (separate with a comma and no space):</b>    
          </label>    
          <input type="text" name="readUsers" id="readUsers" placeholder="readUsers">
          <br>
          <br>
          <b>Enter users with write permissions (separate with a comma and no space):</b>        
          <input type="text" name="writeUsers" id="writeUsers" placeholder="writeUsers">
          <br>
          <br>
          <b>Enter users with execute permissions (separate with a comma and no space):</b>       
          <input type="text" name="executeUsers" id="executeUsers" placeholder="executeUsers">
          <br>
          <br>
         Enter file contents here:
         <br>
         <textarea rows = "15" cols = "100" name = "contents" id ="contents" placeholder ="contents" form="fileform"></textarea>
         
         <br>
         <input type = "submit" value = "submit" />
      </form>
    <br>
    <form method="post" action="listFile">
    <button type="submit">List Files</button>
    </form>
    <br>
    <hr>
    <br>
    <form method="get" action="filepage.php">
    <button type="submit">File Management Page</button>
    </form>
    <br>
    <form method="get" action="welcome.php">
    <button type="submit">Welcome Page</button>
    </form>
    <br>
    <form method="get" action="index.php">
    <button type="submit">Return Home</button>
    </form>
   </body>
</html> 