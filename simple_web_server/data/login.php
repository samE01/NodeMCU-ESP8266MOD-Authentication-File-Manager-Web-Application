<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width">
    
    <style>
      h1 {text-align: center;}
      body {background-color: lightblue};
    </style> 

    <title>FrostByte CY320 Login Page</title>
  </head>
  <body>
    <h1>FrostByte CY320 User Authentication Page</h1>
    <hr size="3" width="100%" color="black">
    <br>
    <div class="login">    
    <form id="login" method="post" action="handleWelcome">    
      <label>
        <b>Username:</b>    
      </label>    
      <input type="text" name="Username" id="Username" placeholder="Username">    
      <br><br>    
      <label>
        <b>Password:</b>    
      </label>    
      <input type="Password" name="Password" id="Password" placeholder="Password">    
      <br>
      <br>
      <input type="submit" name="submit" />
      </form>
      <br>
      <hr size="3" width="100%" color="black">
      <br>
      <form method="get" action="index.php">
        <button type="submit">Return Home</button>
      </form>
      <br>
      <form method="get" action="registration.php">
        <button type="">Registration</button>
      </form>
  </div>   
  </body>
</html>