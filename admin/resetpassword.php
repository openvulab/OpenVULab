<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?>
<?php
if (isset($_POST['submit']))
{
	$required_fields = array(
		'username'
	);
	foreach ($required_fields as $field)
	{
		if (!isset($_REQUEST[$field]))
			error_required_field();
	}
	$confirmation = array(
	);
	foreach ($confirmation as $field)
	{
		if (!($_REQUEST[$field] == $_REQUEST['c'.$field]))
			error_non_confirmed();
	}
	include('include_all.php');
    esp_init_adodb();
    $sql = "SELECT * FROM $ESPCONFIG[user_table] WHERE `username` = '$_REQUEST[username]'";
    $result = execute_sql($sql);
    if ($result->RecordCount() <= 0)
    	error_username_invalid();
    //$sql = "UPDATE $ESPCONFIG[user_table] SET `password` = PASSWORD('change_me_now')";
    $sql = "UPDATE $ESPCONFIG[user_table] SET `password` = PASSWORD('change1me') where `username` =  '$_REQUEST[username]'";
    $n = execute_sql($sql);
    
    $mailMSG = "$_REQUEST[username]:\n\tYour password has been changed. Your new password is \"change1me\" (without quotes). Please log in and change this password as soon as possible.";
    
    mail($result->fields[5],"Password Change Notification",$mailMSG);
    
	echo "Your password has successfully been changed, and an email has been dispatched to you with your new password.";
	echo "<br/> <a href='/'>Back to Login</a>";
}
else
	showForm();
function error_required_field()
{
	showForm('Your have omitted one or more required fields.');
}
function error_non_confirmed()
{
	showForm('Your passwords and/or e-mail addresses did not match their confirmation tests.');
}
function showForm($error = null)
{
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
    <meta http-equiv="Content-type" content="text/html;charset=UTF-8" />
<title>OpenVULab Registration</title>
<link rel="stylesheet" href="http://vulabdev.silkwire.com/vulab-dev/public/css/default.css" type="text/css" />
</head>
<body id="auth">
<div class="headerGraphic"></div><div class="login">OpenVULab Registration
<form id="loginform"  method="post">
<fieldset><legend>Reset Password</legend>
<h2>Please fill out the following form (all fields are required) to reset your password</h2>
<?php
	if ($error != null)
		echo '<h2 style="color:red">ERROR: '.$error.'</h2>';
?>
<div class="row"><label for="email">Email:</label><input type="text" size="20" name="email" id="email" />
</div><div class="row">
<input type="submit" name="submit" value="Submit" /><input type="reset" value="Clear" /></div></fieldset>
</form>
</div>
</body>
</html>
<?php
	exit();
}
?>