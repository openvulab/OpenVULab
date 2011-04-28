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
# basic config file switching
if (is_numeric(stripos($_SERVER['SERVER_NAME'],'localhost'))) {
	include ('phpESP.ini-local.php');
	include ('config.localhost.php');
} else { // its running on a real live domain.
	include ('config.legacylive.php');
	include ('config.live.php');
 } // locahost else

?>