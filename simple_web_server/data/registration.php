<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width">
    
    <style>
      h1 {text-align: center;}
      body {background-color: lightblue};
    </style> 

    <title>FrostByte CY320 Registration</title>
  </head>
  <body>
    <h1>FrostByte CY320 User Registration</h1>
    <hr size="3" width="100%" color="black">
    <br>
    <div class="registration">    
      <form id="registration" method="post" action="handleRegistration">    
        <label>
          <b>Username:</b>    
        </label>    
        <input type="text" name="Username" id="Username" placeholder="Username">    
        <br><br>    
        <label>
          <b>Password:</b>    
        </label>    
        <input type="Password" name="Password" id="Password" placeholder="Password">    
        <br><br>
        <input type="submit" name="submit" />    
      </form>
      <br>
      <hr size="3" width="100%" color="black">
      <br>
      <form method="get" action="index.php">
        <button type="submit">Return Home</button>
      </form>
      <br>
      <form method="get" action="login.php">
        <button type="submit">User Login</button>
      </form>
    </div>   
  </body>
</html>