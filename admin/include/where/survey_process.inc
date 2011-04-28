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
	/*Deprecated
	session_register('survey_id');
	session_register('new_survey');
	session_register('last_tab');
	session_register('curr_q');*/
	if(!isset($_SESSION['survey_id'])){
		$_SESSION['survey_id'] = "";
		$_SESSION['new_survey'] = "";
		$_SESSION['last_tab'] = "";
		$_SESSION['curr_q'] = "";
	}
	if (!@$_POST['where_context']) { @$_POST['where_context'] = ''; } else { @$where_context = @$_POST['where_context']; }
	if (!@$_GET['where_context']) { @$_GET['where_context'] = ''; } else { @$where_context = @$_GET['where_context']; }
	
	/* Use this hack to work around how PHP handles session vars.
	 * When Register_Globals is on, the value of the global $foo
	 * is saved, and $_SESSION['foo'] is ignored.
	 * When Register_Globals is off, the global $foo is ignored
	 * and $_SESSION['foo'] is saved.
	 * By making $_SESSION['foo'] a copy of $foo
	 * when reg_glob is on, we can use $_SESSION uniformly
	 * from here on, regardless of the INI settings.
	 */
	if(ini_get('register_globals')) {
		$_SESSION['survey_id']  = intval($survey_id);
		$_SESSION['new_survey'] = $new_survey;
		$_SESSION['last_tab']   = $last_tab;
		$_SESSION['curr_q']     = $curr_q;
	}
	
	global $errstr;
	$tab="";
	
	if(@$_GET['where'] == 'new' OR @$_GET['new']) {
		$_SESSION['survey_id']  = '';
		$_SESSION['new_survey'] = '';
		$_SESSION['last_tab']   = '';
		$_SESSION['curr_q']     = '';
	}		
	
	if(!empty($_GET['newid'])) {
		$_SESSION['survey_id']  = intval($_GET['newid']);
		$tab="general";
		$_SESSION['last_tab']   = '';
		$_SESSION['new_survey'] = false;
	}

	if(empty($_SESSION['survey_id'])) {
		$_SESSION['survey_id']  = '';
		$_SESSION['new_survey'] = true;
	}

	if(empty($_SESSION['new_survey']))
		$_SESSION['new_survey'] = empty($_SESSION['survey_id']);
	
	/* check ACL to see if user is allowed to design
	 * _this_ survey */
	 $sql = "SELECT * FROM `user` WHERE `userid` = '".$_SESSION['acl']['userid']."'";
		$result = execute_sql($sql);
	if(!empty($_SESSION['survey_id'])) {
		/*$srealm = auth_get_survey_realm($_SESSION['survey_id']);
		if($_SESSION['acl']['superuser'] != 'Y' &&
				!auth_is_owner($_SESSION['survey_id'], $_SESSION['acl']['username']) &&
				!in_array($srealm, array_intersect(
						$_SESSION['acl']['pdesign'],
						$_SESSION['acl']['pall'])) &&
				!auth_no_access(_('to access this form'))) {
			return;
		}*/
		if ($_SESSION['acl']['superuser'] != 'Y' &&
			$result->fields[6] != 'Y')
				auth_no_access(_('to access this form'));
		//else
		//	return;
		
	}

	/* check user's ACL to see if they have rights to
	 * edit/create _any_ survey */
	if($_SESSION['acl']['superuser'] != 'Y' &&
			$result->fields[6] != 'Y' &&
			!auth_no_access(_('to access this form'))) {
		return;
	}
		
	if (isset($_POST['tab'])) {
		$tab=$_POST['tab'];
	}
	if ($tab=="") {
		$tab = $_SESSION['last_tab'];
	}
	$tab = strtolower(preg_replace('/ +/','_',$tab));

/* XXX I18n do not translate */
	if(stristr($tab,'continue')) {
		switch($_SESSION['last_tab']) {
			case 'general':
				$tab='questions';
				break;
			case 'questions':
				$tab='order';
				break;
			case 'order':
				$tab='conditions';
				break;
			case 'conditions':
				$tab='preview';
				break;
			default:
				$tab='general';
		}
	}

/* XXX I18n do not translate */
		
	if(!preg_match('/^[A-Za-z0-9_]+$/',$tab))	// Valid chars are [A-Za-z0-9_]
		$tab = 'general';
	if(!file_exists($ESPCONFIG['include_path'].'/tab/'.$tab.$ESPCONFIG['extension']))
		$tab = 'general';
	if(!file_exists($ESPCONFIG['include_path'].'/tab/'.$tab.$ESPCONFIG['extension'])) {
		echo('<b>'. _('Unable to open include file. Check INI settings. Aborting.'). '</b>');
		exit;
	}
	
	$errstr = '';
	$updated = survey_update($_SESSION['survey_id'],$tab,$_SESSION['last_tab']);
	
?>