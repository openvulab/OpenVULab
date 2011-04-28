<?php
/*
###################################################################
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
###################################################################
*/
?>
<?php
/*
File: 		mod.response.php \\v 1.0
Info:		- dutchtape fix for the vid implementation
Author: 	Blake Edwards
Email:		electBlake@gmail.com

License: 	http://source.fluidproject.org/svn/fluid/components/trunk/LICENSE.txt
*/
?>
<?php
	require_once('../admin/include_all.php');
	require_once("./phpESP.first.php");	
	include('../admin/include/lib/vulab.responses.class.php');

	if ($_SERVER['REQUEST_METHOD'] == 'POST') {
		$response = new Response(@$_POST[rid]);
		@$response_data = array('vid'=>@$_POST[vid]);
		$result = $response->update(@$response_data);
		if (is_array($result)) {
			$err = $result;
		} else {
			if ($result) {
				echo "Successfully submitted your Video ID! <br />You Can Now Return with the Above Link";
			}
		}
	}

?>