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

function get_surveys_byowner($ownerid,$options=null) {
	
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
function filter_surveys_bystatus($surveys,$status,$operator) {
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
}
function clean_cut_parray($projects) {
	$i = 0;
	while (count($cleaned_projects) <= 4)
	{
		if ($projects[$i]->details[id]) { $cleaned_projects[] = $projects[$i]; }
		++$i;
	}
	return $cleaned_projects;
}
function display_surveys_table($fields,$projects,$options=null) {

	
	if (!is_array($fields)) { return "no fields"; }
	$HTML = '<table class="data_nice">'."\n";
	
	if ($options['titles']) {
		$HTML .= '	<tr>';
		foreach ($fields as $field) {
			$HTML .= "<th>$field</th>";
		}
		//if ($options['action_set']) { echo "<th>Actions</th>"; }
		$HTML .= '</tr>'."\n";
	}
	foreach ($projects as $project) {
		
		if ($project->details[id]) {
			$HTML .= '<tr>';
			foreach ($fields as $field) {
				$HTML .= "<td><a href=?where=viewproject&id=".$project->details[id].">".$project->details[$field]."</a></td>";
			}
			if ($options['action_set']) { $HTML .= "<td>".render_actions_html($options['action_set'])."</td>"; }
			$HTML .= '</tr>'."\n";
		}
	}
	$HTML .= '</table>'."\n";
	return $HTML;
}
function render_survey_actions_html($type) {
switch($type) {
case 'drafts':
	return "<input type='button' value='Activate' />";
break;
case 'active':
	return "<input type='button' value='Results' /> <input type='button' value='Extend Date' /> <input type='button' value='Complete' />";
break;

}
}
?>