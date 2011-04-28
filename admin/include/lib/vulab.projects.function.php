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
//Gets Projects based on an userid and a status
//- Returns: array of found project objects.
function get_projects_access($userid,$status='3',$sort=NULL) {
	$sql = "SELECT * FROM `userprojectrel` WHERE `userid` ='$userid'";
	$res = execute_sql($sql);
	if (ErrorMsg()) $err[] = ErrorMsg();
	if ($err) return $err;
	$return = array();

	while (!$res->EOF) {

		list ($p['id'],$p['userid'],$p['projectid'],$p['admin']) = $res->fields;
		$return[] = array_reverse($p);
		$res->MoveNext();		
	}
	return $return;
}
//function will return all public pre or post surveys. 
function  get_public_projects($pre_or_post){
	$getSQL = "SELECT p.id 
			   FROM project as p INNER JOIN survey as s ON
			   p.".$pre_or_post." = s.id
			   WHERE s.PublicSurvey = 'Y'";
	$proj_result = execute_sql($getSQL);
	while (!$proj_result->EOF AND $count < 30) {
		
		++$count;
		list(	$p['id']) = $proj_result->fields;	
		$p = array_reverse($p);

		unset($newproj);
		$newproj = new Project;
		$newproj->init($p['id']);
		$projects[] = $newproj;
		
		$proj_result->MoveNext();
	}
	
	return $projects;
	
}

function get_projects_by($userid,$status='ALL',$sort=NULL) {
	if (!is_numeric($status)) { 
		if (strtolower($status) == 'draft' OR strtolower($status) == 'drafts' OR strtolower($status) == 'd') { $status = 1; }
		if (strtolower($status) == 'active' OR strtolower($status) == 'a') { $status = 2; }
		if (strtolower($status) == 'complete' OR strtolower($status) == 'completed' OR strtolower($status) == 'c') { $status = 3; }
	}
	if ($userid == 1) {
		$user_where = "";
	} else {
		$user_where = "AND `userprojectrel`.`userid` = '$userid'";
	}
	$getSQL = "
	SELECT `project`.id
	FROM userprojectrel, project
	WHERE
		`userprojectrel`.projectid = `project`.`id`
		$user_where
	";
	if ($status != 'ALL') { $getSQL .= "AND `project`.`status` = '$status'"; }
	if ($sort) { $getSQL .= "ORDER BY $sort"; }
	//echo $getSQL;
	
	$proj_result = execute_sql($getSQL);
	while (!$proj_result->EOF AND $count < 30) {
		
		++$count;
		list(	$p['id'],
				$p['name'],
				$p['pre_id'],
				$p['post_id'],
				$p['intro'],
				$p['outro'],
				$p['url'],
				$p['start'],
				$p['end'],
				$p['status'],
				$p['createstamp'],
				$p['editstamp'],
				$p['activestamp'],
				$p['completestamp']) = $proj_result->fields;	
		$p = array_reverse($p);

		unset($newproj);
		$newproj = new Project;
		$newproj->init($p['id']);
		$projects[] = $newproj;
		
		$proj_result->MoveNext();
	}
	
	return $projects;
}
function get_projects_byowner($ownerid,$options=null) {
	
	if (!isset($ownerid)) { return 0; }
	if ($options['limit']) { $suffix = "LIMIT = '$options[limit]' "; }
	$sql = "SELECT * FROM ".$GLOBALS['ESPCONFIG']['userprojectrel_table']." WHERE "."userid='$ownerid' ".$suffix;

	$result = execute_sql($sql);
	while (!$result->EOF) {
		$result->MoveNext();
		$p = array();
		unset($p);
		list(	$p['id'],
				$p['userid'],
				$p['projectid'],
				$p['admin']) = $result->fields;
				
		if ($p['id']) { $projects[] = array_reverse($p); }
	}
	return $projects;
}
//Takes a list of projects and returns only those that are active.
function filter_projects_bystatus($projects,$status,$operator) {
/*	$active = array();

			echo "</pre>";
			
	foreach ($projects as $p) {
		if (isset($p['id'])) {	
	
			unset($project);
			$project = new Project;
			$project->init($p['id']);

			if ($operator == '==') {
				if ($project->details['status'] == $status)
				{
					$active[] = $project;
				}
			} elseif ($operator == '!=') {
				if ($project->details['status'] != $status)
				{
					$active[] = $project;
				}		
			}
		}
	}
	return $active;*/
}
//Takes a list of projects and returns only those that are active.
//LEGACY!
/*
function filter_projects_bystatus($projects,$status,$operator) {
	$active = array();
	foreach ($projects as $p) {
		if (isset($p['id'])) {	
	
			unset($project);
			$project = new Project;
			$project->init($p['id']);
			if ($operator == '==') {
				if ($project->pre_survey['status'] == $status OR $project->post_survey['status'] == $status)
				{
					$active[] = $project;
				}
			} elseif ($operator == '!=') {
				if ($project->pre_survey['status'] != $status OR $project->post_survey['status'] != $status)
				{
					$active[] = $project;
				}		
			}
		}
	}
	return $active;
}*/

