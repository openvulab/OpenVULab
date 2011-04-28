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
echo "To Whom it may Concern:\n\tA new signup has been submitted for a researcher with the following details:\n\tUsername: $_REQUEST[username]\n\tName: $_REQUEST[fname] $_REQUEST[lname]\n\tE-Mail Address: $_REQUEST[email]\n\n\tTo disable this user's account, please click here: http://".$_SERVER['SERVER_NAME']."/admin/disable.php?username=$_REQUEST[username]\n\n\nThis is an automated e-mail.";
?>