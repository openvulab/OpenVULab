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
   if (!isset($_SESSION)) session_start();

   // if the session fails to start
   if (!isset($_SESSION)) {
      echo "This script can't work without setting the php session variable first!!!";
      exit ;
   }

   function response_check_captcha($post_var,$cleanup=1) {
      if (!isset($_POST[$post_var]) || (md5($_POST[$post_var]) != $_SESSION['captcha'])) {
	   return _('You entered an incorrect code. Please fill in the correct code.');
      } else {
	if ($cleanup==1) {
      	   unset($_SESSION['captcha']);
      	   unset($_POST[$post_var]);
	}
        return ('');
      }
   }
?>