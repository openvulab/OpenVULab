<?
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
global $_POST;
if (@$_GET[where] == 'manage') {
	if (!empty($_SESSION['pid'])) { unset($_SESSION['pid']); }
	if (!empty($_SESSION['renamed'])) { unset($_SESSION['renamed']); }
	if (!empty($_SESSION['last_tab'])) { unset($_SESSION['last_tab']); }
	if (!empty($_SESSION['curr_q'])) { unset($_SESSION['curr_q']); }
	if (!empty($_SESSION['survey_id'])) { unset($_SESSION['survey_id']); }
	if (!empty($_SESSION['new_survey'])) { unset($_SESSION['new_survey']); }
}

//ini_set('display_errors','0');

    /* $Id: manage.php,v 1.32 2007/12/10 12:15:55 liedekef Exp $ */

    /* vim: set tabstop=4 shiftwidth=4 expandtab: */

    // Written by James Flemer
    // For eGrad2000.com
    // <jflemer@alum.rpi.edu>

    if (!defined('ESP_BASE'))
    define('ESP_BASE', dirname(dirname(__FILE__)) .'/');
    $CONFIG = ESP_BASE . '/admin/phpESP.ini.php';

    if(!file_exists($CONFIG)) {
        echo("<b>FATAL: Unable to open $CONFIG. Aborting.</b>");
        exit;
    }
    if(!extension_loaded('mysql')) {
        echo('<b>FATAL: Mysql extension not loaded. Aborting.</b>');
        exit;
    }
    require_once($CONFIG);
  	
  	///Include Our Libraries
	require_once ($ESPCONFIG['include_path']."/lib/vulabdatalib.php");
	require_once ($ESPCONFIG['include_path']."/lib/vulab.functions.php");
	require_once ($ESPCONFIG['include_path']."/lib/vulab.projects.class.php");
	require_once ($ESPCONFIG['include_path']."/lib/vulab.projects.function.php");
	require_once ($ESPCONFIG['include_path']."/lib/vulab.users.class.php");
	require_once ($ESPCONFIG['include_path']."/lib/vulab.users.function.php");
	require_once ($ESPCONFIG['include_path']."/lib/vulab.surveys.class.php");
	require_once ($ESPCONFIG['include_path']."/lib/vulab.debugger.php");
	require_once ($ESPCONFIG['include_path']."/lib/vulab.permissions.class.php");
	
	
    /* check for an unsupported web server configuration */
    if((in_array(php_sapi_name(), $ESPCONFIG['unsupported'])) and ($ESPCONFIG['auth_design']) and ($ESPCONFIG['auth_mode'] == 'basic')) {
        echo ('<b>FATAL: Your webserver is running PHP in an unsupported mode. Aborting.</b><br/>');
        echo ('<b>Please read <a href="http://phpesp.sf.net/cvs/docs/faq.html?rev=.&content-type=text/html#iunsupported">this</a> entry in the FAQ for more information</b>');
        exit;
    }
    esp_init_adodb();
    if(get_cfg_var('register_globals')) {
        $_SESSION['acl'] = &$acl;
    }
    if($ESPCONFIG['auth_design']) {
        if ($ESPCONFIG['auth_mode'] == 'basic') {
            $raw_password = @$_SERVER['PHP_AUTH_PW'];
            $username = @$_SERVER['PHP_AUTH_USER'];
        }
        elseif ($ESPCONFIG['auth_mode'] == 'form') {
            if (isset($_POST['Login'])) {
                if (!isset($_POST['username'])) {
                    $username = "";
                }
                if ($_POST['username'] != "") {
                    $_SESSION['username'] = $_POST['username'];
                }
                if (!isset($_POST['password'])) {
                    $password = "";
                }
                if ($_POST['password'] != "") {
                    $_SESSION['raw_password'] = $_POST['password'];
                }
            }
            if (isset($_SESSION['username'])) {
                $username = $_SESSION['username'];
            }
            else {
                $username = "";
            }
            if (isset($_SESSION['raw_password'])) {
                $raw_password = $_SESSION['raw_password'];
            }
            else {
                $raw_password = "";
            }
        }
        $password = _addslashes($raw_password);
        if(!manage_auth($username, $password, $raw_password))
        	exit;
    } else {
        $_SESSION['acl'] = array (
            'username'  => 'none',
            'pdesign'   => array('none'),
            'pdata'     => array('none'),
            'pstatus'   => array('none'),
            'pall'      => array('none'),
            'pgroup'    => array('none'),
            'puser'     => array('none'),
            'superuser' => 'Y',
            'disabled'  => 'N'
        );
    }
	
	if($_SESSION['acl']) {
		$user = new User($_SESSION['acl']['userid']);
		if ($user->details['researcher'] == 'Y') {
			$interface = 'researcher';
			$interface_suffix = '';
		}
		elseif ($user->details['researcher'] == 'N') {
			$interface = 'tester';
			$interface_suffix = '_'.$interface;
		}
	}
	
    if(isset($_POST['where']))
       $where = $_POST['where'];
    elseif(isset($_GET['where']))
       $where = $_GET['where'];
	if (!@$where) { $where = 'manage'; }
	if (!isset($where)) { $where = 'manage'; }
	
	
    if ($where == 'download') {
        include(esp_where($where));
        exit;
    }
    
    if ($_SESSION['acl']['username'] == 'root')
		$_SESSION['acl']['superuser'] = 'Y';
