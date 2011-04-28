<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?><?php
/*
File: 		step_process_5.inc \\v 1.0
Info:		- to be used with ?where=create&step=5 - Process data from the 5th step (inviting users)
Author: 	Blake Edwards
Email:		electBlake@gmail.com

License: 	http://source.fluidproject.org/svn/fluid/components/trunk/LICENSE.txt
*/
?>
<?php

$userids_select = $_POST[users];

$subject = "You've Been Invited! - Participation in Survey";
$message = 
"Welcome <user-fname> <user-lname>, \n
You've been invited to participate in the following usability project survey! \n

<project-name> \n
<project-intro>\n
\n
Participate in <project-name>!\n
at http://130.63.175.158/public/project.php?id=<project-id>
";
foreach ($userids_select as $userid) {
	$user = new User($userid);
	$options = array('pid'=>$_SESSION[pid]);
	$mailresults = $user->email($subject,$message,$options);
	if ($mailresults) {
		$good[] = 'Invitations Successfully Sent!';
		$addUser = new Perm('user',$userid);
		$assignResult = $addUser->assignUser($_SESSION[pid]);
		if (is_array($assignResult)) {
			$err[] = $assignResult;
		} else { 
			$good[] = $assignResult;
		}
	} else {
		/*To test without mail server*/
		$addUser = new Perm('user',$userid);
		$assignResult = $addUser->assignUser($_SESSION[pid]);
		if (is_array($assignResult)) {
			$err[] = $assignResult;
		} else { 
			$good[] = $assignResult;
		}
		$err[] = "Your invitation will be sent when this project is activated!";
	}
}
if (is_array($err)) {
	$step = $from;
}


?>