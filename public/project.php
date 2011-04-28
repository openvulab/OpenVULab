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
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
/* $Id: survey.php,v 1.21 2007/07/09 12:58:21 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Matthew Gregg
// <greggmc at musc.edu>

	require_once('../admin/include_all.php');
	require_once("./phpESP.first.php");	
	error_reporting(E_ALL);
	$_name = '';
	$_title = '';
	$_css = '';
    $sid = '';
    
    
    if (isset($_GET['id'])) {
    	$aProject = new Project;
    	$aProject->init($_GET['id']);
    	if ($aProject->details['status'] != 2) {
    		die('<h1>This study is not available at this time. We\'re Sorry!</h1><ul><li><a href="javascript:history.go(-1)">Go Back...</a></li><li><a href="http://vulab.yorku.ca">Go to VULab.yorku.ca</li></ul>');
    	}
    }
	/*if (isset($_GET['name'])) {
		$_name = _addslashes($_GET['name']);
		unset($_GET['name']);
		$_SERVER['QUERY_STRING'] = ereg_replace('(^|&)name=[^&]*&?', '', $_SERVER['QUERY_STRING']);
	}
    	if (isset($_POST['name'])) {
        	$_name = _addslashes($_POST['name']);
        	unset($_POST['name']);
    	}

	if (!empty($_name)) {
        	$_sql = "SELECT id,name,presurvey,postsurvey,action_url FROM project WHERE name = $_name";
        	if ($_result = execute_sql($_sql)) {
            		if (record_count($_result) > 0)
                		list($sid, $_pname, $_pres,$_posts, $_action) = fetch_row($_result);
            		db_close($_result);
        	}
        	unset($_sql);
        	unset($_result);
	}
	*/
	if (isset($_GET['id'])) {
		$_id = _addslashes($_GET['id']);
		unset($_GET['id']);
		$_SERVER['QUERY_STRING'] = preg_replace('/(^|&)id=[^&]*&?/', '', $_SERVER['QUERY_STRING']);
	}
    	if (isset($_POST['id'])) {
        	$_id = _addslashes($_POST['id']);
        	unset($_POST['id']);
    	}

	if (!empty($_id)) {
        	$_sql = "SELECT id,name,presurvey,postsurvey,action_url FROM project WHERE id = $_id";
        	if ($_result = execute_sql($_sql)) {
            		if (record_count($_result) > 0)
                		list($sid, $_pname, $_pres,$_posts, $_action) = fetch_row($_result);
            		db_close($_result);
        	}
        	unset($_sql);
        	unset($_result);
	}
        // To make all results public uncomment the next line.
        //$results = 1;
        // See the FAQ for more instructions.

        // call the handler-prefix once $sid is set to handle
        // authentication / authorization


       $presql = "select name from survey where id = " . $_pres;
       //$postsql = "select name from survey where id = " . $_posts;
		if ($_result = execute_sql($presql)) {
            		if (record_count($_result) > 0)
                		list($prename) = fetch_row($_result);
            		db_close($_result);
        	}
        	unset($presql);
        	unset($_result);
        	
        //$presql = "select name from survey where id = " . $_pres;
       $postsql = "select name from survey where id = " . $_posts;
		if ($_result = execute_sql($postsql)) {
            		if (record_count($_result) > 0)
                		list($postname) = fetch_row($_result);
            		db_close($_result);
        	}
        	unset($postsql);
        	unset($_result);
		
       
      /*$sqlins = 'update survey set thanks_page =' .
     " 'gluebox.php?ps=$postname".  "&pid=" . $_action ."' where id =" . $_pres;*/
	
	//$result = execute_sql($sqlins);
	//echo ErrorMsg();
	//db_close($_result);

	if (isset($_pres) && $_pres != "" && $_pres != null && $_pres>0 ) {
			header("Location: survey.php?id=" . $_pres ."&project=$sid&stype=pre"); 
			exit;
		}
	elseif (isset($_action) && $_action != "" && $_action != null) {
		header("Location: gluebox.php?&project=$sid");
		}
	elseif (isset($_posts) && $_posts != "" && $_posts != null && $_pres>0 ) {
		header("Location: survey.php?id=" . $_posts ."&project=$sid&stype=post");
		}
	else
	{
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><?php echo($_pname); ?></title>
<script type="text/javascript" src="<?php echo($ESPCONFIG['js_url']);?>default.js"></script>
<?php
    if (!empty($_css)) {
	    echo('<link rel="stylesheet" href="'. $GLOBALS['ESPCONFIG']['css_url'].$_css ."\" type=\"text/css\" />\n");
    }
    unset($_css);
?>
</head>
<body>
<?php
	/*if (isset($_pres) && $_pres != "" && $_pres != null && $_pres>0 )
		echo "<a href=\"survey.php?id=" . $_pres ."&project=$sid&stype=pre\">Pre-Survey</a><br />";
	if (isset($_action) && $_action != "" && $_action != null)
		echo "<a href=\"gluebox.php?&project=$sid\">Visit URL</a><br />";
	if (isset($_posts) && $_posts != "" && $_posts != null && $_pres>0 )
		echo "<a href=\"survey.php?id=" . $_posts ."&project=$sid&stype=post\">Post-Survey</a><br />";*/
?>
This survey does not have any action handlers!
</body>
</html>
<?php
	}
?>