function clean_cut_parray($projects) {
	$i = 0;
	while (count($cleaned_projects) <= 4)
	{
		if ($projects[$i]->details[id]) { $cleaned_projects[] = $projects[$i]; }
		++$i;
	}
	return $cleaned_projects;
}

//- Takes array of Project Objects
//- Returns HTML table of Project Fields
function display_projects_table($fields,$projects,$options=null) {


	if (!is_array($fields)) { return "no fields"; }
	$HTML = '<table class="display">'."\n";
	
	if ($options['titles']) {
		$HTML .= '	<tr>';
		foreach ($fields as $field) {
		
			if ($field == 'activestamp') {
				$field = 'Date Activated';
			}
			if ($field == 'completestamp') {
				$field = 'Date Completed';
			}
			if ($field == 'createstamp') {
				$field = 'Date Created';
			}
			$HTML .= "<th>".ucwords($field)."</th>";
		}
		//if ($options['action_set']) { echo "<th>Actions</th>"; }
		$HTML .= "<th>Action</th>";
		$HTML .= '</tr>'."\n";
	}
	foreach ($projects as $project) {
		
		
		if ($project->details[id]) {
			//Setup Links
			if (strtolower($options['status']) == 'draft' OR $options['status'] == 1) {
				unset($plink);
				$plink = "?where=create&amp;pid=".$project->details[id];
			}
			elseif (strtolower($options['status']) == 'active' OR $options['status'] == 2) {
				unset($plink);
				$plink = "?where=view&amp;pid=".$project->details[id];
			}
			elseif (strtolower($options['status']) == 'complete' OR $options['status'] == 3) {
				unset($plink);
				$plink = "?where=view&amp;pid=".$project->details[id];
			}
			else {
				unset($plink);
				$plink = "?where=create&amp;pid=".$project->details[id];
			}
			if ($options['link']) {
				$plink = str_replace('<pid>',$project->details[id],$options['link']);
			}
			//echo "<pre>";
			//print_r($project);
			//echo "</pre>";
			
			$HTML .= '<tr>';
			foreach ($fields as $key=>$field) {
				unset($field_data);
				$field_data = $project->details[$field];
				if (is_numeric(strpos($field,'stamp'))) {
					$field_data = date("F j, Y, g:i a",$field_data);
				}
				if (!($_GET['where'] == 'viewall')) {
					if (strtolower($options['status']) == 'draft' OR $options['status'] == 1)
						$HTML .= "<td>$field_data - <a href='$plink' $options[link_attrib]> Edit</a></td>";
					elseif (strtolower($options['status']) == 'active' OR $options['status'] == 2) {
						$testers = $plink.'&amp;viewtype=testers';
						$HTML .= "<td>$field_data - <a href='$plink' $options[link_attrib]> Results</a> - <a href='$testers'> Testers</a></td>";
					} elseif (strtolower($options['status']) == 'complete' OR $options['status'] == 3) {
						$HTML .= "<td>$field_data - <a href='$plink' $options[link_attrib]> Results</a></td>";
					} else
						$HTML .= "<td><a href='$plink' $options[link_attrib]>$field_data</a></td>";
				} else {
					if (strtolower($options['status']) == 'draft' OR $options['status'] == 1)
						$HTML .= "<td>$field_data</td>";
					elseif (strtolower($options['status']) == 'active' OR $options['status'] == 2) {
						$testers = $plink.'&amp;viewtype=testers';
						$HTML .= "<td>$field_data</td>";
					} else
						$HTML .= "<td>$field_data</td>";
				}
			}
			if ($options['action_set']) { $HTML .= "<td>".render_actions_html($options['action_set'],$project->details[id])."</td>"; }
			$HTML .= '</tr>'."\n";
		}
	}
	$HTML .= '</table>'."\n";
	return $HTML;
}
function render_actions_html($type,$pid) {
switch($type) {
case 'draft_small':
	return "<a href='#'>edit</a>";
break;
case 'active_small':
	return "<a href='#'>publish</a>";
break;
case 'draft':
	return "<a href='?where=activateproject&amp;lay=ajax&amp;id=$pid&amp;KeepThis=true&amp;TB_iframe=true&amp;height=200&amp;width=450' class='thickbox' title='Are you sure you want to activate this project?'>Activate Project</a> | <a href='?where=create&amp;pid=$pid'>Edit Project</a>";
break;
case 'active':
	return "<a href='?where=view&amp;pid=$pid'>View Results</a> | <a href='?where=view&amp;pid=$pid&amp;viewtype=testers'>View Testers</a> | <a href='?where=deactivateproject&amp;lay=ajax&amp;id=$pid&amp;KeepThis=true&amp;TB_iframe=true&amp;height=200&amp;width=450' class='thickbox' title='Are you sure you want to deactivate this project?'>Deactivate Project</a>";
case 'completed':
	return "<a href='?where=viewcompleted&amp;pid=$pid'>View Results</a>";
break;

}



function create_legacy($data,$option=null) {
	require ESP_BASE.'admin/sanitize.php';
/*
		echo "<pre>";
		print_r($_POST);
		echo "</pre>";
*/
	$pname = sanitize($data['pname']);
	$ppre = sanitize($data['ppre']);
	$ppost = sanitize($data['ppost']);
	$pintro = sanitize($data['pintro']);
	$pthanks = sanitize($data['pthanks']);
	$purl = sanitize($data['purl']);
	$pstart = sanitize($data['pend']);
	$pend = sanitize($data['pstart']);
	$sql = execute_sql("SELECT * FROM `$ESPCONFIG[project_table]` WHERE `name` = '".$project_name."'");
	if ($sql->RecordCount() > 0)
	{
		// Project already exists
		echo("<h2>$project_name already exists.</h2>");
	}
	// Check the validity of the URL
/*	elseif (!validLink($actionurl))
	{
		// url is invalid
		echo("<h2>Invalid URL</h2>");
	}
	elseif ($presurvey == $postsurvey && ($presurvey!= -1))
	{
		echo("<h2>Postsurvey can not equal Presurvey</h2>");
	}*/
	else
	{
	$sqlins = 'insert into '.$ESPCONFIG[project_table].
	 ' (name,presurvey,postsurvey,action_intro_msg,action_outro_msg,action_url) values ( ' .
	"'$pname', ".
	"'$ppre', ".
	"'$ppost', ".
	"'$pintro', ".
	"'$pthanks', ".
	"'$purl') ";
	
	$result = execute_sql($sqlins);
	echo ErrorMsg();
	
/*	$sqlresults = "select * from $ESPCONFIG[project_table] WHERE name = '".$project_name."'";
	$result = execute_sql($sqlresults);
	$projectid = $result->fields[0];*///Replaced by mysql_insert_id();
	$projectid = mysql_insert_id();
	echo $projectid;
	// Insert into userprojectrel table
	$sqlins = "insert into userprojectrel values ('','".$_SESSION['acl']['userid']."','".$projectid."','Y')";
	
	$result = execute_sql($sqlins);
	echo ErrorMsg();
	
	// Insert the root user record
	$sqlins = "insert into userprojectrel values ('','6','".$projectid."','Y')";
	
	$result = execute_sql($sqlins);
	echo ErrorMsg();
	
	if ($ppre) { 
		$sql = "UPDATE `survey` SET `status` = '1' WHERE `id` = '$presurvey'";
		execute_sql($sql);
	}
	if ($ppost) {
		$sql = "UPDATE `survey` SET `status` = '1' WHERE `id` = '$postsurvey'";
		execute_sql($sql);
	}

	}// ELSE END

}

}
?>