?>

<?php if (@$_GET[lay] != 'ajax') { ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title><?php echo($ESPCONFIG['title']); ?></title>
    <script type="text/javascript" src="<?php echo($ESPCONFIG['js_url']);?>default.js"></script>
	<script type="text/javascript" src="<?php echo($ESPCONFIG['js_url']);?>jquery-1.2.6.pack.js"></script>
    <script type="text/javascript" src="<?php echo($ESPCONFIG['js_url']);?>jquery.ajaxContent.js"></script>
    <script type="text/javascript" src="<?php echo($ESPCONFIG['js_url']);?>vulab.admin.js"></script>
    <script type="text/javascript" src="<?php echo($ESPCONFIG['js_url']);?>jquery.form.js"></script>
    <script type="text/javascript" src="<?php echo($ESPCONFIG['js_url']);?>thickbox.js"></script>
    <link rel="stylesheet" href="<?php echo($ESPCONFIG['js_url']);?>thickbox.css" type="text/css" media="screen" />
    
<?php
	if(!empty($ESPCONFIG['style_sheet'])) {
		echo("<link href=\"". $ESPCONFIG['style_sheet'] ."\" rel=\"stylesheet\" type=\"text/css\" />\n");
	}
	if(!empty($ESPCONFIG['charset'])) {
		echo('<meta http-equiv="Content-Type" content="text/html; charset='. $ESPCONFIG['charset'] ."\" />\n");
	}
?>
<script type="text/javascript">

</script>
</head>
<body>
<?php } ?>
 <?php
	/* Moved to Stylesheet
	*
	*echo('bgcolor="'. $ESPCONFIG['main_bgcolor'] .'"');
	*if(!empty($ESPCONFIG['link_color']))  echo(' link="'.  $ESPCONFIG['link_color']  .'"');
	*if(!empty($ESPCONFIG['vlink_color'])) echo(' vlink="'. $ESPCONFIG['vlink_color'] .'"');
	*if(!empty($ESPCONFIG['alink_color'])) echo(' alink="'. $ESPCONFIG['alink_color'] .'"'); 
	*/

	if($ESPCONFIG['DEBUG']) {
		include($ESPCONFIG['include_path']."/debug".$ESPCONFIG['extension']);
	}
	if (@$_SESSION[debug]) {
	echo "<a id='debug_toggle' class='hand'>minimize debug</a> - <a id='log_toggle' class='hand'>expand log</a> - <a href='?where=desettings'>settings</a>";
	echo "<pre class='debug'>";
	echo '<strong>$_POST</strong>'."\n";
	print_r($_POST);
	/*echo '<strong>$_GET</strong>'."\n";
	print_r($_GET);*/
	echo '<strong>$_SESSION</strong>'."\n";
	print_r($_SESSION);
	/*echo '<strong>System</strong>';
	echo "<li>step: ".@$step."</li>";
	echo "<li>go: ".@$go."</li>";
	echo "<li>from: ".@$from."</li>";

	echo '<strong>$project</strong>'."\n";
	print_r($project);
		*/
	echo "</pre>";
	echo "<pre class='log'>";
	echo "</pre>";
	}
	if (!@$_GET['lay']) { $_GET['lay'] = 'full'; }
	
	if ($_GET['lay'] == 'full') {
		if(file_exists($ESPCONFIG['include_path']."/head".$ESPCONFIG['extension'])) {
			include($ESPCONFIG['include_path']."/head".$ESPCONFIG['extension']);
		}
	}
	if ($where != 'logout' AND $where != 'account' AND $where != 'help') {
		$where_interface = "$where$interface_suffix";
	}
//	$include_where = ;
	include(esp_where(($where_interface ? $where_interface : $where)));
	if(@$_GET[lay] == 'full') {
		if(file_exists($ESPCONFIG['include_path']."/foot".$ESPCONFIG['extension']))
			include($ESPCONFIG['include_path']."/foot".$ESPCONFIG['extension']);


?>
</body>
</html>
<?php }//end ajax lay if ?>