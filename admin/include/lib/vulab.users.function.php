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
/*
File: 		vulab.users.function.php \\v 1.0
Info:		- handle some common user functionality (not relating to one specific user)
Author: 	Blake Edwards
Email:		electBlake@gmail.com

License: 	http://source.fluidproject.org/svn/fluid/components/trunk/LICENSE.txt
*/
?>
<?php

//General Users Functions


function getUsers($usertype = 'tester',$number = NULL) {
	
	if ($usertype == 'tester') {
		$usertype_sql = "WHERE `isresearcher` = 'N' AND `disabled` = 'N'";
	} elseif ($usertype == 'researcher') {
		$usertype_sql = "WHERE `isresearcher` = 'Y' AND `disabled` = 'N'";
	} elseif ($usertype == 'all') {
		$usertype_sql = "";
	} elseif ($usertype == 'disabled') {
		$usertype_sql = "WHERE `disabled` = 'Y'";
	}
	$limit_sql = ($number ? "LIMIT $number" : '');
	$sql = "SELECT *
			FROM `user`
			$usertype_sql
			$limit_sql
			";
	$testers_result = execute_sql($sql);
	if (!$testers_result) {
		$err = $testers_result;
	}

	while (!$testers_result->EOF) {
		$testers_result->MoveNext();
		++$count;
		unset($u);
		list(	$u['userid'],
				$u['username'],
				$u['passowrd'],
				$u['fname'],
				$u['lname'],
				$u['email'],
				$u['isresearcher'],
				$u['disabled']) = $testers_result->fields;	
		
		unset($u['password']);
		unset($u['researcher']);
		unset($u['disabled']);
//		$testers[] = array_reverse($u);
		$testers[] = new User($u['userid']);
	}
	if ($err) return $err;
	return $testers;
}
function userFilterPerm($users,$pid,$perm='N') {

	//Get Project Users
	$psql = "SELECT *
			FROM `userprojectrel`
			WHERE projectid = '$pid' AND admin='$perm'
			";
	$pres = execute_sql($psql);
	$project_users = $pres->GetAll();
	print_r($project_users);
	

}
//- Takes array of Project Objects
//- Returns HTML table of Project Fields
function display_users_table($fields,$users,$options=null) {


	if (!is_array($fields)) { return "no fields"; }
	$HTML = '<table class="display padded">'."\n";
	if (count($users) == 0 && $fields[0] == 'option_checkbox')
		$HTML .= '<caption style="font-style:italic; font-weight:bold; color:#00336F; font-size:17px">No Users Available to Add</caption><tr><td></td></tr>';
	elseif (count($users) == 0 && $fields[0] == 'option_none')
		$HTML .= '<caption style="font-style:italic; font-weight:bold; color:#00336F; font-size:17px">No Current Active Users</caption><tr><td></td></tr>';
	else {
		if ($options['titles']) {
			$HTML .= '	<tr>';
			foreach ($fields as $field) {
			
				if ($field == 'option_checkbox') {
					$HTML .= "<th class='slim center'>select <br/><a href='#checkall' class='options0'>all</a> | <a href='#checknone' class='options0' >none</a></th>";
				} elseif ($field == 'option_none'){
					 $HTML .= "<th></th>";
				} else {
					$field_name = ($options['aliases'][$field] ? $options['aliases'][$field] : $field );
					$HTML .= "<th>$field_name</th>";
				}
			}
			//if ($options['action_set']) { echo "<th>Actions</th>"; }
			$HTML .= '</tr>'."\n";
		}
		
		foreach ($users as $user) {
			
			//Setup Links
			$plink = "?where=users&uid=".$user->details[userid];
				
			$HTML .= '<tr>';
			foreach ($fields as $field) {
				if ($field == 'option_checkbox') {
					$HTML .= "<td class='center'><input type='checkbox' name='users[$user->id]' id='users[$user->id]' value='$user->id' class='options0' /></td>";
				} elseif ($field == 'option_none'){
					 $HTML .= "<td></td>";
				} else { 
					//$HTML .= "<td><a href='$plink'>".$user->details[$field]."</a></td>";
					$HTML .= "<td>".$user->details[$field]."</td>";
				}
			}
			if ($options['action_set']) { $HTML .= "<td>".render_actions_html($options['action_set'],$user->details[id])."</td>"; }
			$HTML .= '</tr>'."\n";
		}
	}
	$HTML .= '</table>'."\n";
	return $HTML;
}
?>