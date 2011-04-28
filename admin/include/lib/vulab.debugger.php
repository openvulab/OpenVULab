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
//Vulab debugging

session_start();

if ($_GET[debug]) {
	$_SESSION[debug] = true;
}
if ($_GET[debug] == 'off') {
	unset($_SESSION[debug]);
}
?>