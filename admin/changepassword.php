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
require_once 'include_all.php';
require_once ($ESPCONFIG['include_path']."/lib/vulabdatalib.php");
    esp_init_adodb();
if (isset($_POST['submit']))
{
	$required_fields = array(
		'username',
		'pass',
		'newpass',
		'cnewpass'
	);
	foreach ($required_fields as $field)
	{
		if (!isset($_REQUEST[$field]) || empty($_REQUEST[$field]))
			error_required_field();
	}
	$confirmation = array(
		'newpass'
	);
	foreach ($confirmation as $field)
	{
		if (!($_REQUEST[$field] == $_REQUEST['c'.$field]))
			error_non_confirmed();
	}
  $sql = "SELECT * FROM $ESPCONFIG[user_table] WHERE `password` = PASSWORD('$_REQUEST[pass]') AND `username` = '$_REQUEST[username]'";
  $result = execute_sql($sql);
  if ($result->RecordCount() <= 0)
  	error_password_invalid();
  else {
    $sql = "UPDATE $ESPCONFIG[user_table] SET `password` = PASSWORD('$_REQUEST[newpass]') WHERE `username` = '$_REQUEST[username]'";
    $result = execute_sql($sql);
		show_success();
	}
}
else
	showForm();
function error_password_invalid()
{
	showForm('Your username/password entered is invalid.');
}
function error_required_field()
{
	showForm('Your have omitted one or more required fields.');
}
function error_non_confirmed()
{
	showForm('Your confirmation password did not match.');
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
<fieldset><legend>Change Password</legend>
<span class="error">Please fill out the following form (all fields are required) to change your password</span>
<div class="clear"></div>
<?php
	if ($error != null && !($error === "Successful"))
		echo '<h2 style="color:red">ERROR: '.$error.'</h2>';
?>
<div class="row"><label for="username">Username:</label><input type="text" size="20" name="username" id="username"/>
</div>
<div class="row"><label for="pass">Current Password:</label><input type="password" size="20" name="pass" id="pass"/>
</div>
<div class="row"><label for="newpass">New Password:</label><input type="password" size="20" name="newpass" id="newpass"/>
</div>
<div class="row"><label for="cnewpass">Confirm New Password:</label><input type="password" size="20" name="cnewpass" id="cnewpass"/>
</div>
<?php 
	if ($error === "Successful") {
		echo '<span class="error">Your password has successfully been changed! You may now <a href="/admin/">log in</a>.</span>';
	} ?>
<div class="clear"></div>
<div class="row">
<input type="submit" name="submit" value="Submit" /><input type="reset" value="Clear" /></div></fieldset>
</div>
</form>
</div></div></div><div class="clear"></div>
<div id="footer"> Powered By OpenVULab, v(0.5b)  </div>
</body>
</html>
<?php
	exit();
}
?>