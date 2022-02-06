<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width">
    
    <style>
      h1 {text-align: center;}
      body {background-color: lightblue};
    </style> 

    <title>FrostByte CY320 File Management Page</title>

  </head>

  <body>

    <h1>FrostByte CY320 File Management Page</h1>
    <hr size="3" width="100%" color="black">
    
    <p>Select An Option Below To Manage Your File:</p>
    <p>Note: when entering a file, include the full name (ex: test.txt)</p>
    <!--Needs buttons and options?; needs to be linked to welcome page from login.php-->
    <form method="get" action="createfile.php">
        <button type="submit">Create File</button>
    </form>
      
    <br>
    <form method="get" action="readFile">  
        <button type="submit">Read File</button>
        <input type="text" name="Filename" id="Filename" placeholder="Filename">    
        <br>
    </form>
      
	<br>
    <form method="get" action="editFile">
        <button type="submit">Edit File</button>
        <input type="text" name="Filename" id="Filename" placeholder="Filename">    
        <br>
    </form>
	<br>
    
    <form method="get" action="executeFile">
        <button type="submit">Execute File</button>
        <input type="text" name="Filename" id="Filename" placeholder="Filename">    
        <br>
    </form>
    <br>
    <form action ="deleteFile" method ="post">
        <button type="submit">Delete File</button>
        <input type="text" name="FilenameDelete" id="FilenameDelete" placeholder="Filename">    
    </form>
      
    <br>
    <form method="post" action="listFile">
    <button type="submit">List Files</button>
    </form>

    <!--I left this the same so the user had the option to go back-->
    <br>
    <hr>
    <form method="get" action="welcome.php">
    <button type="submit">Welcome Page</button>
    </form>
    <br>
    <form method="get" action="index.php">
    <button type="submit">Return Home</button>
    </form>

  </body>

</html>