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
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
	unset($found_user);
	# inital includes
	require_once 'include_all.php';
	require_once ($ESPCONFIG['include_path']."/lib/vulabdatalib.php");
    esp_init_adodb();
    
	# lets see if there are any users in the database
	$users_sql = 'SELECT * FROM user';
	$users_res = execute_sql($users_sql);
	if (!$users_res) {
	}
	$users_num = $users_res->RecordCount();
    
    if ($users_num > 0) { $found_user = true; } else { $found_user = false; }

    # if there is no users found, aka this is the first user, lets make them a superuser
    if ($found_user == true) {
    	$realm = 'auto';
    } else {
    	$realm = 'superuser';
    }    

if (isset($_REQUEST['Register']))
{
	$required_fields = array(
		'username',
		'password',
		'cpassword',
		'email',
		'cemail'
	);
	foreach ($required_fields as $field)
	{
		//echo $field;
		if (!isset($_REQUEST[$field]) || empty($_REQUEST[$field]))
			error_required_field();
	}
	$confirmation = array(
		'password',
		'email'
	);
	if (!preg_match("/\b[A-Z0-9._%-]+@[A-Z0-9.-]+\.[A-Z]{2,4}\b/i", $_REQUEST['email']))
		error_invalid_email();
	foreach ($confirmation as $field)
	{
		//echo $field;
		if (!($_REQUEST[$field] == $_REQUEST['c'.$field]))
			error_non_confirmed();
	}
	
	$uname_sql = "SELECT * FROM user WHERE username='$_REQUEST[username]'";
	$uname_res = execute_sql($uname_sql);
	$user_name = $uname_res->RecordCount();
	if ($user_name < 1) {
    $sql = "INSERT INTO $ESPCONFIG[user_table] VALUES('','$_REQUEST[username]',PASSWORD('$_REQUEST[password]'),'$_REQUEST[fname]','$_REQUEST[lname]','$_REQUEST[email]','$_REQUEST[type]','N')";
    $result = execute_sql($sql);
    
    if ($_REQUEST['type'] == 'Y')
    {
	    $sql = "INSERT INTO `designer` VALUES ('$_REQUEST[username]',PASSWORD('$_REQUEST[password]'),'BASIC','$realm','$_REQUEST[fname]','$_REQUEST[lname]','$_REQUEST[email]','Y','N','N','N','N','N','N',now(),NULL)";
    	$result = execute_sql($sql);
		}
		$sql = "INSERT INTO `respondent` VALUES('$_REQUEST[username]',PASSWORD('$_REQUEST[password]'),'BASIC','$realm','$_REQUEST[fname]','$_REQUEST[lname]','$_REQUEST[email]','N',now(),NULL)";
    $result = execute_sql($sql);
    
    if ($_REQUEST['type'] == 'Y') {
    	//$emailMESSAGE = "To Whom it may Concern:\n\tA new signup has been submitted for a researcher with the following details:\n\tUsername: $_REQUEST[username]\n\tName: $_REQUEST[fname] $_REQUEST[lname]\n\tE-Mail Address: $_REQUEST[email]\n\n\tTo disable this user's account, please click here: http://".$_SERVER['SERVER_NAME']."/admin/disable.php?username=$_REQUEST[username]\n\n\nThis is an automated e-mail.";
	    //mail($ESPCONFIG['email']['to'],$ESPCONFIG['email']['subject'],$emailMESSAGE);
		}
	
		$user = new User(mysql_insert_id());
		$options = array('type'=>'welcome','from'=>'invite@vulab.electblake.com');
		$mailresults = $user->email($subject,$message,$options);
		if ($mailresults) {
			echo 'Welcome Email Successfully Sent!</br>';
		} else {
			$err[] = "Sorry! Welcome email cannot be sent at this time.";
		}    
		show_success();
	}
	else
		error_user_exist();
}
else
	showForm();
	
