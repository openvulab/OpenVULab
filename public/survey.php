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

  File: 		survey.php \\v 1.0
  Info:		- public viewing/handling of surveys
  Author: 	Blake Edwards
  Email:		electBlake@gmail.com

  License: 	http://source.fluidproject.org/svn/fluid/components/trunk/LICENSE.txt
 */

/* $Id: survey.php,v 1.21 2007/07/09 12:58:21 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Matthew Gregg
// <greggmc at musc.edu>
require_once('../admin/include_all.php');
require_once("./phpESP.first.php");

$_name = '';
$_title = '';
$_css = '';
$sid = '';

if (isset($_GET['name'])) {
    $_name = _addslashes($_GET['name']);
    unset($_GET['name']);
    $_SERVER['QUERY_STRING'] = ereg_replace('(^|&)name=[^&]*&?', '', $_SERVER['QUERY_STRING']);
}
if (isset($_POST['name'])) {
    $_name = _addslashes($_POST['name']);
    unset($_POST['name']);
}

if (!empty($_name)) {
    $_sql = "SELECT id,title,theme FROM " . $GLOBALS['ESPCONFIG']['survey_table'] . " WHERE name = $_name";
    if ($_result = execute_sql($_sql)) {
        if (record_count($_result) > 0)
            list($sid, $_title, $_css) = fetch_row($_result);
        db_close($_result);
    }
    unset($_sql);
    unset($_result);
}


if (isset($_GET['id'])) {
    $_name = _addslashes($_GET['id']);
    unset($_GET['id']);
    $_SERVER['QUERY_STRING'] = ereg_replace('(^|&)id=[^&]*&?', '', $_SERVER['QUERY_STRING']);
}
if (isset($_POST['id'])) {
    $_name = _addslashes($_POST['id']);
    unset($_POST['id']);
}

if (!empty($_name)) {
    $_sql = "SELECT id,title,theme FROM " . $GLOBALS['ESPCONFIG']['survey_table'] . " WHERE id = $_name";
    if ($_result = execute_sql($_sql)) {
        if (record_count($_result) > 0)
            list($sid, $_title, $_css) = fetch_row($_result);
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


if (empty($_name) && isset($sid) && $sid) {
    $_sql = "SELECT title,theme FROM " . $GLOBALS['ESPCONFIG']['survey_table'] . " WHERE id = '$sid'";
    if ($_result = execute_sql($_sql)) {
        if (record_count($_result) > 0) {
            list($_title, $_css) = fetch_row($_result);
        }
        db_close($_result);
    }
    unset($_sql);
    unset($_result);
}

if (isset($_GET['project'])) {
    $__id = _addslashes($_GET['project']);
    //unset($_GET['project']);
    $_SERVER['QUERY_STRING'] = ereg_replace('(^|&)project=[^&]*&?', '', $_SERVER['QUERY_STRING']);
}
if (isset($_POST['project'])) {
    $__id = _addslashes($_POST['project']);
    unset($_POST['project']);
}

if (!empty($__id)) {
    $_sql = "SELECT id,name,presurvey,postsurvey,action_url FROM project WHERE id = $__id";
    if ($_result = execute_sql($_sql)) {
        if (record_count($_result) > 0)
            list($__sid, $__pname, $__pres, $__posts, $__action) = fetch_row($_result);
        db_close($_result);
    }
    unset($_sql);
    unset($_result);
}
if (isset($_GET['stype']))
    $stype = $_GET['stype'];
include($ESPCONFIG['handler_prefix']);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
    "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <title><?php echo($_title); ?></title>
        <script type="text/javascript" src="js/default.js"></script>
        <script type="text/javascript" src="js/jquery.js"></script>
        <script type="text/javascript" src="js/vulab.public.js"></script>
<?php
if (!empty($_css)) {
    echo('<link rel="stylesheet" href="' . $GLOBALS['ESPCONFIG']['css_url'] . $_css . "\" type=\"text/css\" />\n");
}
unset($_css);
?>
        <script type="text/javascript">
            function closeIframe() {
                var ifr = parent.document.getElementById("postIframe");
                ifr.parentNode.removeChild(ifr);
            }
  
            function postSurveyComplete() {
                parent.postSurveyComplete();
            }
  
            function success() {
                parent.success();
            }
        </script>
                    <script type="text/javascript" src="../infusion/InfusionAll.js"></script>
            <script type="text/javascript" src="../infusion/tests/manual-tests/lib/jquery/plugins/selectbox/jquery.selectbox-0.5.js"></script>
            <script type="text/javascript" src="http://ckeditor-fluid.appspot.com/ckeditor.js"></script>
            <link type="text/css" rel="stylesheet" href="../infusion/framework/fss/css/fss-reset.css" />
            <link type="text/css" rel="stylesheet" href="../infusion/framework/fss/css/fss-layout.css" />
            <link type="text/css" rel="stylesheet" href="../infusion/framework/fss/css/fss-text.css" />
            <link type="text/css" rel="stylesheet" href="../infusion/framework/fss/css/fss-theme-mist.css" />
    </head>
    <body>
<?php
unset($_name);
unset($_title);
include($ESPCONFIG['handler']);

if ($_GET['stype'] == 'post' AND $_REQUEST[rid] AND $_GET['sessionid']) {
    $vid = $_GET['sessionid'];
    $rid = $_REQUEST['rid'];
    require_once('../admin/include_all.php');
    require_once("./phpESP.first.php");
    include('../admin/include/lib/vulab.responses.class.php');
    $response = new Response(@$rid);
    @$response_data = array('vid' => @$vid);

    $result = $response->update(@$response_data);
    if (is_array($result)) {
        $err = $result;
        die($err);
    } else {
        if ($result) {
            #echo "Successfully submitted your Video ID! <br />You Can Now Return with the Above Link";
        }
    }
}
/* 	echo "<pre>";
  print_r($_POST);
  print_r($_SESSION);
  print_r($_REQUEST);
  echo "</pre>";
  if ($stype == 'post' AND $_REQUEST['rid']) {
  echo "<div id='submitVID' style='padding:10px;'>
  What was your video id? <input type='text' name='vid' /> <input type='hidden' name='rid' value='$_REQUEST[rid]'/> <input type='submit' value='Submit Video ID' />
  </div>";
  } */
/* if (isset($__action) && $__action != "" && $__action != null)
  echo "<a href=\"gluebox.php?project=$__sid\">Visit URL</a><br />";
  elseif (isset($__postname) && $__postname != "" && $__postname != null)
  echo "<a href=\"survey.php?name=" . $__postname ."&project=$__sid&stype=post\">Post-Survey</a><br />"; */
?>
    </body>
</html>