function error_required_field()
{
	showForm('You have omitted one or more required fields.');
}
function error_non_confirmed()
{
	showForm('Your passwords and/or e-mail addresses did not match their confirmation tests.');
}
function error_invalid_email()
{
	showForm('You have entered and invalid email address.');
}
function error_user_exist()
{
	showForm('Username already exist. Try another username.');
}
function show_success()
{
	showForm('Successful');
}
function showForm($error = null)
{
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
    <meta http-equiv="Content-type" content="text/html;charset=UTF-8" />
<title>OpenVULab Registration</title>
<script type="text/javascript" src="../js/default.js"></script>
<script type="text/javascript" src="../js/jquery-1.2.6.pack.js"></script>
<script type="text/javascript" src="../js/jquery.ajaxContent.js"></script>
<script type="text/javascript" src="../js/vulab.admin.js"></script>
<script type="text/javascript" src="../js/jquery.form.js"></script>
<script type="text/javascript" src="../js/thickbox.js"></script>
<script type="text/javascript" src="../js/jquery.curvycorners.min.js"></script>
<?php 
		if (empty($_css)) {
       $_css = "style.css";
    }
    $str .= '<link rel="stylesheet" href="'. $GLOBALS['ESPCONFIG']['css_url'].$_css .'" type="text/css" />';
    echo $str;
//<link rel="stylesheet" href="http://vulabdev.silkwire.com/vulab-dev/public/css/default.css" type="text/css">
?>
</head>
<body id="auth">
<div id="main">
	<div id="header">
	<div class="usergreeting"><a href="../index.php"></a></div>
	</div>
	<div id="body">
		<div class="contents">
			<h1>OpenVULab Registration</h1>
<form id="loginform"  method="post" action="">
	<div id="container">
<fieldset><legend>Registration</legend>
<span class="error">All fields are required unless marked otherwise</span>
<div class="clear"></div>

<?php
	if ($error != null && !($error === "Successful"))
		echo '<h2 style="color:red">ERROR: '.$error.'</h2>';
?>
<div class="row"><label for="username">Username:</label><input type="text" size="20" name="username" id="username"/>
</div><div class="row">
<label for="password">Password:</label><input type="password" name="password" id="password"/>
</div><div class="row">
<label for="cpassword">Confirm Password:</label><input type="password" name="cpassword" id="cpassword" />
</div><div class="row">
<label for="fname">First Name (optional):</label><input type="text" name="fname" id="fname"/>
</div><div class="row">
<label for="lname">Last Name (optional):</label><input type="text" name="lname" id="lname"/>
</div><div class="row">
<label for="email">E-Mail Address:</label><input type="text" name="email" id="email"/>
</div><div class="row">
<label for="cemail">Confirm E-Mail Address:</label><input type="text" name="cemail" id="cemail"/>
</div><div class="row">
<label for="type">I am a:</label><select name="type" id="type">
<?php
	# lets see if there are any users in the database
	$users_sql = 'SELECT * FROM user';
	$users_res = execute_sql($users_sql);
	if (!$users_res) {
	}
	$users_num = $users_res->RecordCount();
	
	//echo $users_num;
# if there are no users, lets make the first user a researcher aka admin aka superuser aka root
 if ($users_num < 1) {
?>
	<option value="Y">Admin User</option>
<?php
} else {
?>
	<option value="Y">Researcher</option>
	<option value="N" selected="selected">Tester</option>
<?php
}
?>
</select>
</div>
<?php 
	if ($error === "Successful") {
		echo '<span style="color: #FF0000; font-size: 13px">Thank you for registering! You may now <a href="/admin/">log in</a>.</span>';
	} ?>
<div class="row">
<input type="submit" name="Register" value="Submit" /><input type="reset" value="Clear" /></div></fieldset>
</div>
</form>
</div></div><div class="clear"></div>
<div id="footer"> Powered By OpenVULab, v(0.5b)  </div>
</div>
</body>
</html>
<?php
	exit();
}
?>